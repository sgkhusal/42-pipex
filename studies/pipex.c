/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:14:18 by coder             #+#    #+#             */
/*   Updated: 2022/03/01 01:24:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(){
	//int id = fork();

	int id1 = fork();
	int id2 = fork();
	printf("id1 = %d, id2 = %d\n", id1, id2);

	/* if (id == 0){
		int id2 = fork();
		printf("Hello from fork2 id: %d\n", id2);
	}
	printf("Hello from id: %d\n", id); */

	/* if (id == 0) {
		sleep(1);
	}
	printf("Current ID: %d, parent ID: %d, fork process ID: %d\n",
		getpid(), getppid(), id);
	int res = wait(NULL);
	if (res == -1) {
		printf("No children to wait for fork id = %d\n", id);
	} else {
		printf("%d finished execution, fork id = %d\n", res, id);
	} */
	return (0);
}