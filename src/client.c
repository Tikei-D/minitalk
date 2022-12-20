/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-dana <tel-dana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:02:11 by tel-dana          #+#    #+#             */
/*   Updated: 2022/12/17 14:56:12 by tel-dana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	size_t	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

static void	server_acknowledge(int sig, siginfo_t *info, void *ucontext)
{
	(void) info;
	(void) ucontext;
	if (sig == SIGUSR1)
	{
		write(1, "Data Received\n", 14);
		exit (0);
	}
	else
	{
		write(1, "Signal Error\n", 13);
		exit (1);
	}
}

static	void	compare_and_send(pid_t pid, char *data)
{
	int	i;
	int	bit;

	i = 0;
	while ((i && data[i - 1]) || i == '\0')
	{
		bit = 128;
		while (bit > 0)
		{
			if (bit & data[i])
				kill (pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit /= 2;
			usleep (300);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sigact;

	if (argc != 3)
	{
		printf("Error. Wrong number of arguments\n");
		printf("Type: ./client [PID] [Data]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	sigact.sa_sigaction = server_acknowledge;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	compare_and_send(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
