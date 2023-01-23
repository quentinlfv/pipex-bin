#include "pipex.h"

int check(int argc, char **argv)
{
    *argv += 1;
    if (argc != 5)
        return (0);
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    //int status;

    if (!check(argc, argv))
        return (0);
    pipex.fd[0] = open_doc(argv[1]);
    if (pipex.fd[0] < 0)
        return (0);
    pipex.fd[1] = open_doc(argv[4]);
    if (pipex.fd[1] < 0)
        return (close_doc(pipex.fd[0]), (0));
    pipex.path = path(envp);
    printf("%s\n", pipex.path);
    pipex.all_path = ft_split(pipex.path, ':');
    // pipe(pipex.pipefd);
    // pipex.pid[0] = fork();
    // pipex.pid[1] = fork();
    // close_doc(pipex.pipefd[0]);
    // close_doc(pipex.pipefd[1]);
    // waitpid(pipex.pid[0], &status, 0);
    // waitpid(pipex.pid[1], &status, 0);
    return (0);
}