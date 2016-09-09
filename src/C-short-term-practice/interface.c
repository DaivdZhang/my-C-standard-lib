#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "llist.h"
#include "datautl.h"

/* C99 Standard */

void display_title(void);
void display_menu(void);
void display_ending(void);
void display_search(void);
void display_rank(void);
void display_userlist(void);
void diaplay_recommend(void);
int search(LList);
int rank(LList);
int userlist(void);
int recommend(LList);

void display_title(void)
{
    printf("#########################\n");
    printf("# Music Manager         #\n");
    printf("#       supported by C99#\n");
    printf("#########################\n\n");
}


void display_menu(void)
{
    printf("-1 search\n");
    printf("-2 the hot\n");
    printf("-3 music list\n");
    printf("-4 recommend\n");
    printf("-5 exit\n");
    printf("-------------------------\n");
}


void display_ending(void)
{
    printf("Thank you for your use.\n");
}

void display_search(void)
{
    printf("#########################\n");
    printf("#   search interface    #\n");
    printf("#                       #\n");
    printf("#    press 0 to quit    #\n");
    printf("#########################\n\n");
}


void display_rank(void)
{
    printf("#########################\n");
    printf("#   the top 10 music    #\n");
    printf("#                       #\n");
    printf("#    press 0 to quit    #\n");
    printf("#########################\n\n");
}

void display_userlist(void)
{
    printf("#########################\n");
    printf("#       Music List      #\n");
    printf("#                       #\n");
    printf("#    press 1 to add     #\n");
    printf("#    press 2 to delete  #\n");
    printf("#    press 3 to edit    #\n");
    printf("#    press 0 to quit    #\n");
    printf("#########################\n\n");
}


void diaplay_recommend(void)
{
    printf("#########################\n");
    printf("#     Recommend List    #\n");
    printf("#                       #\n");
    printf("#    press 0 to quit    #\n");
    printf("#########################\n\n");
}
int search(LList list)
{
    while(1)
    {
        char input_content[32];
        system("cls");
        fflush(stdin);
        display_search();
        printf("=================\n");
        printf("input keywords:\n");
        gets(input_content);
        if(strcmp(input_content, "0") == 0)
            break;
        printf("=================\n");
        printf("the results:\n\n");

        unsigned int flag = 0;
        Node* c_node = list;
        Node* p_node = NULL;
        Node* ret = NULL;
        for(; c_node != NULL; c_node = c_node->next)
        {   
            ret = locate(c_node, input_content);
            if(ret != NULL && ret != p_node)
            {
                printnode(ret);
                flag = 1;
                p_node = ret;
            }
        }
        if(flag == 0)
            printf("Not found! Please try again.\n");
        getchar();
    }
    return 0;
}


int rank(LList list)
{
    char ch = '1';
    system("cls");
    fflush(stdin);

    system("cls");
    display_rank();
    sortlist(list);
    reverse(list);
    printlist(list, 10);
    ch = getchar();
    if(ch == 's')
    {   
        for(unsigned int i = 0; i < 100; i++)
        {
            printf("^_^ ");
            if((i+1)%5 == 0)
                printf("\n");
        }
        Sleep(2016);
    }
    return 0;
}


