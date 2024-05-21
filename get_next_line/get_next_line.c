# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (i < srcsize && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src) + 1;
	dst = malloc(len);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, len);
	return (dst);
}

char	*ft_strjoin(char *s1, const char *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = len;
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*save;
	int			nbytes;
	int			to_copy;

	line = ft_strdup(buffer);
	while (!(ft_strchr(line, '\n')) && ((nbytes = read(fd, buffer, BUFFER_SIZE)) > 0))
	{
		buffer[nbytes] = '\0';
		line = ft_strjoin(line, buffer, nbytes);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	save = ft_strchr(line, '\n');
	if (save != NULL)
	{
		to_copy = save - line + 1;
		ft_strlcpy(buffer, save + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		ft_strlcpy(buffer, "", BUFFER_SIZE + 1);
	}
	line[to_copy] = '\0';
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main (void)
{
	int fd;
	char*line;

	fd = open("../test", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return(1);
	}
	while (1)
	{
		printf("\n Read text :\n");
		line = get_next_line(fd);
		if (!line)
		{
			printf("Reached end of the file or error.\n");
			break ;
		}
		printf("Line read : %s", line);
		free(line);
	}

}*/
