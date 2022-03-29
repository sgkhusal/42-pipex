/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:25:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/29 20:47:31 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

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
			ft_clean_ptrptr((void **) data->cmds[i]->args);
			i++;
		}
		ft_clean_ptrptr((void **) data->cmds);
	}
	if (data->input_fd != -1)
		close(data->input_fd);
	if (data->output_fd != -1)
		close(data->output_fd);
	if (data->pipe_in_fd != -1)
		close(data->pipe_in_fd);
}

void	pipex_close_pipe_fds(t_pipex *data)
{
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);
}

void	pipex_close_fds(t_pipex *data)
{
	pipex_close_pipe_fds(data);
	if (data->input_fd != -1)
		close(data->input_fd);
	if (data->output_fd != -1)
		close(data->output_fd);
	if (data->pipe_in_fd != -1)
		close(data->pipe_in_fd);
}
