/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retriya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 11:37:07 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/21 11:37:14 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** 静的バッファから改行より前の部分を取り出して返す。
** 改行が見つかったら buf の残り部分だけを残す。
*/
static char	*extract_line(char **buf)
{
	char	*nl;
	char	*line;
	char	*remaining;

	nl = gnl_strchr(*buf, '\n');
	if (!nl)
	{
		line = gnl_substr(*buf, 0, gnl_strlen(*buf));
		free(*buf);
		*buf = NULL;
		return (line);
	}
	line = gnl_substr(*buf, 0, nl - *buf + 1);
	remaining = gnl_substr(*buf, nl - *buf + 1, gnl_strlen(nl + 1));
	free(*buf);
	*buf = remaining;
	return (line);
}

/*
** fdから読んだデータを静的バッファに溜め込む。
** 改行かEOFが来るまで読み続ける。
*/
static char	*fill_buffer(int fd, char *buf)
{
	char	tmp[BUFFER_SIZE + 1];
	int		n;

	n = read(fd, tmp, BUFFER_SIZE);
	while (n > 0)
	{
		tmp[n] = '\0';
		buf = gnl_strjoin(buf, tmp);
		if (!buf || gnl_strchr(buf, '\n'))
			break ;
		n = read(fd, tmp, BUFFER_SIZE);
	}
	if (n < 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = fill_buffer(fd, buf);
	if (!buf || buf[0] == '\0')
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	return (extract_line(&buf));
}
