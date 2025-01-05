/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/03 15:14:23 by lhagemos         ###   ########.fr       */
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
	WHITESPACE				//10
}	t_token_type;

typedef struct s_node
{
	char			*value;
	char			**cmd;
	int				node;
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

typedef struct s_data
{
	char	*input;
	char	**env;
	char	*pwd;
	t_env	*e_list;
	int		ops;
	int		pipes;
	int		redirs;
	t_token	*token_list;
	t_node	*root;
}	t_data;
