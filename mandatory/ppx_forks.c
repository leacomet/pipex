/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:22 by acomet            #+#    #+#             */
/*   Updated: 2023/05/02 21:07:57 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ppx_fork_write(t_args *ppx_args, int fd[2])
{
	int		pid;
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (ppx_get_cmd_and_args(ppx_args, &cmd, &args, 2) == -1)
			return (-1);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (ppx_fork_free(cmd, args));
		ppx_close_pipe_fd(fd);
		if (read_in_infile(ppx_args) || execve(cmd, args, ppx_args->envp))
			return (ppx_fork_free(cmd, args));
	}
	return (pid);
}

int	ppx_fork_read(t_args *ppx_args, int fd[2])
{
	int		pid;
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (ppx_get_cmd_and_args(ppx_args, &cmd, &args, 3) == -1)
			return (-1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ppx_fork_free(cmd, args));
		ppx_close_pipe_fd(fd);
		if (write_in_outfile(ppx_args) || execve(cmd, args, ppx_args->envp))
			return (ppx_fork_free(cmd, args));
	}
	ppx_close_pipe_fd(fd);
	return (pid);
}

int	ppx_get_cmd_and_args(t_args *ppx_args, char **cmd, char ***args, int i)
{
	*cmd = ppx_get_correct_path(ppx_args->argv[i], ppx_args->all_path);
	if (!*cmd)
		return (-1);
	*args = ppx_get_args(*cmd, ppx_args->argv[i]);
	if (!*args || access(*cmd, X_OK) == -1)
		return (ppx_fork_free(*cmd, *args));
	return (0);
}
