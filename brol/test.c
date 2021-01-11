#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	if (*s2 == 0 || s2 == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		while (i + j < len && s1[i + j] == s2[j])
		{
			j++;
			if (s2[j] == 0)
				return ((char *)&s1[i]);
		}
		i++;
	}
	return (0);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*dest;
	void	*srcs;
	unsigned char	cc;

	cc = (unsigned char)c;
	dest = dst;
	srcs = (void *)src;
	while (n--)
	{
		if (*srcs == cc)
		{
			*dest = *srcs;
			return (++dest);
		}
		*dest = *srcs;
		dest++;
		srcs++;
	}
	return (0);
}

int main()
{
    printf("\n|%s|\n", ft_strnstr("yo\0", "yo",  3));
    memccpy("coucou", "yoyo", 2, 3);
    /*struct timeval t;
    struct timezone tz;
    long long unsigned int nb;
    gettimeofday(&t, &tz);
    
    nb = t.tv_sec;
    printf("\nminutes =>|%lu|\n", nb);
    usleep(5000000);
    gettimeofday(&t, &tz);
    nb = t.tv_sec;
    printf("\nminutes =>|%lu|\n", nb);*/
    /*printf("\nfull temps =>|%lu|\n", t.tv_sec);
    printf("\nminutes =>|%lu|\n", t.tv_sec / 60);
    printf("\nheures =>|%lu|\n", (t.tv_sec / 60) / 60);
    printf("\njours =>|%lu|\n", ((t.tv_sec / 60) / 60) / 24);
    printf("\nmois =>|%lu|\n", (((t.tv_sec / 60) / 60) / 24) / 30);
    printf("\nannees =>|%lu|\n", ((((t.tv_sec / 60) / 60) / 24) / 30) / 12);*/
    return (0);
}