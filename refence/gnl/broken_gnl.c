#include "broken_gnl.h"

// valida no while while s[i] for diferente de \0
char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

//mudar para incremental
//dest e src[i]
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

// se não tiver s retorna
size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	if(!s)
		return 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

// valida se tem *s1, e retorna 0 se não tiver
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	if(*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}
// Já está correta
int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}


/*
ft_memmove
1. adicionar: size_t i;

2. Trocar: if (dest > src)
   Por:    if (dest == src || n == 0)

3. Trocar: return (ft_memcpy(dest, src, n));
   Por:    return (dest);

4. Trocar: else if (dest == src)
   Por:    if (dest < src)

5. Trocar: return (dest);
   Por:    return (ft_memcpy(dest, src, n));

6. adicionar: i = n;

7. Trocar: while (i >= 0)
   Por:    while (i > 0)

8. inverter ordem: i--; vem primeiro
*/
void *ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

    if (dest == src || n == 0)
        return (dest);
    if (dest < src)
		return (ft_memcpy(dest, src, n));
	i = n;
    while (i > 0)
    {
        i--;
        ((char *)dest)[i] = ((char *)src)[i];
    }
    return (dest);
}
/*
A função ft_memmove recebe um destino, uma origem e a quantidade de bytes para copiar.
Se dest == src ou n == 0, retorna dest.
Se dest < src, usa ft_memcpy para copiar normalmente.
Caso contrário, copia os bytes de trás para frente usando um loop com i.
No final, retorna dest.
*/




/*get_next_line
1. Trocar:  char *tmp = ft_strchr(b, '\n');
   Por:     char *tmp;

2. adicionar: int read_ret;

3. Trocar:  while (!tmp)
   Por:     while (!(tmp = ft_strchr(b, '\n')))

3. Trocar:  int read_ret = read(fd, b, BUFFER_SIZE);
   Por:     read_ret = read(fd, b, BUFFER_SIZE);

4. Trocar:  
		if (read_ret == -1)
			return (NULL);
   Por:     
		if (read_ret <= 0)
        {
            b[0] = '\0';
            if (read_ret == -1 || !ret || !*ret)
            {
                free(ret);
                return (NULL);
            }
            return (ret);
        }

5. Trocar:  b[read_ret] = 0;
   Por:     b[read_ret] = '\0';

6. adicionar (antes do return): ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
*/ 
char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;
	char	*tmp;
	int		read_ret;

	while (!(tmp = ft_strchr(b, '\n')))
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			b[0] = '\0';
			if (read_ret == -1 || !ret || !*ret)
			{
				free(ret);
				return (NULL);
			}
			return(ret);
		}
			
		b[read_ret] = '\0';
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return (ret);
}

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}