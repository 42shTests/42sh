#include "shell.h"

/*
** Display the token list on the logger.
*/

static void	s_print(const t_lexer *lexer)
{
	int i;

	i = 0;
	while (i < lexer->size)
	{
		log_debug("tokens[%d] (TT %d - TC %2d) => \"%s\"", i,
				TOKEN_TYPE(i), TOKEN_CODE(i),
				TOKEN_CONTENT(i));
		i++;
	}
}

/*
** Convert an input string into a token list.
*/

int			lexer(t_parser *parser, const char *in)
{
	int		ret;

	if (!parser || !in)
		return (ST_EINVAL);

	log_info("lexer receives input : `%s'", in);
	
	parser->lexer->size = 0;
	if ((ret = lexer_tokenize(in, parser, parser->lexer)) != ST_OK)
	{
		log_error("tokenization failed (incomplete inhibition)");
		return (ret);
	}
	else
	{
		log_success("tokenization succeded, extract %d tokens", parser->lexer->size);
		s_print(parser->lexer);
	}
	return (ST_OK);
}