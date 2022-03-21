/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 01:31:35 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/21 05:09:30 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	ft_strjoin_free(char **str1, char *str2)
{
	char	*aux;

	aux = ft_strjoin(*str1, str2);
	if (str1 != NULL)
		ft_clean(str1);
	*str1 = aux;
}

char	*ft_strsjoin(int n, ...)
{
	va_list	strs;
	int		i;
	char	*s;
	char	*aux;

	va_start(strs, n);
	aux = ft_strdup("");
	i = 0;
	while(i < n)
	{
		s = va_arg(strs, char *);
		ft_strjoin_free(&aux, s);
		if (!aux)
			return (NULL);
		i++;
	}
	va_end(strs);
	return(aux);
}
