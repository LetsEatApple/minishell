/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/04 16:57:36 by grmullin         ###   ########.fr       */
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
//	print_list(data);
	int ops;

	ops = 0;
	if (data->pipes || data->redirs)
	{
		get_root(data);
		ops = data->redirs + data->pipes;
		printf("ops are '%d'\n", ops);
	//	build_AST(data, ops);
	//	exec_AST(data);
	//	printf("root val is '%s' with node val of: '%d'\n", data->root->value, data->root->node);
		clear_table(data);
}
	else
		ft_command(data);
	//printf("data.pipes: '%d' data.redirs: '%d'\n", data->pipes, data->redirs);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	g_signal = 0;
	init_data(&data, ac, envp);
	while ("It's been a")
	{
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		data.input = readline("minihell: ");
		if (data.input == NULL) // EOF (ctrl-D) detected
			break ;
		add_history(data.input);
		if (data.input)
		{
			lexing(&data);
			printf("data.pipes: '%d' data.redirs: '%d'\n", data.pipes, data.redirs);
			init_msh(&data);
		}
	}
	free_data(&data);
	return (g_signal);
}