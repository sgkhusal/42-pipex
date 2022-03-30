/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:54:13 by coder             #+#    #+#             */
/*   Updated: 2022/03/30 18:39:56 by sguilher         ###   ########.fr       */
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
	int		pipe_fds[2];
	int		pipe_in_fd;
	int		total_cmds;
	int		status;
	t_cmd	**cmds;
	char	**exec_paths;
}				t_pipex;

typedef struct s_cmd_split
{
	char	*tmp;
	char	**aux;
	int		i;
	int		quote_pos;
}				t_cmd_split;

void	pipex_init(t_pipex *data, int argc, char *argv[], char *envp[]);
void	pipex_child(t_pipex *data, int i, char *envp[]);
void	pipex_cmd_args_split(t_pipex *data, t_cmd *cmd, char *args);

char	*ft_strsjoin(int n, char *str1, ...);
void	ft_strjoin_free(char **str1, char *str2);
char	**ft_strarrayjoin(char **array, char *str);
void	ft_arraysjoin(char **array1, char **array2);
int		ft_char_pos(char *str, char c);

void	pipex_close(t_pipex *data);
void	pipex_close_pipe_fds(t_pipex *data);
void	pipex_close_fds(t_pipex *data);
void	ft_clean_ptrptr(void **ptr);

void	pipex_error(t_pipex *data, char *msg);
void	pipex_error2(t_pipex *data, char *msg);
void	pipex_quote_error(t_pipex *data, char **aux);
void	pipex_io_fd_error(t_pipex *data);
void	pipex_fd_open_error_msg(char *str);

#endif
