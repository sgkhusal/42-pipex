/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:54:13 by coder             #+#    #+#             */
/*   Updated: 2022/03/21 04:27:14 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs.h"
# include "pipex_errors.h"

# define STDIN 0

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	*path;
}				t_cmd;

typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	int		total_cmds;
	t_cmd	**cmds;
	char	*env_path;
	char	**exec_paths;
}				t_pipex;

void	pipex_init(t_pipex *data, int argc, char *argv[], char *envp[]);

void	close_pipex(t_pipex *data);
void	pipex_error(t_pipex *data, char *msg);

char	*ft_strsjoin(int n, char *str1, ...);
void	ft_strjoin_free(char **str1, char *str2);

#endif
