/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:09:06 by vickovtu          #+#    #+#             */
/*   Updated: 2018/05/01 14:09:09 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				free_content(int fd, t_list **file)
{
	t_list			*cur_file;
	t_list			*prev;

	cur_file = *file;
	prev = NULL;
	while (cur_file)
	{
		if ((int)cur_file->content_size == fd)
			break ;
		prev = cur_file;
		cur_file = cur_file->next;
	}
	if (!prev && cur_file)
		*file = cur_file->next;
	else if (cur_file)
		prev->next = cur_file->next;
	if (cur_file)
	{
		free(cur_file->content);
		free(cur_file);
	}
}

static int			full_line(char **line, size_t len,
		char *tail, char **content)
{
	char			*tmp;
	size_t			content_len;

	content_len = len;
	if (tail)
		content_len = tail - *content;
	if (!(*line = ft_strnew(content_len)))
		return (-1);
	ft_strncpy(*line, *content, content_len);
	tmp = *content;
	if (!(*content = ft_strdup(tail ? tail + 1 : "")))
		return (-1);
	free(tmp);
	return (1);
}

static int			get_line(int fd, char **line, char *buf, char **content)
{
	int				ret;
	size_t			len;
	char			*tmp;
	char			*tail;

	while (!(tail = ft_strchr(*content, '\n')) &&
			(ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(tmp);
	}
	if (!(len = ft_strlen(*content)) && !ret)
		return (0);
	return (full_line(line, len, tail, content));
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*flows = NULL;
	char			*buf;
	t_list			*cur_file;
	int				res;

	if (fd < 0 || !line || BUFF_SIZE == 0 || !(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	cur_file = flows;
	while (cur_file)
	{
		if ((int)cur_file->content_size == fd)
			break ;
		cur_file = cur_file->next;
	}
	if (!cur_file)
	{
		ft_lstadd(&flows, ft_lstnew("", 1));
		flows->content_size = fd;
		cur_file = flows;
	}
	res = get_line(fd, line, buf, (char **)&cur_file->content);
	free(buf);
	if (!res)
		free_content(fd, &flows);
	return (res);
}
