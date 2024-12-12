# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "Libft/libft.h"

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	int i = 0;
	char **argv;
	char *arg = "";
	char *cmd = "/usr/bin/grep";
	argv = (char **)malloc(sizeof(char *)* 3);
	argv[0] = ft_strdup(arg);
	argv[1] = ft_strdup(cmd);
	argv[3] = NULL;
	//char *argv[] = {"/usr/bin/grep", "", NULL};
	execve(argv[0], argv, env);
	perror("error:");
	return(0);
}

/* int main()
{
	char *s = "$ ";
	if (ft_strncmp("$", s, 2) == 0)
		printf("same\n");
	return (0);
} */