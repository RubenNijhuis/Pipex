/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:09:05 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/01/20 17:03:33 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pipex.h>

// void	run_command(char **command, char **env)
// {
// 	// int		exec_status;
// 	// int		amount_paths = 3;
// 	// int		amount_tries = 0;
// 	// char	**path_split;
// 	// char	**command_args;

// 	// path_split = path_splitter(path);
// 	// command_split = command_split(argv);
// 	// while (amount_tries < amount_paths)
// 	// {
// 	(void)command;
// 	char *cmd = {"ls -l"};
// 	execve("/usr/bin", &cmd, env);
// }

void	child_process(int fd, int *end, char *cmd, char **env)
{
	char	**cmd_split;

	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	cmd_split = ft_split(cmd, 32);
	execve("/bin/ls", cmd_split, env);
}

void	parent_process(int fd, int *end, char *cmd, char **env)
{
	int		status;
	char	**cmd_split;

	waitpid(-1, &status, 0);
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd);
	cmd_split = ft_split(cmd, 32);
	execve("/usr/bin/wc", cmd_split, env);
}

void	pipex(int input_fd, int output_fd, char **cmd, char **env)
{
	int		end[2];
	pid_t	parent;

	(void)cmd;
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
		printf("is fout 1");
		return (1);
	}
	pipex(input_fd, output_fd, argv, env);
	return (1);
}
