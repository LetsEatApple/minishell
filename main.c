/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/12/13 13:18:37 by grmullin         ###   ########.fr       */
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
	lexing(data);
	if (data->token_list != NULL)
	{
		preparsing(data);
		if (data->pipes || data->redirs)
		{
			get_root(data);
			parsing(data);
			execute(data->root, data->env);
			clear_table(data);
		}
		else if (data->token_list->type != ENV)
		{
//			printf("type is '%s'\n", get_token_type(data->token_list->type));
			ft_command(data->token_list->cmd, data->env);
		}
	}
	free_data(data);
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
		if (data.input == NULL)
		{
			printf("\n");
			break ;
		}
		add_history(data.input);
		if (data.input)
			init_msh(&data);
	}
	free_split(data.env);
	rl_clear_history();
	return (g_signal);
}
