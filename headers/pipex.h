/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:54:13 by coder             #+#    #+#             */
/*   Updated: 2022/03/17 23:13:45 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libs.h"
# include "pipex_errors.h"

# define STDIN 0

typedef struct s_cmd
{
	int			total_cmds;
	int			player_set;
	int			items_set;
	int			collect_items;
}				t_cmd;

typedef struct s_pipex
{
	int			total_cmds;
	t_cmd		**cmds;
	int			input_fd;
	int			output_fd;
}				t_pipex;

#endif
