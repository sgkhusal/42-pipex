/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:09:46 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/25 05:31:07 by sguilher         ###   ########.fr       */
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
			data->exec_paths = ft_split(ft_strchr(envp[i], '/'), ':');
			if (data->exec_paths == NULL)
				pipex_error(data,
					"pipex: ft_split malloc error for data->exec_paths");
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
		pipex_error(data, "Allocation memory error for data->cmds");
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

static void	set_cmds(t_pipex *data, char *argv[])
{
	int	i;
	
	data->total_cmds = 2; // muda aqui no bonus
	alloc_cmds(data);
	i = 0;
	while(i < data->total_cmds)
	{
		*data->cmds[i] = (t_cmd){.args = NULL, .cmd = NULL, .path = NULL};
		pipex_cmd_args_split(data, data->cmds[i], argv[i + 2]);
		if (data->cmds[i]->args == NULL)
			pipex_error(data, "pipex: malloc error in set_cmds"); // limpar 
		data->cmds[i]->cmd = ft_strdup(data->cmds[i]->args[0]);
		i++;
	}
}

void	pipex_init(t_pipex *data, int argc, char *argv[], char *envp[])
{
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
	set_cmds(data, argv);
	int i = 0;
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

/* static int	cmds_limiters(char **args, char c)
{
	int	i;
	int	j;
	char	*tmp;
	int	simple_quote_qty;
	int	double_quotes_qty;

	simple_quote_qty = ft_limiter_qty(args, '\'');
	double_quotes_qty = ft_limiter_qty(args, '\"');

	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] = c)
		{
			j = 1;
			tmp = ft_strdup(args[i]);
			while (args[i + j][ft_strlen(args[i + j] - 1)] != c)
			{
				tmp = ft_strsjoin(3, tmp, " ", args[i + j]);
				j++;
			}
			tmp = ft_strsjoin(3, tmp, " ", args[i + j]);
			free(args[i]);
			args[i] = tmp;
		}
	}
} */
