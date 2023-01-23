#include "pipex.h"

char    *path(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if(ft_strnstr(envp[i], "PATH", 4))
            return(envp[i] + 5);
        i++;
    }
    return (NULL);
}

char    *find_path(char *cmd, char **all_path)
{
    char    *tmp;
    char    *command;
    int     i;

    i = 0;  
    while (all_path[i])
    {
        tmp = ft_strjoin(all_path[i], "/");
        command = ft_strjoin(tmp, cmd);
        // free(tmp);
        if (access(command, F_OK) == 0)
        {
            printf("path = %s\n", *all_path);
            return (command);
        }
        i++;
    }
    printf("c'est moche\n");
    return (NULL);
}

void    child_one(t_pipex pipex, char **argv, char **envp)
{
    char    *path_cmd;
    char    **arg_command;

    close_doc(pipex.pipefd[1]);
    dup2(pipex.pipefd[0], 1);
    close_doc(pipex.pipefd[0]);
    arg_command = ft_split(argv[2], ' ');
    // if (pipex.pipefd[0] == 0)
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
    close_doc(pipex.pipefd[1]);
    arg_command = ft_split(argv[3], ' ');
    // if (pipex.pipefd[1] == 0)
    path_cmd = find_path(arg_command[0], pipex.all_path);
    // exit(execve("PATH", argv[3], envp));
    execve(path_cmd, arg_command, envp);
}