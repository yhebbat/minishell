#include <stdio.h>
#include <stdlib.h>

typedef	struct	s_file
{
	char	*filename;
	int		type;
	struct	t_file	*next; 
}t_file;

typedef struct s_cmds
{
	// redirections;
	char	**args;
	int		d_q;
	int		s_q;
	char	*cmd;
	struct	t_file	*file;
	struct	s_cmds	*next;
	struct	s_cmds	*prec;
}t_cmds;

typedef struct s_headers
{
	// struct s_env	*env_h;
	// struct s_env	*env_f;
	struct s_cmds	*cmd_h;
	struct s_cmds	*cmd_f;
}t_headers;

char	*add_str(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static	int	ft_mots(char const *s, char c)
{
	int			i;
	int			k;
	int			p;
    int         d_q;
    int         s_q;

    d_q = 0;
    s_q = 0;
	i = 0;
	k = 0;
	p = 1;
	if (*s)
	{
		while (s[i])
		{
			if (s[i] == '"')
			{
				i++;
				while (s[i] && s[i] != '"')
					i++;
			}
			if (s[i] == c)
				p = 1;
			else if (p == 1 && !d_q)
			{
				p = 0;
				k++;
			}
			i++;
		}
	}
    return (k);
}

static void	*ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (0);
}

static int	ft_alpha(char const *s, char c, int i)
{
	int	r;

	r = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
			{
				r++;
				i++;
			}
			i++;
		}
		else
		{
			r++;
			i++;
		}
	}
	return (r);
}

static char	**ft_remp(char **p, char const *s, char c, int mots)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && mots > j)
	{
		k = 0;
		while (s[i] == c)
			s++;
		p[j] = malloc(sizeof(char) * ft_alpha(s, c, i) + 1);
		if (!p[j])
			return (ft_freee(p));
		while (s[i] && s[i] != c)
        {
            if (s[i] == '"')
            {
                i++;
                while (s[i] != '"')
                {
		        	p[j][k] = s[i];
					k++;
					i++;
                }
                i++;
            }
			else
				p[j][k++] = s[i++];
        }
		p[j][k] = '\0';
		j++;
	}
	p[j] = 0;
	return (p);
}

void	ft_addbotcmd(t_headers *head, char *val)
{
	t_cmds	*stack;
	t_cmds	*to_add;

	to_add = malloc(sizeof(t_cmds));
	if (!to_add)
		exit(0);
	if (head->cmd_h == NULL)
	{
		to_add->cmd = add_str(val);
		// to_add->val = add_str(val);
		to_add->next = NULL;
		to_add->prec = NULL;
		head->cmd_f = to_add;
		head->cmd_h = to_add;
	}
	else
	{
		stack = head->cmd_f;
		// to_add->var = add_str(var);
		to_add->cmd = add_str(val);
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->cmd_f = to_add;
	}
}

char	**ft_flex(char const *s, char c)
{
	char	**p;
	int		mots;

	if (s == NULL)
		return (0);
	mots = ft_mots(s, c);
	p = malloc(sizeof(char *) * (mots + 1));
	if (!p)
		return (0);
	return (ft_remp(p, s, c, mots));
}

int	main(int ac, char **av)
{
    (void)ac;
	t_headers *head;
	t_cmds		*test;
    // char    **test;
    int     i = 0;

	head->cmd_h = NULL;
	ft_addbotcmd(head, "\" test| \" | ls");
	ft_addbotcmd(head, "\" test| \"");
	// test->cmd = "\" test| \" | ls";
	test = head->cmd_h;
	while (test)
	{
		test->args = ft_flex(test->cmd, ' ');
		test = test->next;
	}
	test = head->cmd_h;
	while (test)
	{
		int i = 0;
		while (test->args[i])
    	{
       		printf("%s\n", test->args[i]);
        	i++;
    	}
		printf("---------------\n");
		test = test->next;
	}
    // while (test[i])
    // {
    //     printf("%s\n", test[i]);
    //     i++;
    // }
    ft_freee(test->args);
    // var = "test | \"test|ls\"";
	// var = getenv("SHELL");
	// printf("la valeur de PATH est %s\n", var);
    // printf("%d\n%s\n",ft_mots(var, '|'), var);
    // printf("%d\n%s\n",ft_mots(var, '|'), var);
    // printf("%d\n%s\n",ft_alpha(var, '|', 0), var);

    
}
