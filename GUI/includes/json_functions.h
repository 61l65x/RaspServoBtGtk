#ifndef JSON_FUNCTIONS_H
#define JSON_FUNCTIONS_H



typedef struct userData
{
    char            *username;
    int             settings;
    struct userData *next;

}userData;

//SAVE USERS WINDOW


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <cjson/cJSON.h>





#endif