/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:17:39 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/30 14:21:09 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_token_type
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	REDIR_OUT,
	REDIR_IN,
	REDIR_OUT_APPEND,
	HEREDOC,
	WORD,
	CMD,
	ENV,
	WHITESPACE,
}	t_token_type;

typedef struct s_node
{
	char			*value;
	char			**cmd;
	int				node;
	t_token_type	type;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*prev;
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
	int		red_in;
	int		infile;
	int		outfile;
	int		heredoc;
	t_token	*token_list;
	t_node	*root;
	t_doc	doc;
}	t_data;
