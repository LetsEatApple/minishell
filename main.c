/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2025/01/30 10:41:17 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_signal = 0;

void	handle_sig(int sig)
{
	g_signal = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("sigquit\n");
	}
}

void	init_msh(t_data *data)
{
	lexing(data);
	if (data->token_list != NULL)
		preparsing(data);
	if (data->token_list != NULL)
	{
		if (list_size(data->token_list) == 2 && (data->redirs || data->pipes))
			handle_two_tokens(data);
		else if (data->pipes || data->redirs)
		{
			get_root(data);
			parsing(data);
			execute(data, data->root);
			clear_table(data);
		}
		else
			ft_command(data, data->token_list->cmd);
	}
	add_history(data->input);
	free_data(data);
}

void	clear_program(t_data *data)
{
	free_split(data->env);
	free(data->pwd);
	clear_elist(&data->e_list);
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;

	(void)av;
	g_signal = 0;
	init_data(&data, ac, envp);
	while (42)
	{
		set_sig_interactive();
		signal(SIGINT, handle_sig);
		data.input = readline("minishell: ");
		if (data.input == NULL)
		{
			printf("\n");
			break ;
		}
		set_sig_noninteractive();
		if (data.input)
			init_msh(&data);
	}
	clear_program(&data);
	return (g_signal);
}
