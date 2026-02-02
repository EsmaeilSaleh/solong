/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esaleh <esaleh@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 07:48:05 by esaleh            #+#    #+#             */
/*   Updated: 2026/02/02 07:48:08 by esaleh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ensure_capacity(t_buf *buf, size_t add)
{
	size_t	new_cap;
	char	*new_data;

	if (buf->len + add + 1 <= buf->cap)
		return (1);
	new_cap = buf->cap;
	if (new_cap == 0)
		new_cap = 1024;
	while (buf->len + add + 1 > new_cap)
		new_cap *= 2;
	new_data = (char *)malloc(new_cap);
	if (!new_data)
		return (0);
	if (buf->data)
		ft_memcpy(new_data, buf->data, buf->len);
	free(buf->data);
	buf->data = new_data;
	buf->cap = new_cap;
	return (1);
}

static int	append_buffer(t_buf *buf, const char *src, size_t n)
{
	if (!ensure_capacity(buf, n))
		return (0);
	ft_memcpy(buf->data + buf->len, src, n);
	buf->len += n;
	buf->data[buf->len] = '\0';
	return (1);
}

char	*read_file(const char *path)
{
	int		fd;
	ssize_t	n;
	char	tmp[4096];
	t_buf	buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buf = (t_buf){0};
	n = 1;
	while (n > 0)
	{
		n = read(fd, tmp, sizeof(tmp));
		if (n > 0 && !append_buffer(&buf, tmp, (size_t)n))
			n = -1;
	}
	close(fd);
	if (n < 0 || (!buf.data && buf.len == 0))
		return (free(buf.data), NULL);
	if (!buf.data)
		return (ft_strdup(""));
	return (buf.data);
}
