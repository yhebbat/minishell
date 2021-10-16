#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			i;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && ss1[i] == ss2[i])
		i++;
	return (ss1[i] - ss2[i]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	char				*res;
	const char			*acpy;

	i = 0;
	res = dest;
	acpy = src;
	if (res == NULL && acpy == NULL)
		return (0);
	if (ft_memcmp(res, acpy, n) != 0)
	{
		while (i < n)
		{
			res[i] = acpy[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dst;
	char		*ssrc;

	dst = (char *)dest;
	ssrc = (char *)src;
	if (dest == NULL && src == NULL)
		return (0);
	if (ssrc > dst)
		ft_memcpy(dst, ssrc, n);
	else
	{
		dst = (char *)dest + (n - 1);
		ssrc = (char *)src + (n - 1);
		while (n > 0)
		{
			*(dst--) = *(ssrc--);
			n--;
		}
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int		ss1;
	unsigned int		ss2;
	char				*new;

	ss1 = 0;
	ss2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[ss1] != '$')
		ss1++;
	while (s2[ss2] != '\0')
		ss2++;
	if (!(new = (char *)malloc((ss1 + ss2 + 1) * sizeof(char))))
		return (0);
	ft_memmove(new, s1, ss1);
	ft_memmove(new + ss1, s2, ss2);
	new[ss1 + ss2] = '\0';
	return (new);
}

char	*ft_strdup(const char *s)
{
	size_t	k;
	char	*new;
	size_t	i;

	i = 0;
	k = 0;
	while (s[k] != '\0')
		k++;
	if (!(new = (char *)malloc((k + 1) * sizeof(char))))
		return (0);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}