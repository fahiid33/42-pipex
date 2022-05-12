/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:04:07 by fstitou           #+#    #+#             */
/*   Updated: 2022/05/12 19:44:34 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

size_t	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	write_to_fd1(char *lmt, int *fd)
{
	char	*str;

	close(fd[0]);
	dup2(fd[1], STDOUT);
	str = get_next_line(0);
	while (str)
	{
		if (ft_strncmp(str, lmt, ft_strlen1(lmt)) == 0)
			exit(1);
		write(fd[1], str, ft_strlen1(str));
		free(str);
		str = get_next_line(0);
	}
}

void	here_doc(char *command, char **env, char *lmd)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		write_to_fd1(lmd, fd);
		execute(command, env);
	}
}
