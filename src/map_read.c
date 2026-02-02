#include "so_long.h"

static char	*append_buffer(char *data, size_t *len, size_t *cap,
					const char *buf, size_t n)
{
	char	*new_data;
	size_t	new_cap;

	if (*len + n + 1 > *cap)
	{
		new_cap = *cap;
		if (new_cap == 0)
			new_cap = 1024;
		while (*len + n + 1 > new_cap)
			new_cap *= 2;
		new_data = (char *)malloc(new_cap);
		if (!new_data)
			return (NULL);
		if (data)
			ft_memcpy(new_data, data, *len);
		free(data);
		data = new_data;
		*cap = new_cap;
	}
	ft_memcpy(data + *len, buf, n);
	*len += n;
	data[*len] = '\0';
	return (data);
}

char	*read_file(const char *path)
{
	int		fd;
	char	buf[4096];
	ssize_t	n;
	char	*data;
	size_t	len;
	size_t	cap;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	data = NULL;
	len = 0;
	cap = 0;
	while (1)
	{
		n = read(fd, buf, sizeof(buf));
		if (n <= 0)
			break ;
		data = append_buffer(data, &len, &cap, buf, (size_t)n);
		if (!data)
		{
			n = -1;
			break ;
		}
	}
	close(fd);
	if (n < 0 || (!data && len == 0))
	{
		free(data);
		return (NULL);
	}
	if (!data)
		return (ft_strdup(""));
	return (data);
}

char	**split_map(const char *content, int *height)
{
	char	**map;
	int		i;

	if (!content || content[0] == '\0')
		return (NULL);
	if (content[0] == '\n')
		return (NULL);
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n' && content[i + 1] == '\n')
			return (NULL);
		i++;
	}
	map = ft_split(content, '\n');
	if (!map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
		{
			free_map(map);
			return (NULL);
		}
		i++;
	}
	*height = i;
	return (map);
}
