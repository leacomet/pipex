/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_infile_outfile_bns.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:23 by acomet            #+#    #+#             */
/*   Updated: 2023/04/25 14:24:40 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

int	read_in_infile_bns(t_args *ppx_args)
{
	int		i;
	char	*file_name;

	file_name = ppx_args->argv[1];
	i = open(file_name, O_RDONLY);
	if (i == -1)
		return (-1);
	if (dup2(i, STDIN_FILENO) == -1)
	{
		close(i);
		return (-1);
	}
	close(i);
	return (0);
}

int	write_in_outfile_bns(t_args *ppx_args)
{
	int		i;
	char	*file_name;

	file_name = ppx_args->argv[ppx_args->argc - 1];
	if (ft_strcmp(ppx_args->argv[1], "here_doc"))
		i = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		i = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (i == -1)
		return (-1);
	if (dup2(i, STDOUT_FILENO) == -1)
	{
		close(i);
		return (-1);
	}
	close(i);
	return (0);
}
