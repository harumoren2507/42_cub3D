/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retoriya <retriya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 11:37:07 by retoriya          #+#    #+#             */
/*   Updated: 2026/06/21 11:37:14 by retoriya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= gnl_strlen(s))
		len = 0;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*out;
	size_t	len;
	size_t	i;
	size_t	j;

	len = gnl_strlen(s1) + gnl_strlen(s2);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	free(s1);
	return (out);
}
