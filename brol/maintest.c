#include <stdlib.h>
#include <stdio.h>


int ft_strlen(char *str)
{
    int i;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int		nb_len(int nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	utos(int nb, char *str, int i)
{
	if (nb > 9)
	{
		utos(nb / 10, str, i - 1);
	}
	str[i] = nb % 10 + '0';
}

char	*print_join(int time, int order, char *msg)
{
	int		len_time;
	int		len_order;
	char	*str;
	int		i;

	len_time = nb_len(time);
	len_order = nb_len(order);
	if (!(str = (char *)malloc(len_time + len_order + ft_strlen(msg) + 2))) //1 for \0 and 1 for the space bewteen time and order
		return (NULL);
	utos(time, str, len_time - 1);
	str[len_time] = ' ';
	len_order += len_time;
	utos(order, str, len_order);
	i = 0;
	len_order += 1;
	while (msg[i])
		str[len_order++] = msg[i++];
	str[len_order] = '\0';
	return (str);
}

int main()
{
    long long unsigned int time;
    int order;
    char *str;

    time = 0;
    order = 4;
    str = print_join((int)time, order, " has taken a fork");
    printf("mgs ==> |%s|", str);
    free(str);
}