#include <pthread.h>
#define MAX_THREADS 8

struct find_mt_rec_args
{
    int i;
    int n;
    int *A;
    int q;
};

void *find_mt_rec(void *args)
{
    int i = ((struct find_mt_rec_args *)args)->i;
    int n = ((struct find_mt_rec_args *)args)->n;
    int *A = ((struct find_mt_rec_args *)args)->A;
    int q = ((struct find_mt_rec_args *)args)->q;

    if (i >= n || A[i] > q)
        return NULL;
    if (A[i] == q)
    {
        // printf("found\n");
        return NULL;
    }

    if (i < MAX_THREADS - 1)
    {
        struct find_mt_rec_args args_1 = {2 * i + 1, n, A, q};
        struct find_mt_rec_args args_2 = {2 * i + 2, n, A, q};
        pthread_t tid;
        pthread_create(&tid, NULL, find_mt_rec, &args_1);
        find_mt_rec(&args_2);
        pthread_join(tid, NULL);
    }
    else
    {
        find_rec(2 * i + 2, n, A, q);
        find_rec(2 * i + 1, n, A, q);
    }
}

void find_mt(int n, int *A, int q)
{
    struct find_mt_rec_args args = {0, n, A, q};
    find_mt_rec(&args);
}
