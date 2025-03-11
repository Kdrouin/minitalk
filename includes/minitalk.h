/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:00:36 by kadrouin          #+#    #+#             */
/*   Updated: 2025/03/10 20:00:36 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/ft_printf.h"

# define BUFFER_SIZE 1024
# define TIMEOUT 10000

void	handle_signal(int sig);
void	send_char(pid_t server_pid, unsigned char c);
char	*ft_itoa(pid_t num);
int		ft_atoi(const char *str);
char	*ft_strcpy(char *dest, char *src);
void	ft_add_char(char *str);
char	*calloc_char(int size);
void	*ft_memcpy(char *dest, char *src, size_t n);
void	*ft_realloc(char *ptr, size_t old_size, size_t new_size);

#endif

