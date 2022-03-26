/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:49:47 by coder             #+#    #+#             */
/*   Updated: 2022/03/25 22:36:45 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex(t_pipex *data, char *envp[])
{
	int	child_pid;
	int	i;

	i = 0;
	while (i < data->total_cmds)
	{
		if (pipe(data->pipe_fds) == -1)
			pipex_error(data, "pipex: pipe creating error");
		child_pid = fork();
		if (child_pid == -1)
			pipex_error(data, "pipex: fork creating error");
		if (child_pid == 0)
			pipex_child(data, i, envp);
		else
		{
			if (i != 0)
				close(data->pipe_in_fd);
			if (i < data->total_cmds - 1)
				data->pipe_in_fd = dup(data->pipe_fds[0]);
			close(data->pipe_fds[0]);
			close(data->pipe_fds[1]);
			waitpid(child_pid, NULL, 0);
			i++;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_printf("pipex: %s - pipex needs at least 4 arguments\n",
			strerror(E_INVAL));
		exit(EXIT_FAILURE);
	}
	else
	{
		pipex_init(&data, argc, argv, envp);
		pipex(&data, envp);
	}
	pipex_close(&data);
	return (0);
}
