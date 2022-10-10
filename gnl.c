#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *get_next_line(int fd) 
{
	char *s = malloc(10000);
	char *c = s;
    while (read(fd, c, 1) > 0 && *c++ != '\n')
	{
	}
	if (c > s)
		return (*c = 0, s);
	else
	{
		free (s);
		return (NULL);
	}
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*p;
	while ((p = get_next_line(fd)))
	{
		printf("%s", p);
		free (p);
	}
	return (0);
}
