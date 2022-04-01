/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:54:25 by coder             #+#    #+#             */
/*   Updated: 2022/03/16 22:01:43 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

// system libraries
# include <stdio.h> // perror
# include <string.h> // strerror
# include <fcntl.h> // open modes
# include <unistd.h> // pipe, fork, dup, dup2, access, execve
# include <sys/wait.h> // wait, waitpid

// my libraries and functions
# include "../my_libs/libft/src/libft.h"
# include "../my_libs/libft/src/gnl/get_next_line.h"
# include "../my_libs/ft_printf/src/ft_printf.h"

#endif