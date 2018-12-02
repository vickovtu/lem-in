/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:33:58 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/12 12:34:07 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		ft_valid_connect_str(char *line, t_param *lem)
{
	char		**str;
	t_connect	*con;
	t_connect	*conhead;

	conhead = lem->con;
	if (ft_strchr(line, '-') == 0 || ft_dash(line) == 0)
		return (0);
	str = ft_strsplit(line, '-');
	con = ft_con(str, lem);
	if (!con->room_1 || !con->room_2)
	{
		free(con);
		return (0);
	}
	if (!lem->con)
		conhead = con;
	else
	{
		while (lem->con->next != NULL)
			lem->con = lem->con->next;
		lem->con->next = con;
		con->before = lem->con;
	}
	lem->con = conhead;
	return (1);
}

int		ft_valid_s_e(t_room *ph, t_param *lem)
{
	if (ph == NULL)
	{
		ft_putendl(YELLOW"Warning: error room!"R);
		return (0);
	}
	if (lem->start && (ft_strcmp(ph->room_name, lem->start->room_name) == 0 ||
		(ph->y == lem->start->y && ph->x == lem->start->x)))
	{
		free(ph->room_name);
		free(ph);
		ft_putendl(YELLOW"Warning: such data is already in the start room"R);
		return (0);
	}
	if (lem->end && (ft_strcmp(ph->room_name, lem->end->room_name) == 0 ||
		(ph->y == lem->end->y && ph->x == lem->end->x)))
	{
		free(ph->room_name);
		free(ph);
		ft_putendl(YELLOW"Warning: such data is already in the end room"RESET);
		return (0);
	}
	return (1);
}

int		ft_valid_room(t_room *ph, t_room *room)
{
	if (ft_strcmp(ph->room_name, room->room_name) == 0 || (ph->y == room->y &&
		ph->x == room->x))
	{
		free(room->room_name);
		free(room);
		ft_putendl(YELLOW"Warning: room with such data already exists"RESET);
		return (0);
	}
	else
		return (1);
}

t_room	*ft_room_fill(char *line)
{
	int		i;
	t_room	*room;
	int		flag;

	i = 0;
	flag = 0;
	room = ft_list();
	while (line[i] != ' ')
		i++;
	room->room_name = ft_strnew(i);
	i = -1;
	while (line[++i] != ' ')
		room->room_name[i] = line[i];
	room->y = ft_atoi(&line[i]);
	while (line[++i] != ' ')
		if (ft_isdigit(line[i]) == 0)
			flag++;
	room->x = ft_atoi(&line[i]);
	while (line[++i])
		if (ft_isdigit(line[i]) == 0)
			flag++;
	if (flag)
		return (ft_back(room));
	return (room);
}

int		ft_room(char *line, t_param *lem)
{
	t_room	*room;
	t_room	*head;

	head = lem->room;
	room = ft_room_fill(line);
	if (ft_valid_s_e(room, lem) == 0)
		return (0);
	if (!lem->room)
		head = room;
	else
	{
		while (lem->room->next != NULL)
		{
			if (ft_valid_room(lem->room, room) == 0)
				return (0);
			lem->room = lem->room->next;
		}
		if (ft_valid_room(lem->room, room) == 0)
			return (0);
		lem->room->next = room;
		room->before = lem->room;
	}
	lem->room = head;
	return (1);
}
