#include "shell.h"
	

static	int		s_environment_default(char **env)
{
	env = (char **)malloc(sizeof(char *) * 2); // A definir
	env[0] = ft_strdup("DEFAULT=DEFAULT");
	env[1] = NULL;
	return (0);
}


int		environment_init(t_sh *sh, const char *envp[])
{
	int i;

	i = 0;
	if (envp[i] == NULL)
	{
		s_environment_default(sh->envp);
		return (1); // Set Default return
	}
	while (envp[i])
		i++;
	sh->envp = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i])
	{			
		 if ((sh->envp[i] = ft_strdup(envp[i])) == NULL)
		 {
		 	log_fatal("ft_strdup failded because of insuffisant memory availale");
		 	return (-ST_MALLOC);
		 }
//	ft_putendl_fd(sh->envp[i], 1);
		 i++;
	}
	sh->envp[i] = NULL;
	return (ST_OK);
}