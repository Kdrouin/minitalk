/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:58:02 by kadrouin          #+#    #+#             */
/*   Updated: 2025/03/10 20:58:02 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile sig_atomic_t g_ready = 0; 

static void handle_server_ack(int sig)
{
	if (sig == SIGUSR1)
	{
		g_ready = 1;
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("\n✅ Message sent successfully\n");
		exit(0);
	}
}

void	send_char(int server_pid, unsigned char c)
{
	int				i;
	unsigned char	t_char;

	i = 8;
	t_char = c;
	while (i > 0)
	{
		i--;
		t_char = c >> i;
		if (t_char % 2 == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		g_ready = 0;
		while (!g_ready)
			pause();
	}
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*message;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(2, "Usage : ./client <PID du serveur> <Message>\n", 45);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		write(2, "Invalid PID\n", 12);
		return (1);
	}
	ft_printf("Server PID : %d\n", server_pid);
	signal(SIGUSR1, handle_server_ack);
	signal(SIGUSR2, handle_server_ack);
	while (argv[2][i])
		send_char(server_pid, argv[2][i++]);
	send_char(server_pid, '\0');
	ft_printf("Message : %s\n", message = argv[2]);
	return (0);
}
