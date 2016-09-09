#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

/* C99 Standard */

void initialize(Node* header)
{
    header = (Node*)malloc(sizeof(Node));
    if(header == NULL)
        exit(5);
    header->next = NULL;
}


size_t lenof(LList list)
{
    size_t count = 0;
    Node* p = list;

    for(; p->next != NULL; count++, p = p->next)
        ;

    return count;
}


LList create_list(unsigned int length, Song** data)
{
    Node* header = NULL;
    Node* new_node = NULL;

    header = (Node*)calloc(1, sizeof(Node));
    if(header == NULL)
        exit(5);

    header->next = NULL;

    Node* tail = header;
    unsigned int condition = 0;

    while(1)
    {
        if(condition == length)
            break;
        new_node = (Node*)calloc(1, sizeof(Node));
        new_node->data = data[condition];
        tail->next = new_node;
        tail = new_node;
        condition++;
    }
    tail->next = NULL;
    return header;
}


LList insert(LList list, unsigned int index, void* data)
{
    Node* previous_node = list;

    for(unsigned int i = 0; i < index; i++)
        previous_node = previous_node->next;

    Node* node_in = NULL;

    node_in = (Node*)malloc(sizeof(Node));
    node_in->data = data;
    node_in->next = previous_node->next;
    previous_node->next = node_in;

    return list;
}


Node* locate(LList list, void* data)
{
    Node* current_node = list->next;

    for(; current_node != NULL; current_node = current_node->next)
    {
        if(strncmp(current_node->data->name, data, strlen(data)) == 0)
            return current_node;
        if(strncmp(current_node->data->singer, data, strlen(data)) == 0)
            return current_node;
        if(strncmp(current_node->data->rate, data, strlen(data)) == 0)
            return current_node;
    }
    return NULL;
}


LList del(LList list, unsigned int index)
{
    Node* previous_node = list;

    for(unsigned int i = 0; i < index; i++)
        previous_node = previous_node->next;

    Node* tmp = (previous_node->next)->next;
    free(previous_node->next);
    previous_node->next = tmp;

    return list;
}


LList append(LList list, void* data)
{
    Node* previous_node = list;

    for(; previous_node->next != NULL; previous_node = previous_node->next)
        ;
    Node* new_node = NULL;

    new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    previous_node->next = new_node;

    return list;
}


void* pop(LList list, unsigned int index)
{
    void* ret = NULL;
    Node* previous_node = list;

    for(unsigned int i = 0; i < index; i++)
        previous_node = previous_node->next;
    ret = previous_node->next->data;

    del(list, index);
    return ret;
}


LList clear(LList list)
{
    Node* previous_node = list;

    for(; previous_node->next != NULL; previous_node = previous_node->next)
        previous_node->data = NULL;
    previous_node->data = NULL;

    return list;
}


LList sortlist(LList list)
{
         Node* p = NULL;
         p = list->next;

         size_t size = lenof(list);
         for (int i = 0; i < size; i++)
         {
             while (p->next != NULL)
             {
                 double a = atof(p->data->rate);
                 double b = atof(p->next->data->rate);
                 if (a > b)
                 {
                     Song* temp = NULL;
                     temp = p->data;
                     p->data = p->next->data;
                     p->next->data = temp;
                 }
                 p = p->next;
             }
             p = list->next;
         }

     return list;
 }


LList reverse(LList list)
{
    Node* current_node = list->next;
    Node* tmp = NULL;

    list->next = NULL;
    while(current_node != NULL)
    {
        tmp = current_node->next;
        current_node->next = list->next;
        list->next = current_node;
        current_node = tmp;
    }

    return list;
}


void printlist(LList list, unsigned int length)
{
    Node* node = NULL;

    unsigned int i = 0;
    for(node = list->next; node != NULL; node = node->next, i++)
    {
        if(i == length)
            break;
        printf("%u- %s-%s-%s\n", i+1, node->data->name, node->data->singer, node->data->rate);
    }
}


void printnode(Node* node)
{
    printf("====================\n");
    printf("  SONG NAME: ");
    printf("%s\n", node->data->name);
    printf("  SINGER: ");
    printf("%s\n", node->data->singer);
    printf("  RATE: ");
    printf("%s\n", node->data->rate);
    printf("====================\n");
}
