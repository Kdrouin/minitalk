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
	ft_printf("%s\n", str);
	free(str);
	str = NULL;
}

static void handle_char(char *str, int str_len, unsigned char current_char)
{
	str = ft_realloc(str, str_len, str_len + 1);
	if (!str)
	{
		ft_printf("Memory allocation failed\n");
		exit(1);
	}
	str[str_len - 1] = current_char;
	str_len++;
	if (current_char == '\0')
		ft_printnf(str);
	current_char = 0;
}

void	handle_signal(int sig)
{
	static unsigned char	current_char;
	static int				bit_index;
	static char				*str = NULL;
	static int				str_len = 0;

	if (!str)
	{
		str = calloc_char(1);
		str_len = 1;
	}
	current_char |= (sig == 10);
	bit_index++;
	if (bit_index == 8)
	{
		handle_char(str, str_len, current_char);
		bit_index = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	ft_printf("Serveur démarré avec PID : %d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
