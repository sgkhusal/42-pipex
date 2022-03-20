/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:26:37 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/19 02:54:50 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Program from https://cs61.seas.harvard.edu/site/2021/ProcessControl/

/* The Linux kernel implements fixed-size buffers for pipes. It is merely an 
implementation choice and a different kernel (or even a different flavor of the 
Linux kernel) can have different implementations. We can find out the size of 
these pipe buffers using the blocking behavior of pipe file descriptors: we 
create a new pipe, and simply keep writing to it one byte at a time. Every 
time we successfully wrote one byte, we know it has been placed in the buffer 
because there is no one reading from this pipe. We print the number of bytes 
written so far every time to wrote one byte to the pipe successfully. The 
program will eventually stop printing numbers to the screen (because write() 
blocks once there is no more space in the buffer), and the last number printed 
to the screen should indicate the size of the pipe buffer. */

int main() {
    int pipefd[2];
    int r = pipe(pipefd);
    assert(r >= 0);

    size_t x = 0;
    while (1) {
        ssize_t nw = write(pipefd[1], "1", 1);
        assert(nw == 1);
        ++x;
        printf("%zu\n", x);
    }
}

// res = 65536 bytes = 64 KB / 4 bytes = 16384 números