/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_args_bns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:22 by acomet            #+#    #+#             */
/*   Updated: 2023/04/14 13:22:33 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

char	**ppxb_get_args(char *cmd, char *cmd_full)
{
	char	**args;
	int		count;

	count = ppxb_flags_args_count(cmd_full);
	args = malloc(sizeof(char *) * (count + 2));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd);
	if (!args[0])
	{
		free(args);
		return (NULL);
	}
	if (count)
	{
		if (ppxb_get_flags_to_args(args, cmd_full))
			return (NULL);
	}
	args[count + 1] = NULL;
	return (args);
}

int	ppxb_flags_args_count(char *cmd_full)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_full[i] && cmd_full[i] == ' ')
		i++;
	while (cmd_full[i])
	{
		while (cmd_full[i] && cmd_full[i] != ' ')
			i++;
		while (cmd_full[i] && cmd_full[i] == ' ')
			i++;
		if (cmd_full[i])
			count++;
	}
	return (count);
}

int	ppxb_get_flags_to_args(char **args, char *cmd_full)
{
	int		i;
	int		j;
	char	*flags;

	i = 0;
	j = 1;
	flags = NULL;
	while (cmd_full[i] && cmd_full[i] == ' ')
		i++;
	while (cmd_full[i])
	{
		while (cmd_full[i] && cmd_full[i] != ' ')
			i++;
		while (cmd_full[i] && cmd_full[i] == ' ')
			i++;
		if (cmd_full[i])
		{
			args[j] = ppxb_strdup_one_flag_arg(cmd_full + i);
			if (!args[j])
				return (1);
			j++;
		}
	}
	return (0);
}

char	*ppxb_strdup_one_flag_arg(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (s && s[0] == '\'' && s[i - 1] == '\'' && i != 1)
		return (ppxb_strdup_rm_simple_quotes(s));
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != ' ')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ppxb_strdup_rm_simple_quotes(char const *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	str = malloc(sizeof(char) * i - 1);
	if (str == NULL)
		return (NULL);
	j = 1;
	while (s[j] && s[j] != ' ')
	{
		str[j - 1] = s[j];
		j++;
	}
	str[j - 2] = '\0';
	return (str);
}
