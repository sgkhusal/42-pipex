/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:51:00 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/24 04:23:42 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static int pipex_cmd_path(t_pipex *data, t_cmd *cmd)
{
	int i;
	char *path;

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

static void pipex_exec_cmd(t_pipex *data, t_cmd *cmd, char *envp[])
{
	int check;

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
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (check == E_NOEXEC)
			ft_printf_fd(2, "%s: %s\n", cmd->cmd, strerror(E_NOEXEC));
		else if (check == E_CMD_NOT_FOUND)
			ft_printf("pipex: %s: command not found\n", cmd->cmd);
		exit(EXIT_FAILURE);
	}
}

void	pipex_child(t_pipex *data, int i, char *envp[])
{
	ft_printf("Estamos na child\n");
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
	/* else // bonus
	{
		dup2(data->pipe_in_fd, STDIN);
		dup2(data->pipe_fds[1], STDOUT);
	} */
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);
	close(data->input_fd);
	close(data->output_fd);
	//ft_printf_fd(1, "cmd %i = %s\n", i, data->cmds[i]->cmd); //
	pipex_exec_cmd(data, data->cmds[i], envp);
}
