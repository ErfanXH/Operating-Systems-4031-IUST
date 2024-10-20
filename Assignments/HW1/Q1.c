#include <stdlib.h>
#include <stdio.h>

struct person
{
    int weight;
    int rank;
    char *name;
};

int main()
{
    int people_count, weight_count;
    scanf("%d %d", &people_count, &weight_count);
    int temp;
    for (int i = 0; i < weight_count; i++)
    {
        scanf("%d", &temp);
    }
    struct person *persons;
    persons = (struct person *)malloc(people_count * sizeof(struct person));
    for (int i = 0; i < people_count; i++)
    {
        struct person per = {
            .name = (char *)malloc(20 * sizeof(char)),
            .weight = 0,
            .rank = 0};
        scanf("%s %d %d", per.name, &per.weight, &per.rank);
        persons[i] = per;
    }
    for (int i = 0; i < people_count; i++)
    {
        for (int j = 0; j < people_count - 1; j++)
        {
            if (persons[j].rank > persons[j + 1].rank)
            {
                struct person temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < people_count; i++)
    {
        for (int j = 0; j < people_count - 1; j++)
        {
            if (persons[j].weight > persons[j + 1].weight)
            {
                struct person temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < people_count; i++)
    {
        if (i % 3 == 0)
            printf("%d\n", persons[i].weight);
        printf("%d %s\n", persons[i].rank, persons[i].name);
    }
    return 0;
}