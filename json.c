//
// json.h cJSON utility wrapper
// taka-wang
//

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

// get char string via key from cJSON object
char *json_get_char(cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem(inJson, key)->valuestring;
}

// get int via key from cJSON object
int json_get_int(cJSON *inJson, const char *key)
{
    return cJSON_GetObjectItem(inJson, key)->valueint;
}

// load json file to cJSON 
int file_to_json(const char *fname, cJSON **outJson)
{
    FILE *fPtr = fopen(fname,"rb");
    if (fPtr) 
    {
        fseek(fPtr, 0, SEEK_END);
        long len = ftell(fPtr);
        fseek(fPtr, 0, SEEK_SET);
        char *data = (char*) malloc (len+1);
        int _ = fread(data, 1, len, fPtr); _=_;
        fclose(fPtr);
        *outJson = cJSON_Parse(data);
        free(data);
        return outJson ? 0 : 1;
    }
    else
    {
        return -1;
    }

}

// save cJSON to json file
int json_to_file(const char *fname, cJSON *inJson)
{
    FILE *fPtr = fopen(fname, "w");
    if (fPtr)
    {
        fprintf(fPtr, "%s", cJSON_Print(inJson));
        fclose(fPtr);
        return 0;
    }
    else
    {
        return -1;
    }
}

// release cJSON root (auto mode)
void json_release(cJSON *inJson)
{
    cJSON_Delete(inJson);
}
