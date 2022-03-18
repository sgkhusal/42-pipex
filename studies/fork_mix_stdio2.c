/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mix_stdio2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 04:16:44 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/18 18:22:28 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Program from https://cs61.seas.harvard.edu/site/2021/ProcessControl/

#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// The objective of this program is to see that the OS can decide to run the process in any order.

int main() {
    FILE *fd = fopen("outfile_stdio2", "w");
	int p1 = fork();
    assert(p1 >= 0);

    const char* text;
    if (p1 == 0) {
        text = "BABY\n";
    } else {
        text = "mama\n";
    }
	
    for (int i = 0; i != 1000000; ++i) {
        ssize_t s = fputs(text, fd);
    }
}

// run < outfile_stdio2 uniq -c to see that the words are writing in a messy way
// run < outfile_stdio2 wc -l to see that is writted 2000000 words