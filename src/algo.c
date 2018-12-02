/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 20:47:11 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/13 20:47:28 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	ft_way_dop(t_param *lem, t_room *way, int i)
{
	t_room	*head;
	t_room	*head1;

	head = lem->room;
	while (head != NULL && --i >= 0)
	{
		head1 = lem->room;
		while (head1 != NULL)
		{
			if (head1->deep == i)
			{
				ft_way2(way, head1);
				break ;
			}
			head1 = head1->next;
		}
		head = head->next;
	}
}

void	ft_w(t_room *way)
{
	t_room	*way1;

	way1 = way;
	while (way1->before)
	{
		ft_putstr(W);
		ft_putstr(way1->room_name);
		ft_putstr("->");
		ft_putstr(RESET);
		way1 = way1->before;
	}
	ft_putstr(W);
	ft_putstr(way1->room_name);
	ft_putstr(RESET);
	ft_putchar('\n');
}

void	ft_way(t_param *lem, t_room *room)
{
	t_room	*way;
	t_room	*way1;
	int		i;

	i = room->deep;
	way = ft_way1(lem->end);
	way->ant_inside = lem->sum_ants;
	lem->way = way;
	way->next = ft_way1(room);
	way->next->before = way;
	ft_way_dop(lem, way, i);
	way1 = way;
	while (way->next)
		way = way->next;
	if (lem->w)
		ft_w(way);
	ft_print(lem, way->before, way1);
}

int		ft_algo1(t_param *lem, t_connect *con, t_room *head, int i)
{
	con = lem->con;
	while (con != NULL)
	{
		if (ft_strcmp(con->room_1->room_name, head->room_name) == 0 &&
			con->room_2->deep == -1)
			con->room_2->deep = i + 1;
		else if (ft_strcmp(con->room_2->room_name, head->room_name) == 0 &&
			con->room_1->deep == -1)
			con->room_1->deep = i + 1;
		else if ((ft_strcmp(con->room_2->room_name, head->room_name) == 0 ||
			ft_strcmp(con->room_1->room_name, head->room_name) == 0) &&
			(con->room_2->deep == -2 || con->room_1->deep == -2))
		{
			lem->end->deep = i + 1;
			ft_way(lem, head);
			return (0);
		}
		con = con->next;
	}
	return (1);
}

void	ft_algo(t_param *lem)
{
	int			i;
	t_room		*head;
	t_room		*head1;
	t_connect	*con;

	i = 0;
	con = NULL;
	head1 = lem->room;
	while (head1 != NULL)
	{
		head = lem->room;
		while (head != NULL)
		{
			if (i == head->deep && !ft_algo1(lem, con, head, i))
				return ;
			head = head->next;
		}
		i++;
		head1 = head1->next;
	}
	ft_putendl(RED"нет путей"RESET);
}
