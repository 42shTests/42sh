#include "shell.h"

int			key__cut_to_end_of_line(t_termcaps_context *in_context)
{
	size_t	selection_start;
	size_t	selection_end;

	if (in_context->state != STATE_REGULAR)
		return (1);
	selection_start = in_context->command.offset;
	selection_end =
		in_context->command.size - in_context->command.offset;
	key__share__cut_build_copy(in_context,
								selection_start,
								selection_end);
	return (1);
}
