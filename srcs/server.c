/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelnyk <dmelnyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:52:41 by dmelnyk           #+#    #+#             */
/*   Updated: 2025/01/02 16:52:41 by dmelnyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

void	server_startup_message(void)
{
	ft_printf(
		" _______ _       _             _  "
		"_         ______                               \n"
		"(_______|_)     (_)  _        | |"
		"| |       / _____)                              \n"
		" _  _  _ _ ____  _ _| |_ _____| || "
		"|  _   ( (____  _____  ____ _   _ _____  ____ \n"
		"| ||_|| | |  _ \\| (_   _|____ | |"
		"| |_/ )   \\____ \\| ___ |/ ___) | | | ___ |/ ___)\n"
		"| |   | | | | | | | | |_/ ___ | |"
		"|  _ (    _____) ) ____| |    \\ V /| ____| |    \n"
		"|_|   |_|_|_| |_|_|  \\__)_____|\\_"
		")_| \\_)  (______/|_____)_|     \\_/ |_____)_|    \n\n"
		);
}

int	process_bit(int sig, int *bit, int *res)
{
	if (sig == SIGUSR1)
		*res |= 1 << *bit;
	*bit += 1;
	if (*bit == 8)
	{
		write(1, res, 1);
		*res = 0;
		*bit = 0;
		return (1);
	}
	return (0);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static sig_atomic_t	last_pid;
	static int			bit;
	static int			res;

	(void)context;
	if (last_pid != info->si_pid && last_pid)
	{
		bit = 0;
		res = 0;
		last_pid = info->si_pid;
	}
	else
		last_pid = info->si_pid; 
	if (process_bit(sig, &bit, &res))
		last_pid = 0;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	server_startup_message();
	ft_printf("%i\n", pid);
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
		pause();
	return (0);
}
