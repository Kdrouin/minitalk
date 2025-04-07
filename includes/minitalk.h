/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:48:17 by kadrouin          #+#    #+#             */
/*   Updated: 2025/04/05 20:48:17 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

void	send_char(int server_pid, unsigned char c);
void	handle_signal(int sig);
int		ft_atoi(const char *str);
char	*calloc_char(int size);
void	*ft_realloc(char *ptr, size_t old_size, size_t new_size);
void	*ft_memcpy(char *dest, char *src, size_t n);

#endif
