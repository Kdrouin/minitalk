/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:02:31 by kadrouin          #+#    #+#             */
/*   Updated: 2025/03/10 20:02:31 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_printnf(char *str)
{
	ft_printf("%s", str);
	free(str);
	str = NULL;
}

static void	handle_char(char **str, int *str_len, unsigned char *current_char, int pid)
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
		kill(pid, SIGUSR2);
		*str = NULL;
		*str_len = 0;
		kill(pid, SIGUSR2);
	}
	*current_char = 0;
}

static void	error_sig_str(char *str, int sig, int str_len, int current_char, int bit_index)
{
	if (!str && sig == 0)
	{
		str = calloc_char(1);
		str_len = 1;
		current_char = 0;
		bit_index = 0;
	}
	if (sig == SIGINT)
	{

		free(str);
		ft_printf("\nServeur arrêté.\n");
		exit(0);
	}
	exit(1);
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
	if (sig == SIGINT)
		error_sig_str(0, sig, 0, 0, 0);
	if (!str)
		error_sig_str(str, 0, str_len, current_char, bit_index);
	current_char |= (sig == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		handle_char(&str, &str_len, &current_char, pid);
		bit_index = 0;
		kill(pid, SIGUSR1);
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	ft_printf("Serveur démarré avec PID : %d\n", getpid());
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
