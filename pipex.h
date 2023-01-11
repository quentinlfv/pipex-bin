#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_pipex
{
    pid_t   pid[2];
    int     fd[2];
    int     pipefd[2];
    char    *path;
    char    **all_path;

}t_pipex;

/* main.c */
int check(int argc, char **argv);

/* child.c */
char    *path(char **envp);
char    *find_path(char *cmd, char **all_path);
void    child_one(t_pipex pipex, char **argv, char **envp);
void    child_two(t_pipex pipex, char **argv, char **envp);

/* utils.c */
int	open_doc(char *doc);
int	close_doc(int fd);
static int	strcmmp(const char *s1, const char *s2, int i);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
static int	strnbr(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif 