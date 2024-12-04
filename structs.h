/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/04 12:46:31 by grmullin         ###   ########.fr       */
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
	ENV_VAR,				//8
	WHITESPACE,				//9
}	t_token_type;

typedef struct s_node
{
	char			*value;
	int				node;
	t_token_type	type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_token
{
	char			*value;
	char			**cmd;
	int				node;
	int				root;
	t_token_type	type;
	struct s_token	*next;
	struct s_token  *prev;
}	t_token;

typedef struct s_data
{
	char	*input;
	char	**env;
	int		pipes;
	int		redirs;
	t_token	*token_list;
	t_node	*root;
}	t_data;



