/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:16:18 by coder             #+#    #+#             */
/*   Updated: 2022/03/16 22:01:38 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int	main(int argc, char *argv[], char *envp[])
{
	printf("\nAccessing environment variables with getenv function:\n");
	printf("	USER=%s\n", getenv("USER"));
	printf("	HOME=%s\n", getenv("HOME"));
	printf("	TERM=%s\n", getenv("TERM"));
	printf("	PATH=%s\n", getenv("PATH"));

	printf("\nAccessing environment variables with envp:\n");
	int	i = 0;
	while(envp[i])
	{
		if(envp[i][0] == 'P' && envp[i][1] == 'A'&& envp[i][2] == 'T')
			printf("	%s\n", envp[i]);
		if(envp[i][0] == 'S' && envp[i][1] == 'G'&& envp[i][2] == 'U')
			printf("	%s\n", envp[i]);
		i++;
	}
	printf("\n%i environment variables\n", i);

	printf("\nAccessing environment variables with global variable environ:\n");
	//It works like envp
	i = 0;
	while(environ[i])
	{
		if(environ[i][0] == 'P' && environ[i][1] == 'A'&& environ[i][2] == 'T')
			printf("	%s\n", environ[i]);
		if(environ[i][0] == 'S' && environ[i][1] == 'G'&& environ[i][2] == 'U')
			printf("	%s\n", environ[i]);
		i++;
	}
	printf("\n%i environment variables\n\n", i);
	return (0);
}
