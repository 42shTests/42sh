#include "shell.h"

void	proc_free(t_proc **p)
{
	t_option	*opt;
	t_list		*pos;
	t_list		*safe;
	t_list		*head;

	head = &(*p)->bltin_opt_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		opt = CONTAINER_OF(pos, t_option, list_option);
		option_free(&opt);
	}

	if ((*p)->stdin != 0)
	{
		log_info("closing non-standard stdin (%d)", (*p)->stdin);
		close ((*p)->stdin);
	}
	if ((*p)->stdout != 1)
	{
		log_info("closing non-standard stdin (%d)", (*p)->stdout);
		close ((*p)->stdout);
	}
	if ((*p)->stderr != 2)
	{
		log_info("closing non-standard stderr (%d)", (*p)->stderr);
		close ((*p)->stderr);
	}

	ft_memdel_tab((void ***)&(*p)->argv);
	ft_memdel_tab((void ***)&(*p)->envp);
	ft_memdel((void **)&(*p)->command);
	ft_memdel((void **)&(*p)->bltin_char);
	ft_memdel((void **)&(*p));
	*p = NULL;
}
