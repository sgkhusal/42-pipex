/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:47:37 by coder             #+#    #+#             */
/*   Updated: 2022/03/16 22:01:33 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main()
{
	int child_pid;

	printf("Let's understand fork's return:\n");
	child_pid = fork();
	if(child_pid == 0)
		wait(NULL);
	printf("Process PID: %i - Child PID: %i - Parent PID: %i\n",
		getpid(), child_pid, getppid());
	return (0);
}
