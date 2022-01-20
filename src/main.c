/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:09:05 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/01/20 20:10:19 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pipex.h>

void	run_command(char *cmd, char **env)
{
	char	**cmd_split;
	char	*path_to_binary;

	cmd_split = ft_split(cmd, 32);
	path_to_binary = get_path_to_binary(cmd_split, env);
	execve(path_to_binary, cmd_split, env);
}

void	child_process(int fd, int *end, char *cmd, char **env)
{
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	run_command(cmd, env);
}

void	parent_process(int fd, int *end, char *cmd, char **env)
{
	int	status;

	waitpid(-1, &status, 0);
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd);
	run_command(cmd, env);
}

void	pipex(int input_fd, int output_fd, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	parent = fork();
	pipe(end);
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent)
		child_process(input_fd, end, cmd[2], env);
	else
		parent_process(output_fd, end, cmd[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int	input_fd;
	int	output_fd;

	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_fd < 0 || output_fd < 0 || argc != 5)
	{
		perror("File: ");
		return (1);
	}
	pipex(input_fd, output_fd, argv, env);
	return (1);
}
