#include "cJSON.h"
#include "stdio.h"
int main()
{
    cJSON *item;
    cJSON *json;
    char *ptr="{\"name\":\"Bill Gates\",\
		\"street\":\"Fifth Avenue New York 666\",\
		\"age\":56,\
		\"phone\":\"555 1234567\"}";
    printf("%s \n",ptr);
    json = cJSON_Parse(ptr);
    item = cJSON_GetObjectItem(json,"name");
    if(item)
    {
	printf("%s \n",item->valuestring);
    }

}
