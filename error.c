#include "minishell.h"


void	nb_of_quotes(char *line)
{
	int i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			d_q = 1;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
			{
				d_q = 0;
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			s_q = 1;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
			{
				s_q = 0;
				i++;
			}
		}
		else
			i++;
	}
	if (s_q || d_q)
	{
		free(line);
		printf("syntax error in quotes\n");
		exit(0);
	}
}

void	check_error_pipes(char *line)
{
	int i;

	i = 0;
	if (line[0] == '|')
	{
		free(line);
		printf("parse error near `|'\n");
		exit(0);
	}
	while (line[i])
	{
		if ((line[i] == '|' && !line[i + 1]) || (line[i] == '|' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near `|'\n");
			exit(0);
		}
		if ((line[i] == '<' && line[i + 1] == '|') || (line[i] == '>' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near \"<>|\"\n");
			exit(0);
		}
		i++;
	}
}

void	check_error_redirections(char *line)
{
	int i;

	i = 0;
	// if (line[0] == '|')
	// {
	// 	free(line);
	// 	printf("parse error near `|'\n");
	// 	exit(0);
	// }
	while (line[i])
	{
		if ((line[i] == '<' && !line[i + 1]) || (line[i] == '<' && !line[i + 1]))
		{
			free(line);
			printf("parse error near `<'\n");
			exit(0);
		}
		if ((line[i] == '<' && line[i + 1] == '|') || (line[i] == '>' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near \"<>|\"\n");
			exit(0);
		}
		i++;
	}
}

void	check_error(char *line)
{
	nb_of_quotes(line);
	check_error_pipes(line);
	check_error_redirections(line);
}