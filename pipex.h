/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 02:43:28 by fahd              #+#    #+#             */
/*   Updated: 2022/04/25 00:12:02 by fstitou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1

int		openfile(char *filename, int MODE);
int		ft_strchr(char *str, char c);
int		ft_strncmp(char *s1, char *s2, int n);
void	execute(char *command, char **env);
void	redirection(char *command, char **env, int fdin);
char	*ft_strndup(char *str, unsigned int n);
char	*str_join(char *s1, char *s2);
char	**ft_splitcpy(const char *s, char c, char **str, int wd);
int		ft_charcount(const char *s, char c, int i);
int		ft_words(char const *s, char c);
void	*ft_freedom(char **str);
char	**ft_splitcpy(const char *s, char c, char **str, int wd);
char	**ft_split(char const *s, char c);
void	wrong_cmd(char *cmd);
void	here_doc(char *command, char **env, char *lmd);

#endif
