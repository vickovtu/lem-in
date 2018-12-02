/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vickovtu <vickovtu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:01:56 by vickovtu          #+#    #+#             */
/*   Updated: 2018/04/01 18:23:49 by vickovtu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		tmp;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tmp = ft_strlen(s1) + ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(char) * (tmp + 1))) == NULL)
		return (NULL);
	str[tmp] = '\0';
	i = 0;
	j = 0;
	while (s1[j] && i < tmp)
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && i < tmp)
		str[i++] = s2[j++];
	return (str);
}
