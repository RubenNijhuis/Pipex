/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:57:28 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/01/20 16:25:24 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
// void	pipex(int input_fd, int output_fd, char **cmd, char **env)
char	**ft_split(char const *s, char c);

#endif