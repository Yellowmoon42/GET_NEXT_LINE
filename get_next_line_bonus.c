/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faacar <faacar@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:53:25 by faacar            #+#    #+#             */
/*   Updated: 2023/07/27 14:50:01 by faacar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_to_left_str(char *str, char *buf)
{
	char	*res;

	if (!str && buf)
		return (ft_strdup(buf));
	res = ft_strjoin(str, buf);
	ft_free_str(&str, 0);
	return (res);
}

static int	ft_have_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_get_line(char *str)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_new_left_str(char *str)
{
	size_t	i;
	char	*res;

	i = 0;
	while (str[i] != '\n')
		i++;
	if (str[i + 1] == '\0')
		return (ft_free_str(&str, 0));
	res = ft_substr(str, i + 1, ft_strlen(str));
	ft_free_str(&str, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*str[5000];
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_str(&str[fd], 0));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret <= 0 && !str[fd]) || ret == -1)
			return (ft_free_str(&str[fd], 0));
		buf[ret] = '\0';
		str[fd] = ft_read_to_left_str(str[fd], buf);
		if (ft_have_nl(str[fd]))
		{
			line = ft_get_line(str[fd]);
			if (!line)
				return (ft_free_str(&str[fd], 0));
			return (str[fd] = ft_new_left_str(str[fd]), line);
		}
	}
	return (ft_free_str(&str[fd], 1));
}
