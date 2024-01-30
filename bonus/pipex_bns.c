/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:23 by acomet            #+#    #+#             */
/*   Updated: 2023/05/24 16:34:06 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

int	pipex_bns(t_args *ppx_args, int *pid)
{
	int	fd[2];
	int	i;

	if (!ft_strcmp(ppx_args->argv[1], "here_doc"))
		return (ppxb_here_doc(ppx_args, fd, pid));
	if (pipe(fd) == -1)
		return (-1);
	pid[0] = ppxb_first_fork(ppx_args, fd);
	if (pid[0] == -1)
		return (ppxb_close_pipe_fd(fd));
	i = 5;
	while (i < ppx_args->argc)
	{
		pid[i - 4] = ppxb_middle_fork(ppx_args, fd, i - 2);
		if (pid[i - 4] == -1)
			return (ppxb_close_pipe_fd(fd));
		i++;
	}
	pid[i - 4] = ppxb_last_fork(ppx_args, fd, i - 2);
	if (pid[i - 4] == -1)
		return (ppxb_close_pipe_fd(fd));
	return (0);
}

static void	wait_and_free_pid(int argc, int *pid)
{
	int	i;

	i = 5;
	if (pid)
	{
		while (i < argc + 2)
		{
			if (pid[i - 5] != -1)
				waitpid(pid[i - 5], NULL, 0);
			i++;
		}
		free(pid);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**all_path;
	t_args	ppx_args;
	int		*pid;

	all_path = NULL;
	pid = NULL;
	if (argc < 5)
	{
		ft_printferr("Pas le bon nombre d'arguments !\n");
		return (1);
	}
	if (initialize_struct(&ppx_args, argc, argv, envp))
		return (2);
	pid = initialize_pid(argc);
	if (!pid || pipex_bns(&ppx_args, pid))
		ft_printferr("Error\n");
	wait_and_free_pid(argc, pid);
	ppxb_free_path(ppx_args.all_path);
	return (0);
}
