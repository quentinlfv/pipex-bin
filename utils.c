#include "pipex.h"

int	open_doc(char *doc)
{
	int	fd;

	fd = open(doc, O_RDONLY);
	if (fd == -1)
	{
        printf("failed to open\n");
		return (-1);
	}
	return (fd);
}

int	close_doc(int fd)
{
	if (close(fd) < 0)
	{
        printf("failed to close\n");
		return (-1);
	}
	return (1);
}

int	strcmmp(const char *s1, const char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[j] == s1[i] && s2[j] && s1[j])
	{
		i++;
		j++;
	}
	if (s2[j] != 0)
		return (s1[i] - s2[j]);
	return (s1[i -1] - s2[j - 1]);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char			*ptr;
	unsigned int	i;
	int				a;

	ptr = (char *)s1;
	i = 0;
	a = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[0])
		{
			a = strcmmp(s1, s2, i);
			if (ft_strlen(s2) + i > n)
				a = 1;
			if (a == 0)
				return (ptr + i);
		}
		i++;
	}
	return (NULL);
}

int	strnbr(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char *) * (strnbr(s, c) + 1));
	if (!str)
		return (NULL);
	while (i < strnbr(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		while (s[j] != c && s[j])
		{
			k++;
			j++;
		}
		str[i++] = ft_substr(s, (j - k), k);
		k = 0;
	}
	str[i] = NULL;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(str, s1, len1 + 1);
	ft_strlcpy(str + len1, s2, len2 + 1);
	free((void *)s1);
	return (str);
}