/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmullin <grmullin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:43:17 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/25 13:33:30 by grmullin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	add_history(data->input);
	ft_command(data);
}

int main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	(void)envp;
	init_data(&data, ac, envp);
	while (1)
	{
		if (data.input)
			free(data.input);
		signal(SIGINT, handle_sig);
		signal(EOF, handle_sig);
		data.input = readline("minihell: ");
		if (data.input == NULL) // EOF (ctrl-D) detected
			break ;
		init_msh(&data);
	}
	rl_clear_history();
	free_data(&data);
	return 0;
}