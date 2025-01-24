/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/24 17:23:25 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_token_type
{
	SINGLE_QUOTE,			//0
	DOUBLE_QUOTE,			//1
	PIPE,					//2
	REDIR_OUT,				//3
	REDIR_IN,				//4
	REDIR_OUT_APPEND,		//5
	HEREDOC,				//6
	WORD,					//7
	CMD,					//8
	ENV,					//9
	WHITESPACE,				//10
}	t_token_type;

typedef struct s_node
{
	char			*value;
	char			**cmd;
	int				node;
	int				exec;
	t_token_type	type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_token
{
	char			*value;
	char			**cmd;
	t_token_type	type;
	int				file;
	int				arg;
	int				node;
	int				root;
	int				word;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				index;
	int				exp;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_doc
{
	char	*file;
	int		fd;
	char	*delimiter;
}	t_doc;

typedef struct s_data
{
	char	*input;
	char	**env;
	char	*pwd;
	t_env	*e_list;
	int		ops;
	int		pipes;
	int		redirs;
	int		commands;
	int		red_in;
	int		infile;
	int		std_out_fd;
	t_token	*token_list;
	t_node	*root;
	t_doc	doc;
}	t_data;
