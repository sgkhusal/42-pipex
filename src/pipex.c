/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:49:47 by coder             #+#    #+#             */
/*   Updated: 2022/03/21 04:46:36 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex_pipes(t_pipex	*data)
{
	int	pipe_fds[2];
	int	child_pid;
	int	i;

	if(pipe(pipe_fds) == -1)
		pipex_error(data, "Pipe creating error");
	i = 0;
	while(i < data->total_cmds)
	{
		child_pid = fork();
		if(child_pid == -1)
			pipex_error(data, "Fork creating error");
		if (child_pid == 0)
		{
			if (i == 0)
			{
				close(pipe_fds[0]);
				dup2(data->input_fd, STDIN);
				dup2(pipe_fds[1], STDOUT);
			}
			else if (i == data->total_cmds - 1)
			{
				close(pipe_fds[1]);
				dup2(pipe_fds[0], STDIN);
				dup2(data->output_fd, STDOUT);
			}
			else
			{
				dup2(pipe_fds[0], STDIN);
				dup2(pipe_fds[1], STDOUT); // vai dar xabu!!! tem que ser pipes diferentes
			}
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;
	
	if (argc != 5)
	{
		ft_printf("%s - pipex needs 4 arguments\n", strerror(E_INVAL));
		exit(EXIT_FAILURE);
	}
	else
	{
		pipex_init(&data, argc, argv, envp);
	}
	close_pipex(&data);
	return (0);
}
