#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include "./pcs/cJSON.h"

#define DOWNLOAD_LIST_PATH "./download.json"
#define UPLOAD_LIST_PATH "./upload.json"
#define JSON_LEN 100

int downloadList(char *str)
{
    FILE *file = fopen(DOWNLOAD_LIST_PATH,"r");
    char p;
    if(file ==NULL)
    {
        return -1;
    }
    while((p=getc(file))!=EOF)
    {
        *str = p; 
        str ++;
        //printf("%c",p);
    }
    fclose(file);
    return 1;
}
char *getPathFromJSON(cJSON *json)
{
    cJSON *item =   cJSON_GetObjectItem(json,"path");
    if(!item)
    {
        printf("item null");
        return NULL;
    }
    return item->valuestring;
}
int getJSONFromFile(cJSON **json)
{
    char *str;
    FILE *file;
    char byte,*ptr;
    //call download code to download download.json
    //get stream from file 
    str = malloc(sizeof(char)*JSON_LEN);
    if(!str)
    {
        printf("get json memory fail");
    }
    file = fopen(DOWNLOAD_LIST_PATH,"r+");
    if(!file)
    {
        printf("json open fail");
        free(str);
        return -1;    
    }
    //parse download.json 
    ptr = str;
    while((byte = getc(file))!=EOF)
    {
        *ptr = byte;
        ptr ++;
    }   
    //printf("%s \n",str);
    *json = NULL; 
    *json = cJSON_Parse(str);
    if(!(*json))
    {
        printf("get Json parse fail \n");
        fclose(file);
        free(str);
        return -1;
    }
    fclose(file);
    free(str);
    return 1;
}
cJSON * refreshUploadJSON(cJSON *src)
{
    cJSON * dest;
    dest = cJSON_CreateObject();
    cJSON_AddItemToObject(dest,"path",cJSON_CreateString("make"));
    cJSON_AddItemToObject(dest,"status",cJSON_CreateString("2"));
    cJSON_AddItemToObject(dest,"curtime",cJSON_CreateString("2"));
    cJSON_AddItemToObject(dest,"speed",cJSON_CreateString("2 kb"));
    return dest;
}
/* create upload.json to upload*/
int createUPloadJSON(cJSON *json)
{
    FILE * file = fopen(UPLOAD_LIST_PATH,"w+");
    char *s = NULL;
    if(!file)
    {
        printf(" upload open fail");
        return -1;
    }   
    s = cJSON_Print(json);
    //while(s !="\0")
    {
        fputs(s,file);
    }
    fclose(file);
    return 1;
}
int getPathAfterDwnFile(char *path)
{
    char *str;
    cJSON *json;
    if(getJSONFromFile(&json)== -1)
    {
        printf("Get JSON fail");
        return  -1;
    }
    str = getPathFromJSON(json);
    if(!str)
    {
        printf("get item str fail");
        cJSON_Delete(json);
        return -1;
    }

    memcpy(path , str ,strlen(str)); 
    cJSON_Delete(json);
    return 1;
}

#if 1
int main()
{
    char path[JSON_LEN]={0};
    cJSON *json;//*item;
    cJSON *dest;
/*
    str = malloc(sizeof(char)*100);
    if(!str)
    {
        printf("alloc fail");
        return -1;
    }
    if(downloadList(str) != 1)
    {
        return -1;
    }
    printf("%s",str);
    json = cJSON_Parse(str);
    if(!json)
    {
        printf("JSON parse fail \n");
        return -1;
    }
    if(getJSONFromServer(&json)== -1)
    {
        printf("Get JSON fail");
        return  -1;
    }
    //printf("Get JSON suscess \n");
    item = cJSON_GetObjectItem(json,"path");
    if(!item)
    {
        printf("JSON ITEM parse fail \n");
        return -1;
    }
*/
   // path = getPathFromJSON(json);
    system("rm aa.txt");

    if(getPathAfterDwnFile(path)==-1)
    {
        printf("listen fail");
        return -1;
    }
    printf("%s\n",path);
    dest = refreshUploadJSON(json);
    //printf("%s\n",cJSON_Print(dest));
    //printf("%s\n",str);
    createUPloadJSON(dest);
    //cJSON_Delete(json);
    cJSON_Delete(dest);
}
#endif
