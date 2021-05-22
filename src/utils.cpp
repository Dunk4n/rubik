/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:25:29 by niduches          #+#    #+#             */
/*   Updated: 2020/09/14 00:26:10 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

int		Rubik::strncmp(const char *s1, const char *s2, size_t n) const
{
	size_t	i;

	if ((!s1 && !s2) || !n)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		Rubik::strlen(const char *str) const
{
	uint	i;

	i = 0;
	while (*str)
	{
		++str;
		++i;
	}
	return (i);
}
