#include <unistd.h>
#include <sys/wait.h>
#define MAX_FORKS 8

void find_mp_rec(int i, int n, int *A, int q)
{
	if (i >= n || A[i] > q)
		_exit(0);
	if (A[i] == q)
	{
		// printf("found\n");
		_exit(0);
	}
	if (i < MAX_FORKS - 1)
	{
		int pid = fork();
		if (pid < 0)
		{
			perror("failed to fork");
			_exit(0);
		}
		else if (pid == 0)
			find_mp_rec(2 * i + 2, n, A, q);
		else
			find_mp_rec(2 * i + 1, n, A, q);
	}
	else
	{
		find_rec(2 * i + 2, n, A, q);
		find_rec(2 * i + 1, n, A, q);
	}
}

void find_mp(int n, int *A, int q)
{
	int pid = fork();
	if (pid < 0)
	{
		perror("failed to fork");
		return;
	}
	else if (pid == 0)
	{
		find_mp_rec(0, n, A, q);
		_exit(0);
	}
	while (wait(NULL) > 0)
		;
}
