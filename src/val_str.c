/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 20:09:08 by vickovtu          #+#    #+#             */
/*   Updated: 2018/09/12 20:09:21 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		ft_valid_str1(char *line)
{
	int count;
	int i;

	if (line[0] == '#' || line[0] == 'L' || line[0] < 32 || !line[0])
		return (0);
	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			++count;
		if (line[i] == '-')
			return (0);
	}
	if (count != 2)
		return (0);
	return (1);
}

char	*ft_line(void)
{
	char *line;

	while (get_next_line(0, &line))
	{
		if (line[0] == '#' && line[1] != '#')
		{
			free(line);
			continue;
		}
		else
			break ;
	}
	return (line);
}

int		ft_valid_str(char *line, t_param *lem)
{
	int count;
	int count1;
	int i;

	count = 0;
	count1 = 0;
	i = -1;
	if (line[0] == '#' || line[0] == 'L' || line[0] < 32 || !line[0])
		return (0);
	while (line[++i])
	{
		if (line[i] == ' ')
			++count;
		if (line[i] == '-')
			++count1;
	}
	if ((count != 2 && count != 0) || (count1 != 0 && count1 != 1))
		return (write(1, "Warning: not valid string\n", 26) * 0);
	else if (count == 2 && ft_room(line, lem) == 0)
		return (0);
	else if (count == 0 && ft_valid_connect_str(line, lem) == 0)
		return (write(1, "Warning: not valid communication rooms\n", 39) * 0);
	return (1);
}

int		ft_dash(char *line)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (line[++i])
		if (line[i] == '-' && line[i + 1] != '\0')
			++count;
	if (count == 1)
		return (1);
	else
		return (0);
}

int		ft_sum_ants(char *line, t_param *lem)
{
	int i;
	int flag;

	i = -1;
	flag = 1;
	while (line[++i])
		if ((flag = ft_isdigit(line[i])) == 0)
			break ;
	if (flag && (lem->sum_ants = ft_atoi(line)) <= 0)
		flag = 0;
	return (flag);
}
