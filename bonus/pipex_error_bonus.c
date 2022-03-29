/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:46:50 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/29 20:49:46 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex_error(t_pipex *data, char *msg)
{
	perror(msg);
	pipex_close(data);
	exit(EXIT_FAILURE);
}

void	pipex_error2(t_pipex *data, char *msg)
{
	ft_printf_fd(2, "pipex: %s\n", msg);
	pipex_close(data);
	exit(EXIT_FAILURE);
}

void	pipex_quote_error(t_pipex *data, char **aux)
{
	ft_printf("pipex: invalid argument: missing single quote\n");
	ft_clean_ptrptr((void **)aux);
	pipex_close(data);
	exit(EXIT_FAILURE);
}
