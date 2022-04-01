/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:09:46 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/31 04:56:35 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

static void	set_env_path(t_pipex *data, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->exec_paths = ft_split(ft_strchr(envp[i], '/'), ':');
			if (data->exec_paths == NULL)
				pipex_error2(data,
					"ft_split malloc error for data->exec_paths");
			return ;
		}
		i++;
	}
	pipex_error2(data, "no PATH variable encounter");
}

static void	alloc_cmds(t_pipex *data)
{
	int	i;

	data->cmds = (t_cmd **)(malloc((data->total_cmds + 1) * sizeof(t_cmd *)));
	if (!data->cmds)
		pipex_error(data, "pipex: allocation memory error for data->cmds");
	i = 0;
	while (i < data->total_cmds)
	{
		data->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
		if (!data->cmds[i])
			pipex_error(data, "pipex: alloc error for cmd");
		i++;
	}
	data->cmds[i] = NULL;
}

static void	set_cmds(t_pipex *data, int nc, char *cmds[])
{
	int	i;

	data->total_cmds = nc;
	alloc_cmds(data);
	i = 0;
	while (i < data->total_cmds)
	{
		data->cmds[i]->args = NULL;
		data->cmds[i]->cmd = NULL;
		data->cmds[i]->path = NULL;
		i++;
	}
	i = 0;
	while (i < data->total_cmds)
	{
		pipex_cmd_args_split(data, data->cmds[i], cmds[i]);
		if (data->cmds[i]->args == NULL)
			pipex_error2(data, "pipex: cmd args split error");
		if (!data->cmds[i]->args[0])
			data->cmds[i]->cmd = ft_strdup("");
		else
			data->cmds[i]->cmd = ft_strdup(data->cmds[i]->args[0]);
		i++;
	}
}

void	pipex_init(t_pipex *data, int argc, char *argv[], char *envp[])
{
	data->status = 0;
	data->cmds = NULL;
	data->exec_paths = NULL;
	if (data->here_doc != HERE_DOC)
		data->pipe_in_fd = -1;
	if (data->here_doc == HERE_DOC)
		data->input_fd = data->pipe_in_fd;
	else
		data->input_fd = open(argv[1], O_RDONLY, FD_CLOEXEC);
	if (data->input_fd == -1)
		pipex_fd_open_error_msg(argv[1]);
	if (data->here_doc == HERE_DOC)
		data->output_fd = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->output_fd = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output_fd == -1)
		pipex_fd_open_error_msg(argv[argc - 1]);
	set_env_path(data, envp);
	if (data->here_doc == HERE_DOC)
		set_cmds(data, argc - 4, &argv[3]);
	else
		set_cmds(data, argc - 3, &argv[2]);
}
