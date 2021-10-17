#include "minishell.h"


int	nb_of_quotes(char *line)
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
		// free(line);
		printf("syntax error in quotes\n");
		return (1);
	}
	return (0);
}

int	check_error_pipes(char *line)
{
	int i;
	int	d_q;
	int	k;

	d_q = 0;
	i = 0;
	while(line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		// free(line);
		printf("parse error near `|'\n");
		return (1);
	}
	while (line[i])
	{
		if (line[i] == '"')
			d_q++;
		if ((line[i] == '|' && !line[i + 1]) || (line[i] == '|' && line[i + 1] == '|' && d_q % 2 == 0))
		{
			// free(line);
			printf("parse error near `|'\n");
			return (1);
		}
		if ((d_q % 2 == 0 &&(line[i] == '<' || line[i] == '>') && line[i + 1] == '|'))
		{
			// free(line);
			printf("parse error near \"<>|\"\n");
			return (1);
		}
		if(line[i] == '|')
		{
			k = i + 1;
			while(line[k] == ' ')
				k++;
			if (line[k] == '\0')
			{
				printf("parse error near `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_error_redirections(char *line)
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
			// free(line);
			printf("parse error near `<'\n");
			return (1);
		}
		// if ((line[i] == '<' && line[i + 1] == '|') || (line[i] == '>' && line[i + 1] == '|'))
		// {
		// 	free(line);
		// 	printf("parse error near \"<>|\"\n");
		// 	exit(0);
		// }
		i++;
	}
	return (0);
}

int	check_error(char *line)
{
	if (nb_of_quotes(line))
		return (1);
	else if (check_error_pipes(line))
		return (1);
	else if (check_error_redirections(line))
		return (1);
	else
		return (0);
}