/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/09 17:27:25 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_signal = 0;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("sigquit\n");
	}
}

void	init_msh(t_data *data)
{
	pid_t	exec;
	int 	ops;

	exec = 0;
	ops = 0;
	if (data->pipes || data->redirs)
	{
		get_root(data);
		ops = data->redirs + data->pipes;
		build_ast(data, ops);
		ft_init(data->root, data->env);
		clear_table(data);
	}
	else
	{
		exec = fork();
		if (exec == 0)
		{
			ft_command(data->input, data->env);
			exit (EXIT_SUCCESS);
		}
		waitpid(exec, NULL, 0);
	}
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	g_signal = 0;
	init_data(&data, ac, envp);
	signal(SIGINT, handle_sig);
	signal(EOF, handle_sig);
	while ("It's been a")
	{
		data.input = readline("minihell: ");
		if (data.input == NULL) // EOF (ctrl-D) detected
			break ;
		if (data.input)
			add_history(data.input);			
		lexing(&data);
		init_msh(&data);
	}
	free_data(&data);
	return (g_signal);
}

void print_tree(t_node *node, int level)
{
	if (node == NULL)
		return;
	print_tree(node->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	printf("Node Value: %s, Type: %s\n", node->value, get_token_type(node->type));
	print_tree(node->left, level + 1);
}

const char *g_token_type[] = {
    "SINGLE_QUOTE",
    "DOUBLE_QUOTE",
    "PIPE",
    "REDIR_OUT",
    "REDIR_IN",
    "REDIR_OUT_APPEND",
    "HEREDOC",
    "WORD",
    "ENV_VAR",
    "WHITESPACE",
};

const char* get_token_type(t_token_type type) {
    if (type >= 0 && type <= WHITESPACE)  // Ensure the type is within valid range
        return g_token_type[type];
    return "UNKNOWN";  // Fallback for invalid types
}
