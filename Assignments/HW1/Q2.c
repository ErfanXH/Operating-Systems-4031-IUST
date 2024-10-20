#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool CommandIsSwap(char *);
bool CommandIsAdd(char *);
bool CommandIsDeletion(char *);

int main()
{
    int people_count;
    scanf("%d", &people_count);
    char pre_modification_names[people_count][100];
    for (int i = 0; i < people_count; i++)
    {
        scanf("%s", pre_modification_names[i]);
    }
    int operation_count;
    scanf("%d", &operation_count);
    int maximum_possible_length = people_count + operation_count;
    char post_modification_names[maximum_possible_length][100];
    for (int i = 0; i < people_count; i++)
    {
        // copy names into post_modification_names
        strcpy(post_modification_names[i], pre_modification_names[i]);
    }
    char swap[10] = "swap";
    char add[10] = "add";
    for (int i = 0; i < operation_count; i++)
    {
        char command[10];
        scanf("%s", command);
        if (CommandIsDeletion(command))
        {
            char name[100];
            scanf("%s", name);
            int flag = 0;
            for (int i = 0; i < people_count; i++)
            {
                if (strcmp(post_modification_names[i], name) == 0 && flag == 0)
                {
                    flag = 1;
                }
                if (flag == 1)
                {
                    strcpy(post_modification_names[i], post_modification_names[i + 1]);
                }
            }
            people_count--;
        }
        else if (CommandIsAdd(command))
        {
            char name[100];
            scanf("%s", name);
            int place;
            scanf("%d", &place);
            char temp[100];
            for (int i = people_count; i >= place; i--)
            {
                strcpy(post_modification_names[i + 1], post_modification_names[i]);
            }
            strcpy(post_modification_names[place], name);
            ++people_count;
        }
        else if (CommandIsSwap(command))
        {
            char name1[100];
            char name2[100];
            int index1;
            int index2;
            scanf("%s", name1);
            scanf("%s", name2);
            for (int i = 0; i < people_count; i++)
            {
                if (strcmp(post_modification_names[i], name1) == 0)
                {
                    index1 = i;
                }
                if (strcmp(post_modification_names[i], name2) == 0)
                {
                    index2 = i;
                }
            }
            char temp[100];
            strcpy(temp, post_modification_names[index1]);
            strcpy(post_modification_names[index1], post_modification_names[index2]);
            strcpy(post_modification_names[index2], temp);
        }
    }
    for (int i = 0; i < people_count - 1; i++)
    {
        printf("%s ", post_modification_names[i]);
    }
    printf("%s", post_modification_names[people_count - 1]);
    return 0;
}

bool CommandIsSwap(char *command)
{
    return strcmp(command, "swap") == 0;
}

bool CommandIsAdd(char *command)
{
    return strcmp(command, "add") == 0;
}

bool CommandIsDeletion(char *command)
{
    return strcmp(command, "delete") == 0;
}