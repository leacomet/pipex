/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_here_doc_bns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:32:01 by acomet            #+#    #+#             */
/*   Updated: 2023/06/10 15:49:57 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

int	ppxb_here_doc(t_args *ppx_args, int fd[2], int *pid)
{
	int		fd_here_doc[2];
	int		i;

	if (ppx_args->argc < 6 || pipe(fd_here_doc) == -1)
		return (-1);
	i = 6;
	if (ppxb_here_doc_to_pipe(ppx_args, fd_here_doc, pid) || pipe(fd) == -1)
		return (ppxb_close_pipe_fd(fd_here_doc));
	pid[1] = ppxb_first_fork_here_doc(ppx_args, fd_here_doc, fd);
	if (pid[1] == -1)
	{
		ppxb_close_pipe_fd(fd);
		return (ppxb_close_pipe_fd(fd_here_doc));
	}
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

int	ppxb_here_doc_to_pipe(t_args *ppx_args, int fd_here_doc[2], int *pid)
{
	char	*str;
	char	*limiter;

	pid[0] = fork();
	if (pid[0] == -1)
		return (-1);
	if (pid[0] == 0)
	{
		str = ft_strdup("\0");
		if (!str)
			return (ppxb_close_pipe_fd(fd_here_doc));
		limiter = ft_strjoin(ppx_args->argv[2], "\n");
		if (!limiter)
			return (ppxb_close_pipe_fd(fd_here_doc));
		str = ppxb_get_here_doc_str(str, limiter);
		if (!str || dup2(fd_here_doc[1], STDOUT_FILENO) == -1)
			return (ppxb_close_pipe_fd(fd_here_doc));
		ppxb_close_pipe_fd(fd_here_doc);
		ft_printf("%s", str);
		free(str);
		free(pid);
		ppxb_free_path(ppx_args->all_path);
		exit(0);
	}
	return (0);
}

char	*ppxb_get_here_doc_str(char *str, char *limiter)
{
	char	*gnl;
	char	*temp;

	gnl = get_next_line(0);
	while (gnl && ft_strcmp(limiter, gnl))
	{
		temp = str;
		str = ft_strjoin_firstarg_free(str, gnl);
		if (!str)
		{
			if (temp)
				free(temp);
			get_next_line(-2);
			free(limiter);
			return (NULL);
		}
		free(gnl);
		gnl = get_next_line(0);
	}
	get_next_line(-2);
	if (gnl)
		free(gnl);
	free(limiter);
	return (str);
}

int	ppxb_first_fork_here_doc(t_args *ppx_args, int fd_here_doc[2], int fd[2])
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
		if (ppxb_get_cmd_and_args(ppx_args, &cmd, &args, 3) == -1)
			return (-1);
		if (ppxb_fork_here_doc_fd_dup(fd, fd_here_doc) == -1
			|| execve(cmd, args, ppx_args->envp) == -1)
			return (ppxb_fork_free(cmd, args));
	}
	ppxb_close_pipe_fd(fd_here_doc);
	return (pid);
}

int	ppxb_fork_here_doc_fd_dup(int fd[2], int fd_here_doc[2])
{
	if (dup2(fd_here_doc[0], STDIN_FILENO) == -1
		|| dup2(fd[1], STDOUT_FILENO) == -1)
		return (-1);
	ppxb_close_pipe_fd(fd_here_doc);
	ppxb_close_pipe_fd(fd);
	return (0);
}
