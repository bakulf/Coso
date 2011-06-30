#include "ctaskfile.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

CTask *CTaskFile::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QDomElement fileInput = root.firstChildElement(C_TASK_FILEINPUT_TAG);
    if (fileInput.isNull()) {
        std::cerr << "WARNING: No file for the task '"
                  << qPrintable(name)
                  << "`." << std::endl;
        return 0;
    }

    QDomElement fileOutput = root.firstChildElement(C_TASK_FILEOUTPUT_TAG);
    if (fileOutput.isNull()) {
        std::cerr << "WARNING: No file for the task '"
                  << qPrintable(name)
                  << "`." << std::endl;
        return 0;
    }

    return new CTaskFile(context, name, fileInput.text(), fileOutput.text());
}

CTaskFile::CTaskFile(CContext *context, const QString &name, const QString &fileInput, const QString &fileOutput) :
    CTask(context, name, C_TASK_FILE_NAME),
    m_fileInput(fileInput),
    m_fileOutput(fileOutput),
    m_prevValue(true),
    m_in(false)
{
}

CTaskFile::~CTaskFile()
{
}

const QString CTaskFile::info() const
{
    return QString("Transform the file %1 in %2.").arg(m_fileInput).arg(m_fileOutput);
}


int CTaskFile::run(const QString &context)
{
    QFile input(m_fileInput);
    QFile output(m_fileOutput);

    if (!input.open(QIODevice::ReadOnly)) {
        std::cerr << "WARNING: Error opening the file '" << qPrintable(m_fileInput) << "\"." << std::endl;
        return 1;
    }

    if (!output.open(QIODevice::WriteOnly)) {
        std::cerr << "WARNING: Error opening the file '" << qPrintable(m_fileOutput) << "\"." << std::endl;
        return 1;
    }

    if (input.canReadLine()) {
        std::cerr << "WARNING: the input file doesn't support readLine." << std::endl;
        output.close();
        input.close();
        return 1;
    }

    if (output.canReadLine()) {
        std::cerr << "WARNING: the output file doesn't support readLine." << std::endl;
        output.close();
        input.close();
        return 1;
    }

    while (1) {
        char buffer[4096];
        qint64 size = input.readLine(buffer, sizeof(buffer));
        if (size == -1)
            break;

        if (!checkLine(buffer, size, context))
            continue;

        for (qint64 done = 0; done < size;) {
            qint64 ret = output.write(buffer + done);
            if (ret <= 0) {
                std::cerr << "WARNING: Error writing in the file '" << qPrintable(m_fileOutput) << "\"." << std::endl;
                break;
            }

            done += ret;
        }
    }

    output.close();
    input.close();
    return 0;
}

bool CTaskFile::checkLine(const char *buffer, qint64 size, const QString &context)
{
    QByteArray line(buffer, size);

    if (line.startsWith(C_TASK_FILE_TOKEN_START)) {
        if (m_in) {
            std::cerr << "WARNING: this line breaks the parser (No nested blocks!): '"
                      << qPrintable(QString(QByteArray(buffer, size))) << "`." << std::endl;
            return false;
        }

        line.remove(0, strlen(C_TASK_FILE_TOKEN_START));
        line = line.trimmed();

        if (line.isEmpty()) {
            std::cerr << "WARNING: this line breaks the parser: '"
                      << qPrintable(QString(QByteArray(buffer, size))) << "`." << std::endl;
            return false;
        }

        m_prevValue = (line == context);
        m_in = true;
        return false;
    }

    if(line.startsWith(C_TASK_FILE_TOKEN_END)) {
        if (!m_in) {
            std::cerr << "WARNING: this line breaks the parser (End without Start?!?): '"
                      << qPrintable(QString(QByteArray(buffer, size))) << "`." << std::endl;
            return false;
        }

        m_prevValue = true;
        m_in = false;
        return false;
    }
    
    return m_prevValue;
}
