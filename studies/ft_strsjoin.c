/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:42:30 by sguilher          #+#    #+#             */
/*   Updated: 2022/05/11 11:45:42 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../my_libs/libft/src/libft.h"

static void	ft_strjoin_free(char **str1, char *str2)
{
	char	*aux;

	aux = ft_strjoin(*str1, str2);
	if (str1 != NULL)
		ft_clean(str1);
	*str1 = aux;
}

char	*ft_strsjoin(int n, char *str1, ...)
{
	va_list	strs;
	int		i;
	char	*s;
	char	*aux;

	aux = ft_strdup(str1);
	if (!aux)
		return (NULL);
	va_start(strs, str1);
	i = 1;
	while (i < n)
	{
		s = va_arg(strs, char *);
		ft_strjoin_free(&aux, s);
		i++;
		if (!aux)
			i = n;
	}
	va_end(strs);
	return (aux);
}
