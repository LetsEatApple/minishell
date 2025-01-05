#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* 
int	main()
{
	char		*pwd;
    char        *buffer;
    size_t      size;

    size = 10;
    buffer[size];
	pwd = getcwd(buffer, size);
    printf("%s\n", pwd);
    return (0);
}
 */
int main() 
{
	char	*pwd;
	char	*save;
	char	buffer[1024];

	save = getcwd(buffer, sizeof(buffer));
	printf("%s\n", save);
    int i;
    i = chdir(""); 
    if ( i < 0)
        perror("error: ");
    printf("i= %d\n", i);
    save = getcwd(buffer, sizeof(buffer));
	printf("%s\n", save);
    
    return 0;
}