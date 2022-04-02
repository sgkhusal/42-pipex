/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args_split_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:55:08 by sguilher          #+#    #+#             */
/*   Updated: 2022/04/03 00:09:08 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex_bonus.h"

static void	pipex_args_arrays_join(t_cmd *cmd, char *args, int pos, int final)
{
	char	*tmp;
	char	**aux1;
	char	**aux2;

	aux1 = cmd->args;
	tmp = ft_substr(args, pos, final);
	aux2 = ft_split(tmp, ' ');
	cmd->args = ft_arraysjoin(aux1, aux2);
	free(tmp);
	ft_clean_ptrptr((void **)aux2);
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
			{
				cmd->args = NULL;
				pipex_quote_error(data, split.aux);
			}
			else
				pipex_cmd_args_split_part2(cmd, args, &split);
		}
	}
}
