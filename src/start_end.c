/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:09:04 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/11 14:09:15 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		ft_free(char *str, int i)
{
	free(str);
	str = NULL;
	return (i);
}

t_room	*ft_start_end(char *line)
{
	int		i;
	t_room	*start;

	i = 0;
	start = ft_list();
	while (line[i] != ' ')
		i++;
	start->room_name = ft_strnew(i);
	i = -1;
	while (line[++i] != ' ')
		start->room_name[i] = line[i];
	start->y = ft_atoi(&line[i]);
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ')
		i++;
	start->x = ft_atoi(&line[i]);
	return (start);
}

int		ft_start(t_param *lem)
{
	char	*line;
	t_room	*head;

	head = lem->room;
	line = ft_line();
	ft_putendl(line);
	if (!(ft_valid_str1(line)))
	{
		ft_putendl(YELLOW"WARNING : not valid start room data!"RESET);
		return (ft_free(line, 0));
	}
	lem->start = ft_start_end(line);
	lem->start->deep = 0;
	while (head != NULL)
	{
		if (ft_strcmp(head->room_name, lem->start->room_name) == 0 ||
			(head->x == lem->start->x && head->y == lem->start->y))
		{
			ft_putendl(YELLOW"WARNING : such data already exists!"RESET);
			return (ft_free(line, 0));
		}
		head = head->next;
	}
	return (ft_free(line, 1));
}

int		ft_end(t_param *lem)
{
	char	*line;
	t_room	*head;

	head = lem->room;
	line = ft_line();
	ft_putendl(line);
	if (!(ft_valid_str1(line)))
	{
		ft_putendl(YELLOW"WARNING : not valid end room data!"RESET);
		return (ft_free(line, 0));
	}
	lem->end = ft_start_end(line);
	lem->end->deep = -2;
	while (head != NULL)
	{
		if (ft_strcmp(head->room_name, lem->end->room_name) == 0 ||
			(head->x == lem->end->x && head->y == lem->end->y))
		{
			ft_putendl(YELLOW"WARNING : such data already exists!"RESET);
			return (ft_free(line, 0));
		}
		head = head->next;
	}
	return (ft_free(line, 1));
}

void	ft_add_start(t_param *lem)
{
	t_room *head;

	head = lem->room;
	if (head)
	{
		lem->start->next = head;
		while (head->next != NULL)
			head = head->next;
		head->next = lem->end;
		lem->end->before = head;
	}
	else
	{
		lem->start->next = lem->end;
		lem->end->before = lem->start;
	}
	lem->room = lem->start;
	ft_algo(lem);
}
