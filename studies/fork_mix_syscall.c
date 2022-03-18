/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 04:16:44 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/18 04:22:20 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Program from https://cs61.seas.harvard.edu/site/2021/ProcessControl/

#include <unistd.h>
#include <string.h>
#include <assert.h>

// The objective of this program is to see that the OS can decide to run the process in any order.

int main() {
    int p1 = fork();
    assert(p1 >= 0);

    const char* text;
    if (p1 == 0) {
        text = "BABY\n";
    } else {
        text = "mama\n";
    }

    for (int i = 0; i != 1000000; ++i) {
        ssize_t s = write(STDOUT_FILENO, text, strlen(text));
        assert(s == (ssize_t) strlen(text));
    }
}
