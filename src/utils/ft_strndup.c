
#include "minishell.h"

char	*ft_strndup(char *src, size_t n)
{
	char		*dest;
	size_t		len;
	size_t		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (n < len)
		len = n;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
