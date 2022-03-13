/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:09:05 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/03/13 19:02:58 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include "pipex.h"
#include "libft.h"

void	run_command(char *cmd, char **env)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	get_path_to_binary(cmd_split, env);
}

void	child_process(int fd, int *end, char *cmd, char **env)
{
	if (dup2(fd, STDIN_FILENO) < 0)
		exit(127);
	if (dup2(end[1], STDOUT_FILENO) < 0)
		exit(127);
	close(end[0]);
	close(fd);
	run_command(cmd, env);
}

void	parent_process(int fd, int *end, char *cmd, char **env)
{
	int	status;

	waitpid(-1, &status, 0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit(127);
	if (dup2(end[0], STDIN_FILENO) < 0)
		exit(127);
	close(end[1]);
	close(fd);
	run_command(cmd, env);
}

int	pipex(int input_fd, int output_fd, char **cmd, char **env)
{
	int		end[2];
	int		status;
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		perror("Fork: ");
	if (!parent)
		child_process(input_fd, end, cmd[2], env);
	else
		parent_process(output_fd, end, cmd[3], env);
	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	int	input_fd;
	int	output_fd;
	int	status;

	status = 0;
	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_fd < 0 || output_fd < 0 || argc != 5)
		return (1);
	if (!*env)
		return (0);
	status = pipex(input_fd, output_fd, argv, env);
	return (status);
}
