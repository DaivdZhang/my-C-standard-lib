#ifndef _LLIST_H
#define _LLIST_H

/* C99 Standard */

struct song
{
    char name[64];
    char singer[64];
    char rate[8];
};

typedef struct song Song;

struct _node
{
    Song* data;
    struct _node* next;
};


typedef struct _node Node;
typedef struct _node* LList;

void initialize(Node*);
size_t lenof(LList);
LList create_list(unsigned int, Song**);
LList insert(LList, unsigned int, void*);
Node* locate(LList, void*);
LList del(LList, unsigned int);
LList append(LList, void*);
void* pop(LList, unsigned int);
LList clear(LList);
LList sortlist(LList);
LList reverse(LList);
void printlist(LList, unsigned int);
void printnode(Node*);

#endif // _LLIST_H
