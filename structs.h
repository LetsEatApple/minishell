/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/02 19:12:10 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_env
// {
//     char    *key;
//     char    *value;
//     struct s_env   *next;
// }   t_env;

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

typedef struct s_token
{
	char			*value;
	char			**cmd;
	//int				node;
	t_token_type	type;
	struct s_token	*next;
	struct s_token  *prev;
}	t_token;

typedef struct s_data
{
	char	*input;
	t_token	*token_list;
	char	**env;
	int		pipes;
	int		redirs;
}	t_data;



