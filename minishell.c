/*
** EPITECH PROJECT, 2019
** my_strlen.c
** File description:
** count and returns number of characters 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>

static char	*built_in_pwd(void);


typedef struct		s_env
{
	char			*var;		
	struct s_env	*next;
}					t_env;

typedef	struct	s_tab
{
  int		nb;
  int		size;
}		t_tab;

size_t my_strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

char *my_strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;
}

char *my_strrchr(char *s, int c)
{
    char* ret=0;
    do {
        if( *s == (char)c )
            ret=s;
    } while(*s++);
    return ret;
}

char *rm_spaces(char *str)
{
    int i = 0;
    int j = 0;
    char *str_returned = malloc(sizeof(char) * (my_strlen(str) + 10));

    while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
        i++;
    while (str[i] != '\0') {
        if ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0') {
            str_returned[j] = ' ';
            i++;
            j++;
        }
        while((str[i] == ' ' || str[i] == '\t') && str[i] != '\0') {
            i++;
        }
        if (str[i] != '\0') {
            str_returned[j] = str[i];
            i++;
            j++;
        }
    }
	j--;
	for (; j >= 0 && (str_returned[j] == ' ' || str_returned[j] == '\n'); j--);
	str_returned[j+ 1] = '\0';
    return (str_returned);
}

static t_env	*first = NULL;

int my_strncmp( char * s1, const char * s2, size_t n )
{
    while ( n && *s1 && ( *s1 == *s2 ) ) {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 ) {
        return 0;
    }
    else{
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
	}
}

int my_strcmp(const char *string1, char *string2)
{
	int i;
	int difference;
	int length = my_strlen(string1);
	int length2 = my_strlen(string2);
	if (length != length2)
		return 1;
	for (i=0;i< length;i++)
	{
		difference=string1[i]-string2[i];
		if (difference!=0)
		{
			return 1;
		}
	}
	return 0;
}

static char	*get_env_var(char *var)
{
	t_env	*tmp = first;
	size_t	len = 0;

	len = my_strlen(var);

	while (tmp) {
		if (!my_strncmp(var, tmp->var, len)) {
			return (tmp->var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char *my_strdup(char *src) 
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

static char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int c = 0;

    while (dest[i] != '\0')
        i++;

    while (src[c] != '\0') {
        dest[i] = src[c];
        i++;
        c++;
    }
    dest[i] = '\0';
    return (dest);
}

static char *my_strcpy(char *d, char *s) 
{
   char *saved = d;
   while ((*d++ = *s++) != '\0');

   return saved; 
}

int is_charac(char c, char operator)
{	
	if (c == operator)
	    return(0);
	return (1);
}

int	coumpt(char *str, char operator)
{
	int	a = 0;
	int	b = 0;
	while (str[a] != '\0'){
		if (is_charac(str[a], operator) == 1 && is_charac(str[a + 1], operator) != 1){
			b = b + 1;
		}
		a = a + 1;
	}
	return (b + 1);
}

int len_of_word(char *str, int i, char operator)
{
	while (str[i] != '\0') {
                if (is_charac(str[i], operator) != 1)
                        return (i);
                i++;
        }
        return (i);
}

char **my_str_to_word_array(char *str, char operator)
{
	int	y = coumpt(str, operator);
	char	**result = malloc(sizeof(char *) * y + 1);
	int	a = 0;
	int	b = 0;
	int	c = 0;

	while (b < y){
		c = 0;
		result[b] = malloc(sizeof(char) * len_of_word(str, a, operator));
		while (str[a] != '\0' && is_charac(str[a], operator) != 0) {
			result[b][c] = str[a];
			c = c + 1;
			a = a + 1;
		}
		result[b][c] = '\0';
		a = a + 1;
		b = b + 1;

	}
	result[b] = NULL;
	return (result);
}

static void	free_array(char **array)
{
	for (int i = 0; array[i]; i++) {
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

static void	exec_cmd(char **cmd, char **env)
{
	pid_t	pid = 0;
	int		status = 0;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0) {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		if (execve(cmd[0], cmd, env) == -1)
			perror("shell");
		exit(84);
	}
}

static void my_putchar(char c)
{
    write(1, &c, 1);
}


static void my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
}

int built_in_unsetenv(const char *name)
{
    extern char **environ;
    char **ep, **sp;
    size_t len;

    if (name == NULL || name[0] == '\0' || my_strchr(name, '=') != NULL) {
        errno = EINVAL;
        return 84;
    }
	len = my_strlen(name);
	for (ep = environ; *ep != NULL; )
        if (my_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=') {
			for (sp = ep; *sp != NULL; sp++)
                *sp = *(sp + 1);
		} 
		else {
            ep++;
        }

    return 0;
}

static bool	get_absolute_path(char **cmd, char **env)
{
	char	*path = NULL;
	char	*bin = NULL;
	char	**path_split = NULL;
	size_t	idx = 0;
	
	if (cmd[0][0] != '/' && my_strncmp(cmd[0], "./", 2) != 0) {
		for (int i = 0; env[i]; i++) {
			if (!my_strncmp(env[i], "PATH=", 5)) {
				path = my_strdup(&env[i][5]);
				break ;
			}
		}
		if (path == NULL)
			return (false);
		path_split = my_str_to_word_array(path, ':');
		free(path);
		path = NULL;
		for (idx = 0; path_split[idx]; idx++) {
			bin = malloc(sizeof(char)*((my_strlen(path_split[idx]) + 1 + my_strlen(cmd[0]) + 1)));
			if (bin == NULL)
				break ;
			my_strcat(bin, path_split[idx]);
			my_strcat(bin, "/");
			my_strcat(bin, cmd[0]);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
	return (bin == NULL ? false : true);
}

static bool	is_built_in(char *cmd)
{
	const char	*built_in[] = {"cd", "unsetenv", "exit", NULL};

	for (int i = 0; built_in[i]; i++) {
		if (!my_strcmp(built_in[i], cmd))
			return (true);
	}
	return (false);
}

static void	built_in_cd(char *path)
{
	char	*oldpwd = NULL;
	char	*pwd = NULL;
	char	*pwd_ptr = NULL;

	if (path == NULL)
		return;
	if (chdir(path) == 0) {
		pwd = my_strrchr(get_env_var("PWD="), '=') + 1;
		if (oldpwd != NULL && pwd != NULL) {
			my_strcpy(oldpwd, pwd);
		}
		if (pwd != NULL) {
			pwd = &pwd[-my_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			my_strcpy(pwd, pwd_ptr);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	} else {
		perror("chdir");
	}
}

int built_in_exit()
{
  exit(0);
}

static char	*built_in_pwd(void)
{
	char	*cwd = NULL;

	cwd = malloc(sizeof(char)*(PATH_MAX + my_strlen("PWD=") + 1));
	if (cwd == NULL)
		return (NULL);
	if (getcwd(&cwd[4], PATH_MAX) == NULL) {
		perror("getcwd()");
	}
	return (cwd);
}

static void	exec_built_in(char **built_in)
{
	if (!my_strcmp(built_in[0], "pwd")){
		my_putstr(get_env_var("PWD="));
		my_putchar('\n');
	}
	else if (!my_strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
	else if (!my_strcmp(built_in[0], "unsetenv"))
		built_in_unsetenv(built_in[1]);
	else if (!my_strcmp(built_in[0], "exit"))
		built_in_exit();
	
}

static void	add_tail(char *var)
{
	t_env	*ptr = first;
	t_env	*new_node = NULL;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL) {
		my_putstr("Alloc failure\n");
		return ;
	}
	new_node->var = var;
	new_node->next = NULL;
	if (ptr == NULL) {
		first = new_node;
	} else {
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

static void	dup_env(char **envp)
{
	char *var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	
	for (int i = 0; envp[i]; i++) {
		add_tail(my_strdup(envp[i]));
		if (!my_strncmp(envp[i], "PATH", 4)) 
			var_lst[0] = NULL;
		else if (!my_strncmp(envp[i], "HOME", 4)) 
			var_lst[1] = NULL;
		else if (!my_strncmp(envp[i], "OLDPWD", 6)) 
			var_lst[2] = NULL;
		else if (!my_strncmp(envp[i], "PWD", 3)) 
			var_lst[3] = NULL;
		else if (!my_strncmp(envp[i], "SHLVL", 5)) 
			var_lst[4] = NULL;
	}
}

static char	**lst_to_array()
{
	char	**array = NULL;
	t_env	*tmp = first;
	size_t	idx = 0;

	while (tmp) {
		idx++;
		tmp= tmp->next;
	}
	array = malloc(sizeof(char *)*(idx + 1));
	if (array == NULL) {
		perror("calloc");
		exit(-1);
	}
	tmp = first;
	idx = 0;
	while (tmp) {
		array[idx] = tmp->var;
		tmp = tmp->next;
		idx++;
	}
	return (array);
}

static void	free_lst(void)
{
	t_env	*idx = first;
	t_env	*tmp = idx;

	while (idx != NULL) {
		tmp = idx;
		idx = idx->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

int is_pipe(char *str)
{
	return 0;
}

int size(char **args)
{
	int i ;

	for(i = 0; args[i]; i++);
	return i;

}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;
	char	**cmd = NULL;
	char	**env = NULL;
	char *cleanstr = NULL;
	char **param = NULL;
	int count = 0;
	char **cdparam = NULL;

	dup_env(envp);
	buffer = malloc(sizeof(char)*(buf_size));
	if (buffer == NULL) {
		perror("Malloc failure");
		return (84);
	}
	write(1, "$> ", 3);
	while (getline(&buffer, &buf_size, stdin) > 0) {
		cleanstr = rm_spaces(buffer);
		cmd = my_str_to_word_array(cleanstr, ';');

		if (cmd[0] == NULL) {
			write(2, "Command not found\n", 19);
			return (84);
		}
		for(int i = 0; cmd[i] ; i++){
			cmd[i] = rm_spaces(cmd[i]);
			if(is_pipe(cmd[i]) == 1){
				return 0;
			}
			else if (is_built_in(my_str_to_word_array(cmd[i], ' ')[0]) == true) {
				cdparam = my_str_to_word_array(rm_spaces(cmd[i]), ' ');
				exec_built_in(cdparam);
			}
			else {
				env = lst_to_array();
				param = my_str_to_word_array(rm_spaces(cmd[i]), ' ');
				if (get_absolute_path(param, env) == true) {
					exec_cmd(param, env);
				}
			}
		free(env);
		env = NULL;
	}
		write(1, "$> ", 3);
		free_array(cmd);
	}
	free_lst();
	my_putstr("Bye \n");
	free(buffer);
	(void)argc;
	(void)argv;
	return (0);
}