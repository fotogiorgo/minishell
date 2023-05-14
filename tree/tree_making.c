/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_making.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:32:48 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/11 15:19:17 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_type(char *str)
{
	if (ft_strncmp_case_ins(str, "echo", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "cd", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "pwd", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "export", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "unset", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "env", ft_strlen(str)+1) == 0 ||
		ft_strncmp_case_ins(str, "exit", ft_strlen(str)+1) == 0)
			return (BI_EXEC);
	if (*str == '|' && ft_strlen(str) == 1)
		return (PIPE);
	if (ft_strncmp_case_ins(str, "<<", ft_strlen(str)+1) == 0) // here maybe we shouldnt do +1
		return (HEREDOC);
	if ((*str == '>' || *str == '<') && ft_strlen(str) <= 2)
		return (REDIR);
	return (EXEC);
}

static t_tree	*parce_exec(t_argv_vec *argv)
{
	t_tree	*ret;
	int	i;

	i = 0;
	ret = ft_calloc(1, sizeof(t_tree));
	if (ret == NULL)
		exit(1); //should we exit
	ret->type = get_type(argv->argv[0]);
	if(!init_tree_args(ret))
		exit(1);// should we use exit?
	if(!get_args(argv, ret))
		exit(1); //same
	return (ret);
}

static t_tree	*parce_redir(t_argv_vec *argv, t_tree *right_node)
{
	t_tree	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(1, sizeof(t_tree));
	if (ret == NULL)
		return (NULL); // and free rest of the tree cause in make_tree we loe access to it
	ret->argv_for_func = ft_calloc(3, sizeof(char *));
	if (ret->argv_for_func == NULL)
		return (NULL); // same as up free first
	ret->type = get_type(argv->argv[0]);
	ret->argv_for_func[0] = argv->argv[0];
	ret->argv_for_func[1] = argv->argv[1];
	if (!validate_redir_file(ret->argv_for_func[1]))
		return (NULL); // same as up
	argv->argv+=2;
	argv->curr-=2;
	ret->right = right_node;
	add_remainder_to_beginning(argv, right_node);
	return (ret);
}

static t_tree	*parce_pipe(t_argv_vec *argv, t_tree *right_node)
{
	t_tree	*ret;

	ret = ft_calloc(1, sizeof(t_tree));
	ret->type = get_type(argv->argv[0]);
	if(!init_tree_args(ret))
		exit(1);// should we use exit?
	ret->argv_for_func[0] = argv->argv[0];
	argv->argv++;
	argv->curr--;
	ret->right = right_node;
	ret->left = parce_exec(argv);
	return (ret);
}

/* they will segfault here "argv.argv[0]" because argv is not null terminated */
t_tree	*make_tree(t_argv_vec argv)
{
	t_tree	*ret;

	ret = parce_exec(&argv);
	while(argv.curr > 0 && argv.argv[0] && argv.argv[0][0])
	{
		if (argv.argv[0][0] == '|')
			ret = parce_pipe(&argv, ret);
		else
		{
			//printf("hello\n");
			ret = parce_redir(&argv, ret);
			if (ret == NULL)
				return (NULL);
		}
	}
	//print_tree(ret);
	return (ret);
}

/* we have to think about || or | | and shit like that.. for now its handled as an argument */