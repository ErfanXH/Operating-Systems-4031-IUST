#include <stdio.h>
#include <stdlib.h>
#include "normal.c"
#include "multi-thread.c"
#include "multi-process.c"
#include <sys/time.h>

long current_us()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

int run_and_track(void (*fn)(int n, int *A, int q), int n, int *A, int q)
{
    long start = current_us();
    fn(n, A, q);
    long end = current_us();
    return end - start;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", A + i);
    int q;
    scanf("%d", &q);

    time_t dur_n = run_and_track(find, n, A, q);
    printf("normal search took %ld\n", dur_n);
    
    time_t dur_mt = run_and_track(find_mt, n, A, q);
    printf("multi thread search took %ld\n", dur_mt);
    
    time_t dur_mp = run_and_track(find_mp, n, A, q);
    printf("multi process search took %ld\n", dur_mp);
}
