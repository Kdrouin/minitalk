/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:37:05 by kadrouin          #+#    #+#             */
/*   Updated: 2025/04/09 14:37:05 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_printnf(char *str)
{
	ft_printf("%s", str);
	free(str);
	str = NULL;
}

static void	handle_char(char **str, int *str_len,
				unsigned char *current_char, int pid)
{
	*str = ft_realloc(*str, *str_len, *str_len + 1);
	if (!*str)
	{
		ft_printf("Memory allocation failed\n");
		exit(1);
	}
	(*str)[*str_len - 1] = *current_char;
	(*str_len)++;
	if (*current_char == '\0')
	{
		ft_printnf(*str);
		if (kill(pid, SIGUSR2) == -1)
			ft_printf("Error sending signal to client");
		*str = NULL;
		*str_len = 0;
	}
	*current_char = 0;
}

static void	handle_sigint(char *str)
{
	if (str)
		free(str);
	ft_printf("\nServer stopped by SIGINT.\n");
	exit(0);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	current_char;
	static int				bit_index;
	static char				*str;
	static int				str_len;
	pid_t					pid;

	(void)context;
	pid = info->si_pid;
	if (!str)
		init_server_vars(&str, &str_len, &current_char, &bit_index);
	if (sig == SIGINT)
		handle_sigint(str);
	current_char |= (sig == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		handle_char(&str, &str_len, &current_char, pid);
		bit_index = 0;
	}
	else
		current_char <<= 1;
	usleep(100);
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server Started \nPID : %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		pause();
	return (0);
}
