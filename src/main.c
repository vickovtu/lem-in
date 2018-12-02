/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:20:27 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/04 17:25:21 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		ft_ft(t_connect *con, char **str, t_param *lem)
{
	if (lem->start && ft_strcmp(str[0], lem->start->room_name) == 0)
		con->room_1 = lem->start;
	if (lem->end && ft_strcmp(str[0], lem->end->room_name) == 0)
		con->room_1 = lem->end;
	if (lem->start && ft_strcmp(str[1], lem->start->room_name) == 0)
		con->room_2 = lem->start;
	if (lem->end && ft_strcmp(str[1], lem->end->room_name) == 0)
		con->room_2 = lem->end;
}

t_connect	*ft_con(char **str, t_param *lem)
{
	t_connect	*con;
	t_room		*head;

	con = ft_list1();
	head = lem->room;
	ft_ft(con, str, lem);
	if (!con->room_1 || !con->room_2)
		while (head != NULL && head->room_name)
		{
			if (ft_strcmp(str[0], head->room_name) == 0)
				con->room_1 = head;
			if (ft_strcmp(str[1], head->room_name) == 0)
				con->room_2 = head;
			if (con->room_1 && con->room_2)
				break ;
			head = head->next;
		}
	free(str[0]);
	free(str[1]);
	free(str);
	return (con);
}

int			ft_hesh(t_param *lem, char *line)
{
	if (ft_strcmp(line, "##start") == 0 && !(lem->start))
		return (ft_start(lem));
	else if (ft_strcmp(line, "##end") == 0 && !(lem->end))
		return (ft_end(lem));
	else if (line[0] == '#' && (line[1] != '#' || !line[1]))
		return (1);
	ft_putendl(YELLOW"Warnind: not valid string using"RESET);
	return (0);
}

void		ft_get(t_param *lem, char *line, int flag)
{
	while (flag && (get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		if (ft_strlen(line) == 0)
			break ;
		if (!lem->sum_ants)
			flag = ft_sum_ants(line, lem);
		else if (ft_strchr(line, '#'))
			flag = ft_hesh(lem, line);
		else if (ft_valid_str(line, lem) == 0)
			flag = 0;
		free(line);
	}
}

int			main(int argv, char **argc)
{
	t_param		lem;
	char		*line;
	int			flag;

	ft_bzero(&lem, sizeof(lem));
	flag = 1;
	line = NULL;
	if (argv > 1 && ((argc[1] && ft_strstr(argc[1], "-l")) ||
		(argc[2] && ft_strstr(argc[2], "-l"))))
		lem.leaks = 1;
	if (argv > 1 && ((argc[1] && ft_strstr(argc[1], "-w")) ||
		(argc[2] && ft_strstr(argc[2], "-w"))))
		lem.w = 1;
	ft_get(&lem, line, flag);
	if (lem.start && lem.end && lem.con)
		ft_add_start(&lem);
	else
		ft_putstr(RED"ERROR!\n"RESET);
	if (lem.leaks)
		system("leaks lemIn");
	return (0);
}
