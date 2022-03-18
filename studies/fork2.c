/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:56:59 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/17 19:10:20 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main()
{
	int child_pid1;
	int child_pid2;

	printf("\nLet's understand multiples fork's return:\n");
	printf("Hello from initial pid %d\n", getpid());
	child_pid1 = fork();
	child_pid2 = fork();
	if(child_pid1 != 0)
	{
		if(child_pid2 != 0)
		{
			// father process
			// the father always have to wait the child, otherwise, if the
			// the father terminates before the child, the child will turns into 
			// a zumbi process (a real orphan!!) and no one will be looking at 
			// it (it's sad!!) and we won't have to know if it terminates ok
			waitpid(child_pid1, NULL, 0);
			waitpid(child_pid2, NULL, 0);
			printf("\n*********************************************************\n");
			printf("Hello! I'am the parent of all processes in this program:\n");
			printf("Process PID: %i\n", getpid());
			printf("Child 1 PID: %i\n", child_pid1);
			printf("Child 2 PID: %i\n", child_pid2);
		}
		else
		{
			printf("\n*********************************************************\n");
			printf("Hello! I'am the child 2 and I don't have any child:\nProcess PID: %i\nChild 1 PID: %i\nChild 2 PID: %i\nParent PID: %i\n",
				getpid(), child_pid1, child_pid2, getppid());
		}
	}
	if(child_pid1 == 0)
	{
		if(child_pid2 != 0)
		{
			waitpid(child_pid2, NULL, 0);
			printf("\n*********************************************************\n");
			printf("Hello! I'am the child 1 and I also have a child:\nProcess PID: %i\nChild 1 PID: %i\nChild 2 PID: %i\nParent PID: %i\n",
				getpid(), child_pid1, child_pid2, getppid());
		}
		else
		{
			printf("\n*********************************************************\n");
			printf("Hello! I'am the child from child 1 and so the grandchild from father process:\nProcess PID: %i\nChild 1 PID: %i\nChild 2 PID: %i\nParent PID: %i\n",
				getpid(), child_pid1, child_pid2, getppid());
		}
	}
	return (0);
}
