/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:22 by acomet            #+#    #+#             */
/*   Updated: 2023/03/17 14:13:06 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bns.h"

int	ppxb_close_pipe_fd(int fd[2])
{
	if (fd)
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (-1);
}
