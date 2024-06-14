
#include "gtk_functions.h"
#include "bt_functions.h"
#include "json_functions.h"

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

// GETS THE USERDATA
struct userData *getUserData(void)
{
    cJSON *root = loadUser();
    if (root == NULL)return NULL;

    if (root != NULL && cJSON_IsArray(root)) {
        int arraySize = cJSON_GetArraySize(root);

        for (int i = 0; i < arraySize; i++) {
            cJSON *userObject = cJSON_GetArrayItem(root, i);
            if (cJSON_IsObject(userObject)) {
                cJSON *usernameItem = cJSON_GetObjectItemCaseSensitive(userObject, "username");
                cJSON *settingsItem = cJSON_GetObjectItemCaseSensitive(userObject, "settings");

                if (cJSON_IsString(usernameItem) && cJSON_IsNumber(settingsItem)) {
                    const char *username = usernameItem->valuestring;
                    int settings = settingsItem->valueint;

                    // Now, you can work with 'username' and 'settings' here
                    printf("Username: %s, Settings: %d\n", username, settings);
                }
            }
        }
    }

}

