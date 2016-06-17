#include "shell.h"

/*
** Allocate a new processus with default values.
*/

t_proc	*proc_alloc(char **envp)
{
	t_proc	*p;

	if (!(p = ft_memalloc(sizeof(t_proc))))
		return (NULL);
	p->command = NULL;
	if ((p->envp = ft_array_dup(envp)) == NULL)
		return (NULL);
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->signaled = 0;
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	p->exit_status = EXIT_SUCCESS;
	p->bltin_char = NULL;
	p->bltin_status = ST_OK;
	INIT_LIST_HEAD(&p->bltin_opt_head);
	return (p);
}