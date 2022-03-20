/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:28:06 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/18 20:39:37 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

int main() {
    printf("Hello from parent pid %d\n", getpid());

    // Start a child
    pid_t p1 = fork();
    assert(p1 >= 0);
    if (p1 == 0) {
        sleep(5);
        printf("Goodbye from child pid %d\n", getpid());
        exit(0);
    }
    double start_time = current_timestamp();

    // Wait for the child and print its status
    int status;
    pid_t exited_pid = waitpid(p1, &status, 0);
	//the last argument to waitpid(), 0, tells the system call to block until the child exits
    assert(exited_pid == p1);

    if (WIFEXITED(status)) {
        printf("Child exited with status %d after %g sec\n",
                WEXITSTATUS(status), current_timestamp() - start_time);
		//the child’s exit status is usually 0 (which is also EXIT_SUCCESS) on 
		//successful exit and 1 (EXIT_FAILURE) on error exit.
    } else {
        printf("Child exited abnormally [%x]\n", status);
    }
}
