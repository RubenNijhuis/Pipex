/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path_to_binary.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/20 19:33:38 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/01/20 23:08:38 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pipex.h>
#include <stdio.h>

static char **get_global_path_split(char **env)
{
	int		i;
	char	*path;
	char **	path_split;
	char *path_clean;
	size_t id_length;

	id_length = 5;
	i = 0;
	while (env[i] != (void *)0)
	{
		if (ft_strncmp(env[i], "PATH=", id_length) == 0)
			path = env[i];
		i++;
	}
	path_clean = ft_substr(path, id_length, ft_strlen(path) - id_length);
	path_split = ft_split(path_clean, 58);
	return (path_split);
}

char	*get_path_to_binary(char **cmd, char **env)
{
	char **global_path_split;
	int i;
	char *working_cmd;

	i = 0;
	global_path_split = get_global_path_split(env);
	while(global_path_split[i] != 0)
	{
		working_cmd = ft_strjoin(global_path_split[i], ft_strjoin("/", cmd[0]));
		if (execve(working_cmd, cmd, env) != -1)
			break;
		free(working_cmd);
		i++;
	}
	return (working_cmd);
}
