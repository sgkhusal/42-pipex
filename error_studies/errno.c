/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:50:39 by coder             #+#    #+#             */
/*   Updated: 2022/03/16 17:52:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	main()
{
	int		fd;
	char	*line;
	char	**error;
	char	*msg;

	fd = open("errno", O_RDONLY);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		error = ft_split(line, ' ');
		msg = strerror(ft_atoi(error[2]));
		ft_printf("Error number %s - %s: %s\n", error[2], error[1], msg);
		free(line);
		line = NULL;
	}
	close(fd);
}

