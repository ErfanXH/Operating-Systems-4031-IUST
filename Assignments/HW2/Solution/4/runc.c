#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2)
        exit(1);

    char *last_slash = NULL;
    for (char *c = argv[1]; *c != '\0'; c++)
        if (*c == '/')
            last_slash = c;
    
    if (last_slash != NULL) {
        *last_slash = '\0';       // "folder/code.c\0" becomes "folder\0code.c\0"
        chdir(argv[1]);           // chdir accepts a null terminated string. here, argv[1] ends at first \0
        argv[1] = last_slash + 1; // argv[1] is a pointer to start of string. move it to start of filename
    }

    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        argv[0] = "gcc";
        execvp("gcc", argv);
        _exit(1); // if process reaches here, execvp has failed
    }

    waitpid(pid, &status, 0);

    if (status != 0)
        exit(-1);

    char *argument_list[] = {"./a.out", NULL};
    execvp(argument_list[0], argument_list);
    exit(1); // if process reaches here, execvp has failed
}