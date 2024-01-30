/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:34:02 by acomet            #+#    #+#             */
/*   Updated: 2023/05/03 15:29:00 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

static int	check_access_while_no_path_bns(t_args *ppx_args)
{
	int		i;
	char	*cmd;

	i = 2;
	while (i < ppx_args->argc - 1)
	{
		cmd = ppxb_get_cmd(ppx_args->argv[i]);
		if (!cmd)
			return (1);
		if (access(cmd, X_OK) == -1)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		i++;
	}
	ppx_args->all_path = malloc(sizeof(char *) * 1);
	if (!ppx_args->all_path)
		return (1);
	ppx_args->all_path[0] = ft_strdup("\0");
	if (!ppx_args->all_path[0])
		return (1);
	return (0);
}

int	initialize_struct(t_args *ppx_args, int argc, char **argv,
		char **envp)
{
	ppx_args->argc = argc;
	ppx_args->argv = argv;
	ppx_args->envp = envp;
	ppx_args->all_path = ppxb_get_all_path(envp);
	if (!ppx_args->all_path)
	{
		if (check_access_while_no_path_bns(ppx_args))
		{
			ft_printferr("No path\n");
			return (1);
		}
	}
	return (0);
}

int	*initialize_pid(int argc)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * (argc - 3));
	if (!pid)
		return (NULL);
	i = 0;
	while (i < argc - 3)
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}
