/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:09:05 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/01/17 14:53:39 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

void run_command(char **command, char *path)
{
	int exec_status;
	int amount_paths = 3;
	int amount_tries = 0;
	char **path_split;
	char **command_args;

	path_split = path_splitter(path);
	command_split = command_split(argv)
	while (amount_tries < amount_paths)
	{
		exec_status = execve(path_split[amount_tries], char *const argv[], char *envp[]);
		amount_tries++;
	}
}

void	child_process(int fd, int *end, char **cmd, char **env)
{
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	
	// run command 
	run_command(cmd, )

	// end[0] = STDOUT_FILENO;

	// output -> end[0] // begin
}

void	parent_process(int fd, char **cmd)
{
	int	status;

	waitpid(-1, &status, 0);
	dup2(fd, STDIN_FILENO); // f2 is the stdout
	dup2(end[0], STDOUT_FILENO); // end[0] is the stdin
	close(end[1])
	close(fd);
	// run command on fd and output
}

void	pipex(int input_fd, int output_fd, char **argv, char **env)
{
	int		end[2];
	pid_t	parent;

	parent = fork();
	pipe(end);
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent) // if fork() returns 0, we are in the child process
		child_process(input_fd, cmd1, end, env);
	else
		parent_process(output_fd, cmd2, end, env);
}

int	main(int argc, char **argv, char **env)
{
	int		input_fd;
	int		output_fd;

	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_fd < 0 || output_fd < 0)
		printf("is fout 1");
	pipex(input_fd, output_fd, argv, env);
	return (1);
}
