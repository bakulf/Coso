#define C_PACKAGE  "coso"
#define C_VERSION  "0.1"
#define C_PATH     ".coso"
#define C_GLOBAL   "_global"

#define C_TASK_ROOT_TAG "CosoTask"
#define C_TASK_TYPE_TAG "Type"

// Edit File Task -----------------------------------------------------------
#define C_TASK_EDITFILE_NAME "editFile"

#define C_TASK_EDITFILE_INPUT_TAG "FileInput"
#define C_TASK_EDITFILE_OUTPUT_TAG "FileOutput"

#define C_TASK_EDITFILE_TOKEN_START "__COSO_START__"
#define C_TASK_EDITFILE_TOKEN_END   "__COSO_END__"

// Remove File Task ---------------------------------------------------------
#define C_TASK_REMOVEFILE_NAME "removeFile"
#define C_TASK_REMOVEFILE_FILE_TAG "File"

// Remove File Task ---------------------------------------------------------
#define C_TASK_CREATEFILE_NAME "createFile"
#define C_TASK_CREATEFILE_INPUT_TAG "FileInput"
#define C_TASK_CREATEFILE_OUTPUT_TAG "FileOutput"

// Templates ----------------------------------------------------------------
// TODO: comments...
#define C_TASK_EDITFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>editFile</Type>\n" \
    "  <FileInput>/home/baku/.ssh/config.coso</FileInput>\n" \
    "  <FileOutput>/tmp/AA.txt</FileOutput>\n" \
    "</CosoTask>\n"

// TODO: comments...
#define C_TASK_REMOVEFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>editFile</Type>\n" \
    "  <File>/home/baku/.ssh/AA.txt</File>\n" \
    "</CosoTask>\n"

// TODO: comments...
#define C_TASK_CREATEFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>editFile</Type>\n" \
    "  <FileInput>/home/baku/.ssh/config.coso</FileInput>\n" \
    "  <FileOutput>/tmp/AA.txt</FileOutput>\n" \
    "</CosoTask>\n"
