/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:25:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/26 02:36:41 by sguilher         ###   ########.fr       */
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
	ft_printf("pipex: %s\n", msg);
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

void	ft_clean_ptrptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	else
	{
		if (ptr[i])
		{
			while (ptr[i])
			{
				free(ptr[i]);
				ptr[i] = NULL;
				i++;
			}
		}
		free(ptr);
		ptr = NULL;
	}
}

void	pipex_close(t_pipex *data)
{
	int	i;

	if (data->exec_paths)
		ft_clean_ptrptr((void **) data->exec_paths);
	if (data->cmds != NULL)
	{
		i = 0;
		while (data->cmds[i])
		{
			if (data->cmds[i]->cmd)
				free(data->cmds[i]->cmd);
			if (data->cmds[i]->path)
				free(data->cmds[i]->path);
			if (data->cmds[i]->args)
				ft_clean_ptrptr((void **) data->cmds[i]->args);
			i++;
		}
		ft_clean_ptrptr((void **) data->cmds);
	}
	close(data->input_fd);
	close(data->output_fd);
}
