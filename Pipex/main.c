/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:48:23 by lhagemos          #+#    #+#             */
/*   Updated: 2024/11/08 10:47:31 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pro	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Error: Too few/many arguments passed!\n", 2);
		return (1);
	}
	ft_memset(&pipex, 0, sizeof(t_pro));
	check_files(&pipex, av);
	collect_data(&pipex, av, env);
	ft_pipe(&pipex);
	free_memory(pipex);
	return (0);
}
