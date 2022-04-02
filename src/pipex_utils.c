/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 01:31:35 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/25 20:45:27 by sguilher         ###   ########.fr       */
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

int	ft_char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_strarrayjoin(char **array, char *str)
{
	int		size;
	int		i;
	char	**new_array;

	if (!array && !str)
		return (NULL);
	else if (!str)
		return (array);
	size = 0;
	if (array != NULL)
	{
		while (array[size] != NULL)
			size++;
	}
	new_array = (char **)malloc((size + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (++i < size)
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	return (new_array);
}

char	**ft_arraysjoin(char **array1, char **array2)
{
	int		i;
	char	**aux;
	char	**new_array;

	i = 0;
	aux = array1;
	while (array2[i])
	{
		new_array = ft_strarrayjoin(aux, array2[i]);
		ft_clean_ptrptr((void **)aux);
		aux = new_array;
		i++;
	}
	return (new_array);
}
