/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:09:46 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/21 05:25:48 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	set_env_path(t_pipex *data, char *envp[])
{
	int	i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->env_path = envp[i];
			data->exec_paths = ft_split(ft_strchr(envp[i], '/'), ':');
			if (data->exec_paths == NULL)
				pipex_error(data, "ft_split malloc error for data->exec_paths");
			return ;
		}
		i++;
	}
	pipex_error(data, "No PATH variable encounter");
}

static void	alloc_cmds(t_pipex *data)
{
	int	i;

	data->cmds = (t_cmd **)(malloc((data->total_cmds + 1) * sizeof(t_cmd *)));
	if (!data->cmds)
		pipex_error(data, "Allocation memory error for data->cmds"); // precisa limpar
		//a variável de ambiente;
	i = 0;
	while (i < data->total_cmds)
	{
		data->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
		if (!data->cmds[i])
			pipex_error(data, "Malloc error for cmd.");
		i++;
	}
	data->cmds[i] = NULL;
}

static void	cmds_path(t_pipex *data, t_cmd *cmd)
{
	int		i;
	char	*path;
	int		no_exec;

	i = 0;
	no_exec = 0;
	while (data->exec_paths[i])
	{
		path = ft_strsjoin(3, data->exec_paths[i], "/", cmd->cmd);
		if(access(path, F_OK) == 0)
		{
			if(access(path, X_OK) == 0)
			{
				cmd->path = path;
				return ;
			}
			else
				no_exec = 1;
		}
		free(path);
		i++;
	}
	if (no_exec == 1)
		ft_printf("%s: %s\n", cmd->cmd, strerror(E_NOEXEC)); ///////// checar behavior no bash
	else
		ft_printf("%s: command not found\n", cmd->cmd);
}

static void	set_cmds(t_pipex *data, char *argv[])
{
	int	i;
	
	data->total_cmds = 2; // muda aqui no bonus
	alloc_cmds(data);
	i = 0;
	while(i < data->total_cmds)
	{
		*data->cmds[i] = (t_cmd){.args = NULL, .cmd = NULL, .path = NULL};
		data->cmds[i]->args = ft_split(argv[i + 2], ' '); ///
		if (data->exec_paths == NULL)
			pipex_error(data, "Malloc error for data->cmds[i]->args"); // limpar  */
		data->cmds[i]->cmd = ft_strdup(data->cmds[i]->args[0]);
		cmds_path(data, data->cmds[i]);
		ft_printf("%s\n", data->cmds[i]->path);
		i++;
	}
}

void	pipex_init(t_pipex *data, int argc, char *argv[], char *envp[])
{
	data->env_path = NULL;
	data->cmds = NULL;
	data->exec_paths = NULL;
	data->input_fd = open(argv[1], O_RDONLY, FD_CLOEXEC); ///
	if (data->input_fd == -1)
		perror(argv[1]); // bash: infile: ...
	data->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC |
		FD_CLOEXEC, 0644);
	if (data->output_fd == -1)
		pipex_error(data, argv[argc - 1]);
	set_env_path(data, envp);
	ft_printf("%s\n", data->env_path);
	int i = 0;
	/* while(data->exec_paths[i])
	{
		ft_printf("%s\n", data->exec_paths[i]);
		i++;
	} */
	set_cmds(data, argv);
	i = 0;
	while (data->cmds[i])
	{
		ft_printf("cmd = %s\n", data->cmds[i]->cmd);
		int j = 0;
		while(data->cmds[i]->args[j])
		{
			ft_printf("Arg %i = %s\n", j, data->cmds[i]->args[j]);
			j++;
		}
		i++;
	}
}
