/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_numbers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 03:19:16 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/20 18:32:28 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	int	total_nb;
	int	prime;
	int	prime_idx;
	int	pipe_fds1[2];
}				t_data;

void	prime_numbs(t_data *data);
void	write_numbers(t_data *data, int fd_in, int fd_out);
void	filter_prime(int nb, int prime, int fd);
int		new_prime(t_data *data, int fd_in, int fd_out);
ssize_t	read_write(int fd_in, int fd_out);

int	main(int argc, char *argv[]){
	t_data	data;

	if(argc == 1)
		data.total_nb = 1000;
	else if((data.total_nb = atoi(argv[1])) > 32766)
	{
		printf("Number too big. Pipe's file descriptor size don't comport it.\n");
		exit(EXIT_FAILURE);
	}
	data.prime = 2;
	if(pipe(data.pipe_fds1) == -1)
		perror("pipe function error");
	prime_numbs(&data);
	close(data.pipe_fds1[1]);
	close(data.pipe_fds1[0]);
	return (0);
}

void	prime_numbs(t_data *data)
{
	int		pipe2_fds[2];
	int		pipe3_fds[2];
	int		child_pid;
	
	data->prime_idx = 1;
	fprintf(stdout, "prime %i: %i\n", data->prime_idx, data->prime);
	fflush(stdout);
	while (data->prime_idx < data->total_nb)
	{
		if(pipe(pipe2_fds) == -1)
			perror("pipe function error");
		if(pipe(pipe3_fds) == -1)
			perror("pipe function error");
		child_pid = fork();
		if(child_pid == -1)
			perror("fork function error");
		if(child_pid == 0)
		{
			close(data->pipe_fds1[1]);
			close(pipe3_fds[0]);
			close(pipe2_fds[1]);
			close(pipe2_fds[0]);
			write_numbers(data, data->pipe_fds1[0], pipe3_fds[1]);
			close(data->pipe_fds1[0]);
			close(pipe3_fds[1]);
 			exit(EXIT_SUCCESS); //true value
		}
		else
		{
			close(pipe3_fds[1]);
			dup2(pipe2_fds[1], data->pipe_fds1[1]);
			data->prime_idx++;
			data->prime = new_prime(data, pipe3_fds[0], pipe2_fds[1]);
			close(pipe3_fds[0]);
			dup2(pipe2_fds[0], data->pipe_fds1[0]);
			close(pipe2_fds[1]);
			close(pipe2_fds[0]);
			wait(NULL);
			if(data->prime == 0)
				return ;
			fprintf(stdout, "prime %i: %i\n", data->prime_idx, data->prime);
			fflush(stdout);
		}
	}
}

int	new_prime(t_data *data, int fd_in, int fd_out)
{
	int	i;
	ssize_t	res;
	int prime;
	int	nb;

	i = 1;
	while (i <= data->prime_idx)
	{
		prime = read_write(fd_in, fd_out);
		i++;
	}
	res = 1;
	while (res > 0)
	{
		res = read_write(fd_in, fd_out);
	}
	if (res >= 0 && prime > data->prime)
		return (prime);
	else if (prime == data->prime)
		return (0);
	else
		exit(EXIT_FAILURE);
}

ssize_t	read_write(int fd_in, int fd_out)
{
	ssize_t	r;
	ssize_t	w;
	int	nb;
	
	r = read(fd_in, &nb, sizeof(int));
	if (r == -1)
		perror("read function error");
	w = write(fd_out, &nb, sizeof(int));
	if (w == -1)
		perror("write function error");
	if (r > 0)
		return(nb);
	else
		return (r);
}

void	write_numbers(t_data *data, int fd_in, int fd_out)
{
	int	nb;
	int	r;

	if(data->prime == 2)
	{
		nb = 2;
		while (nb <= data->total_nb)
		{
			filter_prime(nb, 2, fd_out);
			nb++;
		}
	}
	else
	{
		r = read(fd_in, &nb, sizeof(int));
		while (r > 0)
		{
			if (r == -1)
				perror("read function error");
			filter_prime(nb, data->prime, fd_out);
			r = read(fd_in, &nb, sizeof(int));
		}
	}
}

void	filter_prime(int nb, int prime, int fd)
{
	int	w;
	
	if (nb == prime || nb % prime != 0)
	{
		w = write(fd, &nb, sizeof(int));
		if (w == -1)
			perror("write function error");
		//printf("write %i for prime %i.\n", nb, prime);
	}
}