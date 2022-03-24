/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:25:36 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/22 22:19:12 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex_error(t_pipex *data, char *msg)
{
	perror(msg);
	pipex_close(data);
	exit(EXIT_FAILURE);
}

static void	clean_ptrptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL && !(*ptr))
		return ;
	else
	{
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
		ptr = NULL;
	}
}

void	pipex_close(t_pipex *data)
{
	int i;
	
	if (data->exec_paths)
		clean_ptrptr((void **) data->exec_paths);
	if (data->cmds != NULL)
	{
		i = 0;
		while(data->cmds[i])
		{
			if (data->cmds[i]->cmd)
				free(data->cmds[i]->cmd);
			if (data->cmds[i]->path)
				free(data->cmds[i]->path);
			clean_ptrptr((void **) data->cmds[i]->args);
			i++;
		}
		clean_ptrptr((void **) data->cmds);
	}
	close(data->input_fd);
	close(data->output_fd);
}
