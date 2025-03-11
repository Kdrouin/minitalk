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

void	send_char(pid_t server_pid, unsigned char c)
{
	int i;
	unsigned char t_char;

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
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;
	int		i;

	i = 0;
	if (argc != 3)
	{
		write(2, "Usage : ./client <PID du serveur> <Message>\n", 45);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	ft_printf("Server PID : %d\n", server_pid);
	ft_printf("Message : %s\n", message = argv[2]);
	while (message[i])
	{
		send_char(server_pid, message[i]);
		ft_printf("Sent : %c\n", message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
