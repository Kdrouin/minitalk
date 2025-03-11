/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadrouin <kadrouin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:13:01 by kadrouin          #+#    #+#             */
/*   Updated: 2025/03/11 18:13:01 by kadrouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*calloc_char(int size)
{
	char *tab;
	int i;

	i = 0;
	tab = (char *)malloc(size * sizeof(char));
	if (!tab)
		return (0);
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

void	*ft_realloc(char *ptr, size_t old_size, size_t new_size)
{
	char	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
		new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}

void	*ft_memcpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
