/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ft_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:55:08 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/25 20:50:24 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	pipex_args_arrays_join(t_cmd *cmd, char *args, int pos, int final)
{
	char	*tmp;
	char	**aux;

	tmp = ft_substr(args, pos, final);
	aux = ft_split(tmp, ' ');
	ft_arraysjoin(cmd->args, aux);
	free(tmp);
	ft_clean_ptrptr((void **)aux);
}

void	pipex_cmd_args_split_part2(t_cmd *cmd, char *args, t_cmd_split *split)
{
	split->tmp = ft_substr(args, split->i, split->quote_pos);
	cmd->args = ft_strarrayjoin(split->aux, split->tmp);
	ft_clean_ptrptr((void **)split->aux);
	free(split->tmp);
	split->i = split->i + split->quote_pos + 1;
	if (args[split->i])
	{
		split->quote_pos = ft_char_pos(&args[split->i], '\'');
		if (split->quote_pos != -1)
		{
			if (split->quote_pos == 1 && args[split->i] == ' ')
				split->i += 2;
			else
			{
				pipex_args_arrays_join(cmd, args, split->i, split->quote_pos);
				split->i = split->i + split->quote_pos + 1;
			}
			split->aux = cmd->args;
		}
		else
		{
			pipex_args_arrays_join(cmd, args, split->i, ft_strlen(args));
			split->i = ft_strlen(args);
		}
	}
}

void	pipex_cmd_args_split(t_pipex *data, t_cmd *cmd, char *args)
{
	t_cmd_split	split;

	split.quote_pos = ft_char_pos(args, '\'');
	if (split.quote_pos == -1)
		cmd->args = ft_split(args, ' ');
	else
	{
		split.tmp = ft_substr(args, 0, split.quote_pos);
		split.aux = ft_split(split.tmp, ' ');
		free(split.tmp);
		split.i = split.quote_pos + 1;
		while (args[split.i] && split.quote_pos != -1)
		{
			split.quote_pos = ft_char_pos(&args[split.i], '\'');
			if (split.quote_pos == -1)
				pipex_quote_error(data, split.aux);
			else
				pipex_cmd_args_split_part2(cmd, args, &split);
		}
	}
}

// se for comando vazio "" --> não faz nada!! --> está dando segfault
// problema com "" (aspas sem comando - dá segfault, bash dá cmd not found)