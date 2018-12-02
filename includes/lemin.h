/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:49:14 by vickovtu          #+#    #+#             */
/*   Updated: 2018/07/17 15:54:15 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>

# define BUFF_SIZE	100
# define RESET		"\033[0m"
# define R			"\033[0m"
# define W			"\033[34;46m"
# define RED		"\033[31;7m"
# define YELLOW		"\033[1;33m"
# define WHITE		"\033[1;37m"
# define GREEN		"\033[1;32m"

typedef struct			s_room
{
	char			*room_name;
	int				y;
	int				x;
	int				deep;
	int				ant_inside;
	struct s_room	*next;
	struct s_room	*before;

}						t_room;

typedef struct			s_connect
{
	t_room				*room_1;
	t_room				*room_2;
	struct s_connect	*next;
	struct s_connect	*before;
}						t_connect;

typedef struct			s_ants
{
	t_room				*way;
	struct s_ants		*next;
	struct s_ants		*pre;
	int					num;
}						t_ant;

typedef struct			s_param
{
	int					sum_ants;
	t_room				*start;
	t_room				*end;
	t_room				*room;
	t_connect			*con;
	t_room				*way;
	t_ant				*ant;
	int					leaks;
	int					w;
}						t_param;

int						get_next_line(const int fd, char **line);
int						main(int argv, char **argc);
void					ft_get(t_param *lem, char *line, int flag);
int						ft_hesh(t_param *lem, char *line);
t_connect				*ft_con(char **str, t_param *lem);
void					ft_ft(t_connect *con, char **str, t_param *lem);
void					ft_algo(t_param *lem);
int						ft_algo1(t_param *l, t_connect *c, t_room *h, int i);
void					ft_way(t_param *lem, t_room *room);
void					ft_way_dop(t_param *lem, t_room *way, int i);
t_room					*ft_list(void);
t_connect				*ft_list1(void);
t_room					*ft_way1(t_room *room);
void					ft_way2(t_room *way, t_room *room);
void					ft_print(t_param *lem, t_room *way, t_room *way1);
int						ft_print2(int i, t_param *lem, t_ant *a, t_room *w);
t_ant					*ft_ant(t_ant *ant, t_room *way, int i);
int						ft_valid_connect_str(char *line, t_param *lem);
int						ft_valid_s_e(t_room *ph, t_param *lem);
int						ft_valid_room(t_room *ph, t_room *room);
t_room					*ft_room_fill(char *line);
int						ft_room(char *line, t_param *lem);
void					ft_add_start(t_param *lem);
int						ft_end(t_param *lem);
int						ft_start(t_param *lem);
t_room					*ft_start_end(char *line);
int						ft_free(char *str, int i);
int						ft_sum_ants(char *line, t_param *lem);
int						ft_dash(char *line);
int						ft_valid_str(char *line, t_param *lem);
char					*ft_line(void);
int						ft_valid_str1(char *line);
void					ft_w(t_room	*way);
t_room					*ft_back(t_room	*room);

#endif
