/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 19:06:36 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/26 19:06:47 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_ant	*ft_ant(t_ant *ant, t_room *way, int i)
{
	t_ant *an;
	t_ant *head;

	head = ant;
	an = (t_ant *)malloc(sizeof(t_ant));
	an->way = way;
	an->next = NULL;
	an->pre = NULL;
	an->num = i;
	if (ant == NULL)
		head = an;
	else
	{
		while (ant->next)
			ant = ant->next;
		ant->next = an;
		ant->pre = ant;
	}
	return (head);
}

int		ft_print2(int i, t_param *lem, t_ant *a, t_room *w)
{
	int b;

	b = 1;
	a = lem->ant;
	while (b <= i && a)
	{
		if (a->way && a->num)
		{
			ft_putstr(GREEN"L");
			ft_putnbr(a->num);
			ft_putstr("->");
			ft_putstr(a->way->room_name);
			ft_putstr("; ");
			ft_putstr(RESET);
			if (a->num == w->ant_inside && a->way->room_name == w->room_name)
				return (0);
		}
		if (a->way->before)
			a->way = a->way->before;
		else
			a->num = 0;
		b++;
		a = a->next;
	}
	return (1);
}

void	ft_print(t_param *lem, t_room *way, t_room *way1)
{
	t_ant	*ant1;
	int		i;

	i = 0;
	ant1 = NULL;
	if (way->room_name == way1->room_name)
		while (++i <= lem->sum_ants)
		{
			ft_putstr(GREEN"L");
			ft_putnbr(i);
			ft_putstr("->");
			ft_putstr(way1->room_name);
			ft_putstr("; ");
			ft_putstr(RESET);
		}
	else
	{
		while (++i <= lem->sum_ants)
			lem->ant = ft_ant(lem->ant, way, i);
		i = 0;
		while (ft_print2(++i, lem, ant1, way1))
			ft_putchar('\n');
	}
	ft_putchar('\n');
}
