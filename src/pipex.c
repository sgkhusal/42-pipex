/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:49:47 by coder             #+#    #+#             */
/*   Updated: 2022/03/17 23:17:15 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	pipex_pipes(t_pipex	*data)
{
	int	pipe_fds[2];
	int	child_pid;
	int	i;

	if(pipe(pipe_fds) == -1)
		pipex_error("Pipe creating error");
	i = 0;
	while(i < data->total_cmds)
	{
		child_pid = fork();
		if(child_pid == -1)
			pipex_error("Fork creating error");
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

int	main(int argc, char **argv)//, char **envp)
{
	t_pipex	data;
	int	i;
	
	//perror("Erro de argumentos");
	if (argc != 5)
	{
		ft_printf("%s - pipex needs 4 arguments\n", strerror(E_INVAL));
		exit(EXIT_FAILURE);
	}
	else
	{
		i = 0;
		data.total_cmds = 2;
		data.input_fd = open(argv[1], O_RDONLY, FD_CLOEXEC); ///
		if (data.input_fd == -1)
			pipex_error(argv[1]); // bash: infile: ...
		data.output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC |
			FD_CLOEXEC, 0644);
		if (data.input_fd == -1)
			pipex_error(argv[argc - 1]);
		// encontrar os paths
		while (argv[i])
		{
			ft_printf("%s\n", argv[i]);
			i++;
		}
		ft_printf("comands = %i\ninfile fd = %i\noutfile fd = %i\n",
			data.total_cmds, data.input_fd, data.output_fd);
	}
	return (0);
}
