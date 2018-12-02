/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:24:58 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/12 12:25:55 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room		*ft_list(void)
{
	t_room	*list;

	list = (t_room *)malloc(sizeof(t_room));
	list->room_name = NULL;
	list->y = 0;
	list->x = 0;
	list->deep = -1;
	list->ant_inside = 0;
	list->next = NULL;
	list->before = NULL;
	return (list);
}

t_connect	*ft_list1(void)
{
	t_connect	*list;

	list = (t_connect *)malloc(sizeof(t_connect));
	list->room_1 = NULL;
	list->room_2 = NULL;
	list->next = NULL;
	list->before = NULL;
	return (list);
}

t_room		*ft_way1(t_room *room)
{
	t_room	*list;

	list = (t_room *)malloc(sizeof(t_room));
	list->room_name = room->room_name;
	list->y = room->y;
	list->x = room->x;
	list->deep = room->deep;
	list->ant_inside = room->ant_inside;
	list->next = NULL;
	list->before = NULL;
	return (list);
}

void		ft_way2(t_room *way, t_room *room)
{
	t_room	*list;

	while (way->next)
		way = way->next;
	list = (t_room *)malloc(sizeof(t_room));
	way->next = list;
	list->room_name = room->room_name;
	list->y = room->y;
	list->x = room->x;
	list->deep = room->deep;
	list->ant_inside = room->ant_inside;
	list->next = NULL;
	list->before = way;
	return ;
}

t_room		*ft_back(t_room *room)
{
	free(room->room_name);
	free(room);
	return (NULL);
}
