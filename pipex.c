/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:59:04 by mclerico          #+#    #+#             */
/*   Updated: 2022/09/06 12:17:52 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getpath(char **envp, char *cmd)
{
	int		i;
	char	**dirs;
	char	*slash;

	i = 0;
	if (!access(cmd, F_OK))
		return (cmd);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
			 break ;
		envp++;
	}
	if (!*envp)
		return (cmd);
	*envp += 5;
	dirs = ft_split(*envp, ':');
	slash = ft_strjoin("/", cmd);
	i = 0;
	while (dirs[i] && access(ft_strjoin(dirs[i], slash), F_OK))
		i++;
	if (!dirs[i])
		return ("");
	return (ft_strjoin(dirs[i], slash));
}

void	ft_1st_proc(int f1, int end[2], char *cmd, char **envp)
{
	char	**cmd1;
	char	*command;

	close(end[0]);
	dup2(f1, STDIN_FILENO);
	close(f1);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	cmd1 = ft_split(cmd, ' ');
	command = ft_getpath(envp, cmd1[0]);
	execve(command, cmd1, envp);
	perror(cmd1[0]);
	ft_free_split(cmd1);
	exit(1);
}

void	ft_2nd_proc(int f2, int end[2], char *cmd, char **envp)
{
	char	**cmd1;
	char	*command;

	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(f2, STDOUT_FILENO);
	close(f2);
	cmd1 = ft_split(cmd, ' ');
	command = ft_getpath(envp, cmd1[0]);
	execve(command, cmd1, envp);
	perror(cmd1[0]);
	ft_free_split(cmd1);
	exit(1);
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	int		end[2];
	pid_t	p;

	pipe(end);
	p = fork();
	if (p < 0)
		return ;
	if (p == 0)
		ft_2nd_proc(f2, end, argv[3], envp);
	else
		ft_1st_proc(f1, end, argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;

	if (argc != 5)
		return (1);
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 1)
	{
		perror(argv[1]);
		return (1);
	}
	if (f2 < 1)
	{
		perror(argv[4]);
		return (1);
	}
	pipex(f1, f2, argv, envp);
}