int userlist(void)
{
    LList userlist = NULL;

    userlist = file_to_list("userdata.txt");
    while(1)
    {
        char ch = 'z';

        system("cls");
        display_userlist();
        printlist(userlist, lenof(userlist));
        ch = getchar();
        fflush(stdin);
        if(ch == '0')
            break;
        else if(ch == '1')
        {
            system("cls");
            char singer[64];
            char name[64];
            Song* _tmp = (Song*)calloc(1, sizeof(Song));

            printf("======================\n");
            printf("increase your list. ||\n");
            printf("======================\n");
            printf("input the name of the song:\n");
            scanf("%[^\n]", name);
            memmove(_tmp->name, name, strlen(name));

            fflush(stdin);
            printf("input the name of the singer:\n");
            scanf("%[^\n]", singer);
            memmove(_tmp->singer, singer, strlen(singer));
            memmove(_tmp->rate, "0.0", 8);
            append(userlist, _tmp);
        }
        else if(ch == '2')
        {
            int choice = 0;

            system("cls");
            printf("========================\n");
            printf("the current list is:  ||\n");
            printf("========================\n");
            printlist(userlist, lenof(userlist));
            printf("=============================\n");
            printf("WARNING: YOU CAN NOT REDO. ||\n");
            printf("=============================\n");
            printf("input the index of the song you want to delete:\n");
            printf("--");
            scanf("%d", &choice);
            fflush(stdin);
            if(choice > lenof(userlist) || choice - 1 < 0)
            {
                printf("NO SUCH A SONG.\nplease check again.\npress enter to continue.");
                getchar();
                continue;
            }
            del(userlist, choice-1);
        }
        else if(ch == '3')
        {
            int choice = 0;

            system("cls");
            printf("========================\n");
            printf("the current list is:  ||\n");
            printf("========================\n");
            printlist(userlist, lenof(userlist));
            printf("input the index of the song you want to edit:\n");
            printf("--");
            scanf("%d", &choice);
            fflush(stdin);
            if(choice > lenof(userlist) || choice - 1 < 0)
            {
                printf("NO SUCH A SONG.\nplease check again.\npress enter to continue.");
                getchar();
                continue;
            }

            Node* c_node = userlist->next;
            for(int i = 0; i < choice - 1; c_node = c_node->next, i++)
                ;
            printnode(c_node);
            char singer[64];
            char name[64];
            char rate[8];
            printf("input the name of the song:\n");
            scanf("%[^\n]", name);

            fflush(stdin);
            printf("input the name of the singer:\n");
            scanf("%[^\n]", singer);

            fflush(stdin);
            printf("input the rate:\n");
            scanf("%[^\n]", rate);

            memmove(c_node->data->name, name, strlen(name));
            memmove(c_node->data->singer, singer, strlen(singer));
            memmove(c_node->data->rate, rate, strlen(rate));
        }
    }


    FILE* fp = NULL;

    fp = fopen("userdata.txt", "w");
    if(fp == NULL)
        exit(707271);
    data_pickle(fp, userlist);
    fclose(fp);
    printf("userlist saved!\npress any key to continue.");
    getchar();
    return 0;
}


int recommend(LList list)
{
    system("cls");
    fflush(stdin);
    diaplay_recommend();

    LList userlist = NULL;
    Node* n = list->next;
    Node* pn = NULL;
    int flag = 0;

    userlist = file_to_list("userdata.txt");
    while(flag != 2)
    {
        for(; n != NULL; n = n->next)
        {
            if(rand()%8 == 1)
            {   
                if(atof(n->data->rate) < 4.0)
                    continue;
                if(locate(userlist, n->data->name) != NULL)
                    continue;
                if(n == pn)
                    continue;
                printnode(n);
                pn = n;
                flag++;
            }
            if(flag == 2)
                break;
        }
        n = list->next;
    }
    getchar();
    fflush(stdin);
    return 0;
}


int main(void)
{
    FILE* fp = NULL;

    char** data = NULL;
    LList list = NULL;
    size_t length = 0;
    char select = '0';
    Song** tmp = NULL;

    data = (char**)calloc(4096, sizeof(char*));
    if(data == NULL)
        exit(707171);

    fp = fopen("data.txt", "r");
    if(fp == NULL)
        exit(707271);
    length = freadlines(fp, data);
    fclose(fp);


    tmp = (Song**)calloc(length, sizeof(Song*));
    tmp = data_assemble(tmp, data, length);
    list = create_list(length, tmp);
    

    srand(time(NULL));

    while(1)
    {
        system("cls");
        display_title();
        display_menu();
        select = getchar();
        if(select == 'q')
            break;
        fflush(stdin);
        switch(select)
        {
            case '1': search(list); break;
            case '2': rank(list); break;
            case '3': userlist(); break;
            case '4': recommend(list); break;
            case '5': select = 'q'; break;
            default: break;
        }
        if(select == 'q')
            break;
    }
    display_ending();
    printf("press any key to continue.");
    getchar();
}
