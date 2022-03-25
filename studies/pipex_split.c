/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 01:46:17 by sguilher          #+#    #+#             */
/*   Updated: 2022/03/25 04:58:31 by sguilher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	clean_ptrptr(void **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL && !(*ptr))
		return ;
	else
	{
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
		ptr = NULL;
	}
}

char	**ft_strarrayjoin(char **array, char *str)
{
	int		size;
	int		i;
	char	**new_array;

	if (!array && !str)
		return (NULL);
	else if (!str)
		return (array);
	size = 0;
	if (array != NULL)
	{
		while (array[size] != NULL)
			size++;
	}
	new_array = (char **)malloc((size + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	return (new_array);
}

void	pipex_cmd_args_split(t_cmd *cmd, char *args)
{
	int		i;
	int		simple_quote;
	char	*tmp;
	char	**aux;

	simple_quote = char_pos(args, '\'');
	ft_printf("simple_quote = %i\n", simple_quote);
	if (simple_quote == -1)
		cmd->args = ft_split(args, ' ');
	else
	{
		tmp = ft_substr(args, 0, simple_quote);
		ft_printf("tmp = %s\n", tmp);
		aux = ft_split(tmp, ' ');
		free(tmp);
		i = simple_quote + 1;
		while(args[i] && simple_quote != -1)
		{
			simple_quote = char_pos(&args[i], '\'');
			ft_printf("simple_quote = %i\n", simple_quote);
			if (simple_quote == -1)
			{
				ft_printf_fd(2, "pipex: invalid argument: missing single quote\n");
				clean_ptrptr((void **)aux);
				//pipex_close(data);
				exit(EXIT_FAILURE);
			}
			else
			{
				tmp = ft_substr(args, i, simple_quote);
				ft_printf("tmp = %s\n", tmp);
				cmd->args = ft_strarrayjoin(aux, tmp);
				clean_ptrptr((void **)aux);
				free(tmp);
				i = i + simple_quote + 1;
				if (args[i])
				{
					simple_quote = char_pos(&args[i], '\'');
					if (simple_quote != -1)
					{
						if (simple_quote == 1 && args[i] == ' ')
							i += 2;
						else
						{
							tmp = ft_substr(args, i, simple_quote);
							ft_printf("simple_quote = %i\n", simple_quote);
							ft_printf("here tmp = %s\n", tmp);
							aux = ft_split(tmp, ' ');
							int j = 0;
							char	**aux2;
							while (aux[j])
							{
								aux2 = cmd->args;
								cmd->args = ft_strarrayjoin(aux2, aux[j]);
								clean_ptrptr((void **)aux2);
								j++;
							}
							free(tmp);
							i = i + simple_quote + 1;
						}
						aux = cmd->args;
					}
				}
			}
		}
	}
}

int	main()
{
	t_cmd	cmd;
	char	args[] = "     '  ' awk -F: '{print $1}' bla bla bla ' ' '   ' '' nnnnn";
	int		i;

	ft_printf("%s\n", args);
	pipex_cmd_args_split(&cmd, args);
	i = 0;
	while (cmd.args[i])
	{
		ft_printf("%s - size = %i\n", cmd.args[i], ft_strlen(cmd.args[i]));
		i++;
	}
}


/* typedef struct s_word_set
{
	int	init;
	int	final;
	int	size;
	int	limiter_type;
	struct s_word_set	*next;
}				t_word_set;


static size_t	words_setup(char const *s, char c)
{
	int		i;
	size_t	count;
	t_word_set	*ws;
	t_word_set	**words;

	if (!s || !s[0])
		return (0);
	words = (t_word_set *)malloc(sizeof(t_word_set));
	if (!words)
		return (NULL);
	count = 0;
	i = 0;
	if (s[i] != c && s[i])
	{
		ws = (t_word_set *)malloc(sizeof(t_word_set));
			if (!words)
		return (NULL);
		count = 1;
		ws->init = i;
		ws->next = NULL;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
		{
			count++;
			ws->init = i;
		}
		i++;
	}
	return (count);
} */