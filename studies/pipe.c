/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:26:37 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/18 21:30:25 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Program from https://cs61.seas.harvard.edu/site/2021/ProcessControl/

int main() {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r == 0);

    pid_t p1 = fork();
    assert(p1 >= 0);

    if (p1 == 0) {
        const char* message = "Hello, mama!";
        ssize_t nw = write(pipefd[1], message, strlen(message));
        assert(nw == (ssize_t) strlen(message));
        exit(0);
    }

	close(pipefd[1]); // if not closed, the program will wait more input to read in the pipe
    FILE* f = fdopen(pipefd[0], "r");
    while (!feof(f)) {
        char buf[BUFSIZ];
        if (fgets(buf, BUFSIZ, f) != NULL) {
            printf("I got a message! It was “%s”\n", buf);
        }
    }
    printf("No more messages :(\n");
    fclose(f);
}