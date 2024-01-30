/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:22 by acomet            #+#    #+#             */
/*   Updated: 2023/04/08 17:06:34 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ppx_get_all_path(char **envp)
{
	char	**all_path;
	char	*path_on_one_line;
	int		i;

	i = 0;
	all_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path_on_one_line = ft_strdup(envp[i] + 3);
			if (path_on_one_line && path_on_one_line[0])
				path_on_one_line[0] = ' ';
			if (path_on_one_line && path_on_one_line[0] && path_on_one_line[1])
				path_on_one_line[1] = ':';
			all_path = ft_split(path_on_one_line, ':');
			if (all_path && all_path[0] && all_path[0][0])
				all_path[0][0] = '\0';
			if (path_on_one_line)
				free(path_on_one_line);
			break ;
		}
		i++;
	}
	return (all_path);
}

char	*ppx_get_correct_path(char *cmd_full, char **all_path)
{
	int		i;
	char	*correct_path;
	char	*cmd_without_flags;

	i = 0;
	cmd_without_flags = ppx_get_cmd(cmd_full);
	if (!cmd_without_flags)
		return (NULL);
	while (all_path[i])
	{
		correct_path = ft_strjoin(all_path[i], cmd_without_flags);
		if (!correct_path)
			free(cmd_without_flags);
		if (!correct_path)
			return (NULL);
		if (!access(correct_path, X_OK))
		{
			free(cmd_without_flags);
			return (correct_path);
		}
		free(correct_path);
		i++;
	}
	free(cmd_without_flags);
	return (NULL);
}

char	*ppx_get_cmd(char *cmd_full)
{
	int		i;
	int		j;
	char	*temp;
	char	*cmd_without_flags;

	i = 0;
	j = 0;
	while (cmd_full[j] && cmd_full[j] == ' ')
		j++;
	while (cmd_full[j + i] && cmd_full[j + i] != ' ')
		i++;
	temp = malloc(sizeof(char) * i + 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, cmd_full + j, i + 1);
	cmd_without_flags = ft_strjoin("/", temp);
	free(temp);
	if (!cmd_without_flags)
		return (NULL);
	return (cmd_without_flags);
}
