/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down_corner.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 03:02:10 by niduches          #+#    #+#             */
/*   Updated: 2020/09/19 03:35:41 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

static uint	resolution_down[6] = {2, 8, 0, 6, 0, 0};

bool	Rubik::down_corner_in_place(uint idx)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	x = this->colors[tab[idx] * 9 + 8];
	uint	y = this->colors[tab[(idx + 1) % 4] * 9 + 6];
	uint	z = this->colors[DOWN * 9 + resolution_down[tab[idx]]];

	return ((x == tab[idx] || x == tab[(idx + 1) % 4] || x == DOWN) &&
		(y == tab[idx] || y == tab[(idx + 1) % 4] || y == DOWN) &&
		(z == tab[idx] || z == tab[(idx + 1) % 4] || z == DOWN));
}

bool	Rubik::all_down_corner_in_place(void)
{
	uint	i;

	i = 0;
	while (i < 4)
	{
		if (!this->down_corner_in_place(i))
			return (false);
		++i;
	}
	return (true);
}

void	Rubik::put_down_corner(void)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	i;

	while (!this->all_down_corner_in_place())
	{
		i = 0;
		while (i < 4)
		{
			if (this->down_corner_in_place(i))
			{
				make_instructions("B' D F D' B D F' D'", tab[i]);
				break ;
			}
			++i;
		}
		if (i == 4)
			make_instructions("B' D F D' B D F' D'");
	}
}
