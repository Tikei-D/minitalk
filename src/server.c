/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-dana <tel-dana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:39:22 by tel-dana          #+#    #+#             */
/*   Updated: 2022/12/17 15:02:00 by tel-dana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	joined = malloc (sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	tmp = joined;
	while (*s1)
		*(tmp++) = *(s1++);
	while (*s2)
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (joined);
}

static void	handler(int sig, siginfo_t *info, void	*ucontext)
{
	static int	bit;
	static int	c;
	static char	*s = "";

	(void) ucontext;
	if (sig == SIGUSR1)
		c |= (128 >> bit);
	bit++;
	if (bit == 8)
	{
		s = ft_strjoin(s, (char *)&c);
		if (c == '\0')
		{
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
			free(s);
			s = "";
			kill(info->si_pid, SIGUSR1);
		}
		bit = 0;
		c = 0;
	}	
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;

	(void) argv;
	if (argc != 1)
	{
		printf("Error. Please enter correct number of arguments\n");
		printf("Type: ./server\n");
	}
	printf("PID: %d\n", getpid());
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
