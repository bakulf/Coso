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
#define C_TASK_EDITFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>editFile</Type>\n" \
    "\n" \
    "  <!-- this file is a template. Please, edit it this part: -->\n" \
    "\n" \
    "  <!-- FileInput must be used for the template of your file -->\n" \
    "  <FileInput>/the/path/of/a/file.txt</FileInput>\n" \
    "  <!-- FileOutput is the file that will be created from the template -->\n" \
    "  <FileOutput>/the/output/file.txt</FileOutput>\n" \
    "</CosoTask>\n"

#define C_TASK_REMOVEFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>removeFile</Type>\n" \
    "\n" \
    "  <!-- this file is a template. Please, edit it this part: -->\n" \
    "\n" \
    "  <!-- Here, the path of the file you want to remove: -->\n" \
    "  <File>/an/important/file.txt</File>\n" \
    "</CosoTask>\n"

#define C_TASK_CREATEFILE_TEMPLATE \
    "<CosoTask>\n" \
    "  <Type>createFile</Type>\n" \
    "\n" \
    "  <!-- this file is a template. Please, edit it this part: -->\n" \
    "\n" \
    "  <!-- FileInput will be copied in the path of the output file. -->\n" \
    "  <FileInput>/the/path/of/a/file.txt</FileInput>\n" \
    "  <FileOutput>/the/new/file.txt</FileOutput>\n" \
    "</CosoTask>\n"
