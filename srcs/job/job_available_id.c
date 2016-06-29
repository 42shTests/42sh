/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_available_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	job_available_id(void)
{
	int		id;
	int		exists;
	t_list	*j_pos;
	t_job	*j;

	id = 0;
	while (++id)
	{
		exists = 0;
		j_pos = (t_list*)&g_current_jobs_list_head;
		while ((j_pos = j_pos->next) && j_pos != &g_current_jobs_list_head)
		{
			j = CONTAINER_OF(j_pos, t_job, list_job);
			if (j->id == id)
			{
				exists = 1;
				break ;
			}
		}
		if (exists == 0)
			break ;
	}
	return (id);
}
