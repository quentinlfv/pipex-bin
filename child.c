#include "pipex.h"

char    *path(char **envp)
{
    char   *path;

    while (*envp)
    {
        if(ft_strnstr(*envp, "PATH", 4))
            return(*envp + 5);
        *envp++;
    }
    return (NULL);
}

char    *find_path(char *cmd, char **all_path)
{
    char    *tmp;
    char    *command;

    while (*all_path)
    {
        tmp = ft_strjoin(*all_path, "/");
        command = ft_strjoin(tmp, cmd);
        if (access(cmd, F_OK) == 0)
            return (*all_path);
        *all_path++;
    }
}

void    child_one(t_pipex pipex, char **argv, char **envp)
{
    char *path_cmd;

    close_doc(pipex.pipefd[1]);
    dup2(pipex.pipefd[0], 1);
    close(pipex.pipefd[0]);
    path_cmd = find_path(argv[2], pipex.all_path);
    // exit(execve(path_cmd, argv[2], envp));
    execve(path_cmd, argv[2], envp);
}

void    child_two(t_pipex pipex, char **argv, char **envp)
{
    char    *path_cmd;

    close_doc(pipex.pipefd[0]);
    dup2(pipex.pipefd[1], 0);
    close(pipex.pipefd[1]);
    path_cmd = find_path(argv[3], pipex.all_path);
    // exit(execve("PATH", argv[3], envp));
    execve(path_cmd, argv[3], envp);
}