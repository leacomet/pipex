/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:23 by acomet            #+#    #+#             */
/*   Updated: 2023/05/10 16:06:44 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_args *ppx_args)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (-1);
	pid1 = ppx_fork_write(ppx_args, fd);
	if (pid1 == -1)
	{
		ft_printferr("Error\n");
		return (ppx_close_pipe_fd(fd));
	}
	pid2 = ppx_fork_read(ppx_args, fd);
	if (pid2 == -1)
	{
		ft_printferr("Error\n");
		return (ppx_close_pipe_fd(fd));
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	check_access_while_no_path(t_args *ppx_args)
{
	int		i;
	char	*cmd;

	i = 2;
	while (i < ppx_args->argc - 1)
	{
		cmd = ppx_get_cmd(ppx_args->argv[i]);
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

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	**all_path;
	t_args	ppx_args;

	all_path = NULL;
	if (argc != 5)
	{
		ft_printferr("not the right numbers of arguments !\n");
		return (1);
	}
	ppx_args.argc = argc;
	ppx_args.argv = argv;
	ppx_args.envp = envp;
	ppx_args.all_path = ppx_get_all_path(envp);
	if (!ppx_args.all_path)
	{
		if (check_access_while_no_path(&ppx_args))
		{
			ft_printferr("no path\n");
			return (2);
		}
	}
	i = pipex(&ppx_args);
	ppx_free_path(ppx_args.all_path);
	return (i);
}
