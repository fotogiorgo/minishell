/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:10:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/10 17:23:50 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_path(char *path, char *command)
{
	int		size;
	char	*ret;
	int		access_bool;
	
	size = ft_strlen(path) + ft_strlen(command) + 2;
	ret = malloc(size);
	if (ret == NULL)
		return (NULL); //does it have to exit?
	ft_strlcpy(ret, path, size);
	ft_strlcat(ret, "/", size);
	ft_strlcat(ret, command, size);
	access_bool = access(ret, F_OK | X_OK);
	if (access_bool == 0)
		return (ret);
	free(ret);
	return (NULL);
}

/* remember to free split and in exec_ve the ret of this func*/
char	*get_path(char	*command)
{
	char	**split_paths;
	char	*paths;
	char	*ret;
	int		i;

	i = 0;
	ret = 0;
	if(access(command, F_OK | X_OK) == 0)
		return (command);
	paths = get_value_from_key("PATH");
	if (paths == NULL)
		return (NULL);
	split_paths = ft_split(paths, ':');
	free(paths);
	if (split_paths == NULL)
		return (NULL);
	while (split_paths[i] && ret == 0)
	{
		ret = check_path(split_paths[i], command);
		i++;
	}
	//free_split();
	return (ret);
}