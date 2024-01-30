/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:18:50 by acomet            #+#    #+#             */
/*   Updated: 2023/03/17 14:34:46 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ppx_fork_free_close(char *cmd, char **args, int fd[2])
{
	ppx_fork_free(cmd, args);
	ppx_close_pipe_fd(fd);
	return (-1);
}

int	ppx_fork_free(char *cmd, char **args)
{
	int	i;

	i = 0;
	if (cmd)
		free(cmd);
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	return (-1);
}

void	ppx_free_path(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		if (path[i])
			free(path[i]);
		i++;
	}
	free(path);
}
