/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_forks_bns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:22 by acomet            #+#    #+#             */
/*   Updated: 2023/05/24 16:34:10 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

int	ppxb_first_fork(t_args *ppx_args, int fd[2])
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
		if (ppxb_get_cmd_and_args(ppx_args, &cmd, &args, 2) == -1)
			return (-1);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (ppxb_fork_free(cmd, args));
		ppxb_close_pipe_fd(fd);
		if (read_in_infile_bns(ppx_args) || execve(cmd, args, ppx_args->envp))
			return (ppxb_fork_free(cmd, args));
	}
	return (pid);
}

int	ppxb_get_cmd_and_args(t_args *ppx_args, char **cmd, char ***args, int i)
{
	*cmd = ppxb_get_correct_path(ppx_args->argv[i], ppx_args->all_path);
	if (!*cmd)
	{
		ft_printf("cmd error\n");
		return (-1);
	}
	*args = ppxb_get_args(*cmd, ppx_args->argv[i]);
	if (!*args || access(*cmd, X_OK) == -1)
		return (ppxb_fork_free(*cmd, *args));
	return (0);
}

int	ppxb_middle_fork(t_args *ppx_args, int old_fd[2], int i)
{
	int		new_fd[2];
	int		pid;
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	new_fd[0] = old_fd[0];
	new_fd[1] = old_fd[1];
	if (pipe(old_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (ppxb_fork_free(cmd, args));
	if (pid == 0)
	{
		if (ppxb_get_cmd_and_args(ppx_args, &cmd, &args, i) == -1)
			return (-1);
		if (ppxb_middle_fork_next_fd(new_fd, old_fd) == -1)
			return (ppxb_fork_free(cmd, args));
		if (execve(cmd, args, ppx_args->envp))
			return (ppxb_fork_free(cmd, args));
	}
	ppxb_close_pipe_fd(new_fd);
	return (pid);
}

int	ppxb_middle_fork_next_fd(int new_fd[2], int old_fd[2])
{
	int	i;

	i = dup2(new_fd[0], STDIN_FILENO);
	if (i != -1)
		i = dup2(old_fd[1], STDOUT_FILENO);
	ppxb_close_pipe_fd(old_fd);
	ppxb_close_pipe_fd(new_fd);
	if (i == -1)
		return (-1);
	return (0);
}

int	ppxb_last_fork(t_args *ppx_args, int fd[2], int i)
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
		if (ppxb_get_cmd_and_args(ppx_args, &cmd, &args, i) == -1)
			return (-1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ppxb_fork_free(cmd, args));
		ppxb_close_pipe_fd(fd);
		if (write_in_outfile_bns(ppx_args) || execve(cmd, args, ppx_args->envp))
			return (ppxb_fork_free(cmd, args));
	}
	ppxb_close_pipe_fd(fd);
	return (pid);
}
