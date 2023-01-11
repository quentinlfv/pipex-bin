#include "pipex.h"

char    *path(char **envp)
{
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
        free(tmp);
        if (access(cmd, F_OK) == 0)
        {
            printf("path = %s\n", *all_path);
            return (command);
        }
        *all_path++;
    }
    return (NULL);
}

void    child_one(t_pipex pipex, char **argv, char **envp)
{
    char    *path_cmd;
    char    **arg_command;

    close_doc(pipex.pipefd[1]);
    dup2(pipex.pipefd[0], 1);
    close(pipex.pipefd[0]);
    arg_command = ft_split(argv[2], ' ');
    path_cmd = find_path(arg_command[0], pipex.all_path);
    // exit(execve(path_cmd, argv[2], envp));
    execve(path_cmd, arg_command, envp);
}

void    child_two(t_pipex pipex, char **argv, char **envp)
{
    char    *path_cmd;
    char    **arg_command;

    close_doc(pipex.pipefd[0]);
    dup2(pipex.pipefd[1], 0);
    close(pipex.pipefd[1]);
    arg_command = ft_split(argv[3], ' ');
    path_cmd = find_path(arg_command[0], pipex.all_path);
    // exit(execve("PATH", argv[3], envp));
    execve(path_cmd, arg_command, envp);
}