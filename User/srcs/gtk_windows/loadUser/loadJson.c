
#include "gtk_functions.h"
#include "bt_functions.h"
#include <stdio.h>
#include <stdlib.h> // Added for memory allocation
#include <string.h>
#include <cjson/cJSON.h>

//LOADS THE JSON 
cJSON *loadUser() {
    const char *filePath = "user.json";
    FILE *file = fopen(filePath, "r");
    cJSON *root = NULL;

    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *fileContent = (char *)malloc(fileSize + 1);
        if (fileContent == NULL) {
            fclose(file);
            return NULL;
        }

        fread(fileContent, 1, fileSize, file);
        fileContent[fileSize] = '\0';
        fclose(file);

        root = cJSON_Parse(fileContent);
        free(fileContent);
    }

    return root;
}
