/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bns.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:31:00 by acomet            #+#    #+#             */
/*   Updated: 2023/05/03 15:29:43 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BNS_H
# define PIPEX_BNS_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../ft_printferr/ft_printferr.h"
# include "../get_next_line/get_next_line.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;	
	char	**all_path;
}	t_args;

	/* main */
int		pipex_bns(t_args *ppx_args, int *pids);

	/* initialize */
int		initialize_struct(t_args *ppx_args, int argc, char **argv,
			char **envp);
int		*initialize_pid(int argc);

	/* forks */
int		ppxb_first_fork(t_args *ppx_args, int fd[2]);
int		ppxb_get_cmd_and_args(t_args *ppx_args, char **cmd, char ***args,
			int i);
int		ppxb_middle_fork(t_args *ppx_args, int old_fd[2], int i);
int		ppxb_middle_fork_next_fd(int new_fd[2], int old_fd[2]);
int		ppxb_last_fork(t_args *ppx_args, int fd[2], int i);

	/* path */
char	**ppxb_get_all_path(char **env);
char	*ppxb_get_correct_path(char *cmd_full, char **all_path);
char	*ppxb_get_cmd(char *cmd_full);

	/* get args */
char	**ppxb_get_args(char *cmd, char *cmd_full);
int		ppxb_flags_args_count(char *cmd_full);
int		ppxb_get_flags_to_args(char **args, char *cmd_full);
char	*ppxb_strdup_one_flag_arg(const char *s);
char	*ppxb_strdup_rm_simple_quotes(char const *s);

	/* infile outfile */
int		read_in_infile_bns(t_args *ppx_args);
int		write_in_outfile_bns(t_args *ppx_args);

	/* here doc */
int		ppxb_here_doc(t_args *ppx_args, int fd[2], int *pid);
int		ppxb_here_doc_to_pipe(t_args *ppx_args, int fd_here_doc[2], int *pid);
char	*ppxb_get_here_doc_str(char *str, char *limiter);
int		ppxb_first_fork_here_doc(t_args *ppx_args, int fd_here_doc[2],
			int fd[2]);
int		ppxb_fork_here_doc_fd_dup(int fd[2], int fd_here_doc[2]);

	/* free */
void	ppxb_free_path(char **all_path);
int		ppxb_fork_free_close(char *cmd, char **args, int fd[2]);
int		ppxb_fork_free(char *cmd, char **args);

	/* close */
int		ppxb_close_pipe_fd(int fd[2]);

#endif
