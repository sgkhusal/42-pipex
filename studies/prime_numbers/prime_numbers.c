/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prime_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 03:19:16 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/20 16:43:19 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

void	prime_numbs(int pipe_fds[2], int n);
void	write_numbers(int n, int prime, int fd_in, int fd_out);
void	filter_prime(int nb, int prime, int fd);
int		new_prime(int pos, int fd_in, int fd_out, int actual_prime);
ssize_t	read_write(int fd_in, int fd_out);

int	main(){
	int	pipe_fds[2];
	int n;

	n = 10000;
	if(pipe(pipe_fds) == -1)
		perror("pipe function error");
	prime_numbs(pipe_fds, n);
	close(pipe_fds[1]);
	close(pipe_fds[0]);
	return (0);
}

void	prime_numbs(int pipe_fds[2], int n)
{
	int		pipe2_fds[2];
	int		pipe3_fds[2];
	int		child_pid;
	int		prime;
	int		i;
	
	i = 1;
	prime = 2;
	fprintf(stdout, "prime %i: %i\n", i, prime);
	fflush( stdout );
	while (i < n)
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
			close(pipe_fds[1]);
			close(pipe3_fds[0]);
			close(pipe2_fds[1]);
			close(pipe2_fds[0]);
			write_numbers(n, prime, pipe_fds[0], pipe3_fds[1]);
			close(pipe_fds[0]);
			close(pipe3_fds[1]);
 			exit(EXIT_SUCCESS); //true value
		}
		else
		{
			close(pipe3_fds[1]);
			dup2(pipe2_fds[1], pipe_fds[1]);
			wait(NULL);
			i++;
			prime = new_prime(i, pipe3_fds[0], pipe2_fds[1], prime);
			close(pipe3_fds[0]);
			dup2(pipe2_fds[0], pipe_fds[0]);
			close(pipe2_fds[1]);
			close(pipe2_fds[0]);
			if(prime == 0)
				return ;
			fprintf(stdout, "prime %i: %i\n", i, prime);
			fflush( stdout );
		}
	}
}

int	new_prime(int pos, int fd_in, int fd_out, int actual_prime)
{
	int	i;
	ssize_t	res;
	int prime;
	int	nb;

	i = 1;
	while (i <= pos)
	{
		prime = read_write(fd_in, fd_out);
		i++;
	}
	res = 1;
	while (res > 0)
	{
		res = read_write(fd_in, fd_out);
	}
	if (res >= 0 && prime > actual_prime)
		return (prime);
	else if (prime == actual_prime)
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

void	write_numbers(int n, int prime, int fd_in, int fd_out)
{
	int	nb;
	int	r;

	if(prime == 2)
	{
		nb = 2;
		while (nb <= n)
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
			filter_prime(nb, prime, fd_out);
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