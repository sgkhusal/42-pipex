/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:49:47 by coder             #+#    #+#             */
/*   Updated: 2022/03/31 06:03:38 by sguilher         ###   ########.fr       */
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
	if (data->here_doc == HERE_DOC && data->pid_here_doc == child_pid)
	{
		if (data->status != EXIT_SUCCESS)
			pipex_error(data, "pipex: here_doc failure");
	}
}

void	pipex(t_pipex *data, char *envp[])
{
	int	i;
	int	child_pid;

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

void	here_doc_read(t_pipex *data, char *limiter, int lim_size, int fd)
{
	int		gnl;
	char	*aux;

	aux = NULL;
	limiter = ft_strjoin(limiter, "\n");
	gnl = get_next_line(0, &aux);
	while (gnl == 1)
	{
		if (ft_strnstr(aux, limiter, lim_size) == NULL)
		{
			ft_putstr_fd(aux, fd);
			ft_clean(&aux);
			gnl = get_next_line(0, &aux);
			if (gnl == -1)
			{
				close(fd);
				pipex_error(data, "pipex: get_next_line error.");
			}
		}
		else
			gnl = 0;
	}
	close(fd);
	free(limiter);
	ft_clean(&aux);
}

void	pipex_here_doc(t_pipex *data, char *limiter)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		pipex_error(data, "pipex: here_doc pipe creating error");
	data->pid_here_doc = fork();
	if (data->pid_here_doc == -1)
		pipex_error(data, "pipex: here_doc fork creating error");
	if (data->pid_here_doc == 0)
	{
		close(pipe_fd[0]);
		here_doc_read(data, limiter, ft_strlen(limiter) + 1, pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		pipex_exit_status(data, data->pid_here_doc);
		data->pipe_in_fd = dup(pipe_fd[0]);
		close(pipe_fd[0]);
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
		pipex_here_doc(&data, argv[2]);
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
