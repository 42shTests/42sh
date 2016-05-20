#include "shell.h"

/*
** This function takes a job t_job as argument and iterates
** on its process list to launch them sequentially.
** It handles pipes and redirections.
*/

static int			s_fork_it(t_job *j, t_proc *p)
{
	// before callback built-in
	p->pid = fork();
	if (p->pid < 0)
		return (ST_FORK);
	else if (p->pid == 0)
		proc_launch(j, p);
	else
	{
		if (shell_is_interactive() == 1)
		{
			if (j->pgid == 0)
				j->pgid = p->pid;
			if (setpgid(p->pid, j->pgid) < 0)
				return (ST_SETPGID);
		}
	}
	return (ST_OK);
}

int					job_launch(t_job *j)
{
	int				ret;
	t_list			*pos;
	t_list			*head;
	t_proc			*p;
	int				job_pipe[2];
	int				outputs[3];

	job_pipe[0] = -1;
	outputs[STDIN_FILENO] = j->stdin;
	outputs[STDERR_FILENO] = j->stderr;
	head = &j->proc_head;
	pos = head;
	LIST_FOREACH(head, pos)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		if (pos->next != head)
		{
			if (pipe(job_pipe) < 0)
				exit(ST_PIPE);
			outputs[STDOUT_FILENO] = job_pipe[STDOUT_FILENO];
		}
		else
			outputs[STDOUT_FILENO] = j->stdout;

		p->stdin = outputs[STDIN_FILENO];
		p->stdout = outputs[STDOUT_FILENO];
		p->stderr = outputs[STDERR_FILENO];
		if ((ret = s_fork_it(j, p)) != ST_OK)
			return(ret);

		if (outputs[STDIN_FILENO] != j->stdin)
			close(outputs[STDIN_FILENO]);
		if (outputs[STDOUT_FILENO] != j->stdout)
			close(outputs[STDOUT_FILENO]);
		outputs[STDIN_FILENO] = job_pipe[0];

		// useful if we need to keep last process alive:
		//if (p->next == NULL)
		//	break ;
	}
	if (shell_is_interactive() == 0)
	{
	//	wait for job to complete
	//	after callback built-in
	}
	else if (j->foreground == 1)
	{
		job_foreground(j, 0);
	//	put job to foreground
	//	after callback built-in
	}
	//else
	//	put job to background
	return (ST_OK);
}
