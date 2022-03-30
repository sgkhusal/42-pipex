/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:51:00 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/30 19:01:39 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static int	pipex_cmd_path(t_pipex *data, t_cmd *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (data->exec_paths[i])
	{
		path = ft_strsjoin(3, data->exec_paths[i], "/", cmd->cmd);
		if (!path)
			pipex_error(data, "pipex: cmd path string creation error");
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				cmd->path = path;
				return (OK);
			}
			else
				return (E_NOEXEC);
		}
		free(path);
		i++;
	}
	return (E_CMD_NOT_FOUND);
}

static void	pipex_error_cmd_path(t_pipex *data, t_cmd *cmd, int check)
{
	if (check == E_NOEXEC)
	{
		ft_printf_fd(2, "%s: %s\n", cmd->cmd, strerror(E_NOEXEC));
		pipex_close(data);
		exit(E_NOEXEC);
	}
	else if (check == E_CMD_NOT_FOUND)
	{
		ft_printf_fd(2, "pipex: %s: command not found\n", cmd->cmd);
		pipex_close(data);
		exit(E_CMD_NOT_FOUND);
	}
	exit(EXIT_FAILURE);
}

static void	pipex_exec_cmd(t_pipex *data, t_cmd *cmd, char *envp[])
{
	int	check;

	check = pipex_cmd_path(data, cmd);
	if (check == OK)
	{
		check = execve(cmd->path, cmd->args, envp);
		if (check == -1)
		{
			ft_printf_fd(2, "pipex: execve execution error for command %s",
				cmd->cmd);
			pipex_error(data, " ");
		}
		exit(EXIT_FAILURE);
	}
	else
		pipex_error_cmd_path(data, cmd, check);
}

void	pipex_check_cmd(t_pipex *data, t_cmd *cmd)
{
	if (!cmd->cmd[0])
	{
		pipex_close_pipe_fds(data);
		pipex_error2(data, ": command not found");
		exit(EXIT_FAILURE);
	}
}

void	pipex_child(t_pipex *data, int i, char *envp[])
{
	if (i == 0 && data->input_fd == -1)
		pipex_io_fd_error(data);
	if (i == data->total_cmds - 1 && data->output_fd == -1)
		pipex_io_fd_error(data);
	pipex_check_cmd(data, data->cmds[i]);
	if (i == 0)
	{
		dup2(data->input_fd, STDIN);
		dup2(data->pipe_fds[1], STDOUT);
	}
	else if (i == data->total_cmds - 1)
	{
		dup2(data->pipe_in_fd, STDIN);
		dup2(data->output_fd, STDOUT);
	}
	else
	{
		dup2(data->pipe_in_fd, STDIN);
		dup2(data->pipe_fds[1], STDOUT);
	}
	pipex_close_fds(data);
	pipex_exec_cmd(data, data->cmds[i], envp);
}
