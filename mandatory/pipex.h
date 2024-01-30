/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:31:00 by acomet            #+#    #+#             */
/*   Updated: 2023/04/21 14:30:52 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../ft_printferr/ft_printferr.h"
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
int		pipex(t_args *ppx_args);
int		check_access_while_no_path(t_args *ppx_args);

	/* forks */
int		ppx_fork_write(t_args *ppx_args, int fd[2]);
int		ppx_fork_read(t_args *ppx_args, int fd[2]);
int		ppx_get_cmd_and_args(t_args *ppx_args, char **cmd, char ***args,
			int i);

	/* infile and outfile */
int		read_in_infile(t_args *ppx_args);
int		write_in_outfile(t_args *ppx_args);

	/* get path */
char	**ppx_get_all_path(char **env);
char	*ppx_get_correct_path(char *cmd_full, char **all_path);
char	*ppx_get_cmd(char *cmd_full);

	/* get args */
char	**ppx_get_args(char *cmd, char *cmd_full);
int		ppx_flags_args_count(char *cmd_full);
int		ppx_get_flags_to_args(char **args, char *cmd_full);
char	*ppx_strdup_one_flag_arg(const char *s);
char	*ppx_strdup_rm_simple_quotes(const char *s);

	/* close */
int		ppx_close_pipe_fd(int fd[2]);

	/* free */
int		ppx_fork_free_close(char *cmd, char **args, int fd[2]);
int		ppx_fork_free(char *cmd, char **args);
void	ppx_free_path(char **path);

#endif
