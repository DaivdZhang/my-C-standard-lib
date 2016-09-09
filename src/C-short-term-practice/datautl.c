#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datautl.h"
#include "llist.h"

/* C99 Standard */

unsigned int freadlines(FILE* fp, char** dataarr)
{
    void* pdata = NULL;
    unsigned int i = 0;
    for(;; i++)
    {
        char* tmp = (char*)calloc(128, sizeof(char));
        pdata = fgets(tmp, 128, fp);
        if(pdata == NULL)
            break;
        char* data = (char*)calloc(strlen(tmp), sizeof(char));
        memmove(data, tmp, strlen(tmp)-1);
        pdata = data;
        dataarr[i] = pdata;
        free(tmp);
    }
    return i;
}

Song** data_assemble(Song** container, char** dataarr, unsigned int length)
{
    char** names = (char**)calloc(length, sizeof(char*));
    char** singers = (char**)calloc(length, sizeof(char*));
    char** rates = (char**)calloc(length, sizeof(char*));

    for(unsigned int i = 0; i < length; i++)
    {
        char** sstr = (char**)calloc(3, sizeof(char*));
        strsplit(sstr, dataarr[i], ';');
        names[i] = sstr[0];
        singers[i] = sstr[1];
        rates[i] = sstr[2];
    }

    /*char** _data = (char**)calloc(length*3, sizeof(char*));
    for(unsigned int i = 0; i < length; i++)
    {
        _data[i*3] = names[i];
        printf("%s\n", _data[i*3]);
        _data[i*3+1] = singer[i];
        printf("%s\n", _data[i*3+1]);
        _data[i*3+2] = rates[i];
        printf("%s\n", _data[i*3+2]);
    }*/

    /*Song** data = (Song**)calloc(length, sizeof(Song*));*/
    for(unsigned int i = 0; i < length; i++)
    {
        container[i] = (Song*)calloc(1, sizeof(Song));
        memmove(container[i]->name, names[i], strlen(names[i]));
        memmove(container[i]->singer, singers[i], strlen(singers[i]));
        memmove(container[i]->rate, rates[i], strlen(rates[i]));
    }
    return container;
}


int data_pickle(FILE* fp, LList list)
{
    Node* node = list->next;

    for(; node != NULL; node = node->next)
    {
        char* line = (char*)calloc(128, sizeof(char));
        if(line == NULL)
            exit(50);
        memmove(line, node->data->name, strlen(node->data->name));
        strcat(line, ";");
        strcat(line, node->data->singer);
        strcat(line, ";");
        strcat(line, node->data->rate);
        strcat(line, ";");
        strcat(line, "\n");
        fputs(line, fp);
        free(line);
    }
    return 0;
}


LList file_to_list(char* filename)
{
    FILE* fp = NULL;
    char** data = NULL;
    LList _list = NULL;
    size_t length = 0;
    Song** tmp = NULL;

    data = (char**)calloc(2048, sizeof(char*));
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("failed to open file.\n");
        exit(707271);
    }   
    length = freadlines(fp, data);
    fclose(fp);

    tmp = (Song**)calloc(length, sizeof(Song*));
    tmp = data_assemble(tmp, data, length);
    _list = create_list(length, tmp);

    return _list;
}


char** strsplit(char** sstr, char* str, char d)
{
    char* tp = str;
    char** tpsstr = sstr;
    char* start = str;
    unsigned int length = 0;
    unsigned int count = 0;

    while(*tp != '\0')
    {
        if(*tp == d)
        {
            char* tmp = (char*)calloc(length+1, sizeof(char));
            memmove(tmp, start, length);
            *tpsstr = tmp;
            tpsstr++;
            length = 0;
            start = tp + 1;
        }
        else
            length++;
        tp++;
        count++;
    }
    return sstr;
}
