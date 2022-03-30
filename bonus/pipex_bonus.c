/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:49:47 by coder             #+#    #+#             */
/*   Updated: 2022/03/30 20:52:17 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

static void	pipex_exit_status(t_pipex *data, int child_pid)
{
	int	w;
	int	status;

	w = waitpid(child_pid, &status, 0);
	if (w == -1)
	{
		pipex_error(data, "pipex: waitpid error");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
}

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
			pipex_close_pipe_fds(data);
			pipex_exit_status(data, child_pid);
			i++;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	data;

	if (ft_strlen(argv[1]) == 8 && ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (argc < 6)
		{
			ft_printf("pipex: %s - here_doc needs at least 5 arguments\n",
				strerror(E_INVAL));
			exit(EXIT_FAILURE);
		}
		data.here_doc = HERE_DOC;
	}
	else if (argc < 5)
	{
		ft_printf("pipex: %s - pipex needs at least 4 arguments\n",
			strerror(E_INVAL));
		exit(EXIT_FAILURE);
	}
	else
		data.here_doc = NO_HERE_DOC;
	pipex_init(&data, argc, argv, envp);
	pipex(&data, envp);
	pipex_close(&data);
	return (data.status);
}
