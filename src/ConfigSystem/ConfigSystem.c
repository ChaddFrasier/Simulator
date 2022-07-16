#include "ConfigSystem.h"

static int MAX_LINE_LENGTH = 80;
static int FILE_LENGTH_LINES = 11;
static char * START_PATTERN = "START CONFIG:";
static char * END_PATTERN = "END CONFIG:";

CONFIG_STATUS_CODES CS_ReadConfigFile(FILE *file, ConfigurationData* configData ){
    if(file == NULL){
        return NULL_FILE_ERROR;
    }
    if(configData == NULL) {
        return NULL_DATA_POINTER_ERROR;
    }

    char line[MAX_LINE_LENGTH];
    /* Get each line until there are none left */
    for (int i = 0; i < FILE_LENGTH_LINES; i ++ )
    {
        if(fgets(line, MAX_LINE_LENGTH, file)){
            /* Print each line */
            if(isVersionLine(line)) {
                configData->version = getVersionFromLine(line);
                printf("VERSION IS %ld\n", configData->version);
            }
        }    
    }




    return CONFIGURATION_SUCCESS;
}

double getVersionFromLine( char * line ) {
    return 0.0;
}

bool isVersionLine( char * line ) {
    return true;
}