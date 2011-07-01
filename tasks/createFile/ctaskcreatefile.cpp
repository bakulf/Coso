#include "ctaskcreatefile.h"

#include "ccontext.h"
#include "constants.h"

#include <iostream>

CTask *CTaskCreateFile::helper(CContext *context, const QString &name, const QDomElement &root)
{
    QDomElement fileInput = root.firstChildElement(C_TASK_CREATEFILE_INPUT_TAG);
    if (fileInput.isNull()) {
        std::cerr << "WARNING: No input file for the task '"
                  << qPrintable(name)
                  << "` (task ignored)." << std::endl;
        return 0;
    }

    QDomElement fileOutput = root.firstChildElement(C_TASK_CREATEFILE_OUTPUT_TAG);
    if (fileOutput.isNull()) {
        std::cerr << "WARNING: No output file for the task '"
                  << qPrintable(name)
                  << "` (task ignored)." << std::endl;
        return 0;
    }

    return new CTaskCreateFile(context, name, fileInput.text(), fileOutput.text());
}

bool CTaskCreateFile::generator(const QFileInfo &file)
{
    return CTask::generator(file, C_TASK_CREATEFILE_TEMPLATE);
}

CTaskCreateFile::CTaskCreateFile(CContext *context, const QString &name, const QString &fileInput, const QString &fileOutput) :
    CTask(context, name, C_TASK_CREATEFILE_NAME),
    m_fileInput(fileInput),
    m_fileOutput(fileOutput)
{
}

CTaskCreateFile::~CTaskCreateFile()
{
}

const QString CTaskCreateFile::info() const
{
    return QString("Create the file %1 (from the template %2).").arg(m_fileInput).arg(m_fileOutput);
}


int CTaskCreateFile::run(const QString &context)
{
    Q_UNUSED(context);

    if (QFile::exists(m_fileOutput)) {
        std::cerr << "WARNING: the file '"
                  << qPrintable(m_fileOutput)
                  << "` exist." << std::endl;
        return 0;
    }

    if (!QFile::copy(m_fileInput, m_fileOutput)) {
        std::cerr << "ERROR: Error coping file '"
                  << qPrintable(m_fileInput)
                  << "` in '"
                  << qPrintable(m_fileOutput)
                  << "`." << std::endl;
    }

    return 0;
}
