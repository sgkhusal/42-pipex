/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:55:08 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/25 05:33:14 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	pipex_cmd_args_split(t_pipex *data, t_cmd *cmd, char *args)
{
	int		i;
	int		simple_quote;
	char	*tmp;
	char	**aux;

	simple_quote = ft_char_pos(args, '\'');
	if (simple_quote == -1)
		cmd->args = ft_split(args, ' ');
	else
	{
		tmp = ft_substr(args, 0, simple_quote);
		aux = ft_split(tmp, ' ');
		free(tmp);
		i = simple_quote + 1;
		while(args[i] && simple_quote != -1)
		{
			simple_quote = ft_char_pos(&args[i], '\'');
			if (simple_quote == -1)
			{
				ft_printf("pipex: invalid argument: missing single quote\n");
				clean_ptrptr((void **)aux);
				pipex_close(data);
				exit(EXIT_FAILURE);
			}
			else
			{
				tmp = ft_substr(args, i, simple_quote);
				cmd->args = ft_strarrayjoin(aux, tmp);
				clean_ptrptr((void **)aux);
				free(tmp);
				i = i + simple_quote + 1;
				if (args[i])
				{
					simple_quote = ft_char_pos(&args[i], '\'');
					if (simple_quote != -1)
					{
						if (simple_quote == 1 && args[i] == ' ')
							i += 2;
						else
						{
							tmp = ft_substr(args, i, simple_quote);
							aux = ft_split(tmp, ' ');
							ft_arraysjoin(cmd->args, aux);
							free(tmp);
							clean_ptrptr((void **)aux);
							i = i + simple_quote + 1;
						}
						aux = cmd->args;
					}
				}
			}
		}
	}
}

// se for comando vazio "" --> não faz nada!! --> está dando segfault
// problema com "" (aspas sem comando - dá segfault, bash dá cmd not found)