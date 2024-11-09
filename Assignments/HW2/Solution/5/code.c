#include <stdio.h>

int main () {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        long long s;
        int x;
        scanf("%d", &x);
        if (i)
            s += x;
        else
            s = x;
        printf("%lld\n", s);
    }
}
