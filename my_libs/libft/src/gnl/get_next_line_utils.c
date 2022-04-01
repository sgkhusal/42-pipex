/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:57:13 by sguilher          #+#    #+#             */
/*   Updated: 2022/04/01 18:11:38 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_strjoin(char **next, char *buffer)
{
	char	*aux;

	aux = ft_strjoin(*next, buffer);
	ft_clean(next);
	*next = aux;
}

void	ft_clean(char **str)
{
	if (str == NULL && !(*str))
		return ;
	if (*str)
		free(*str);
	*str = NULL;
}
