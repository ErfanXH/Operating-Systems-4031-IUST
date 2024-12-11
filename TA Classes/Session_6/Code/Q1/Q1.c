#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char buffer[128];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    printf("File descriptors: %d, %d\n\n", pipefd[0], pipefd[1]);

    for (int i = 0; i < 4; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Child process
        {
            printf("Child %d Hi\n", getpid());
            close(pipefd[0]); // Close unused read end
            sprintf(buffer, "Child PID: %d\n", getpid());
            write(pipefd[1], buffer, sizeof(buffer));
            close(pipefd[1]); // Close write end after writing
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    close(pipefd[1]); // Close unused write end
    for (int i = 0; i < 4; i++)
    {
        wait(NULL); // Wait for each child to exit
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s", buffer);
    }
    close(pipefd[0]); // Close read end after reading

    return 0;
}
