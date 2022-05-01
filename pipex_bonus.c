/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 08:07:00 by fahd              #+#    #+#             */
/*   Updated: 2022/05/01 13:28:21 by fahd             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, filename, ft_strchr(filename, 0));
			write(STDERR, ": No such file or directory\n", 28);
			return (STDIN);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && ft_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr(path, ':'));
		bin = str_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strchr(path, ':') + 1;
	}
	return (cmd);
}

void	execute(char *command, char **env)
{
	char	**ac;
	char	*path;

	if (command[0] != '\0')
		ac = ft_split(command, ' ');
	else
	{
		wrong_cmd(command);
		exit(127);
	}
	path = get_path(ac[0], env);
	execve(path, ac, env);
	wrong_cmd(command);
}

void	redirection(char *command, char **env, int filein)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit(2);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		if (filein == STDIN)
			exit(2);
		execute(command, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	filein;
	int	fileout;
	int	i;

	i = 2;
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac == 6)
	{
		fileout = openfile(av[ac - 1], OUTFILE);
		dup2(fileout, STDOUT);
		here_doc(av[3], env, av[2]);
		execute(av[4], env);
	}
	else if (ac >= 5)
	{
		filein = openfile(av[1], INFILE);
		fileout = openfile(av[ac - 1], OUTFILE);
		dup2(filein, STDIN);
		dup2(fileout, STDOUT);
		while (i < ac - 2)
			redirection(av[i++], env, filein);
		execute(av[ac - 2], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	return (1);
}
