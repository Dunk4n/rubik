/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 09:41:44 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 17:25:41 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

static uint	resolution_down[6] = {2, 8, 0, 6, 0, 0};

bool	Rubik::down_corner_in_right_place(uint idx)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};

	return (((uint)this->colors[tab[idx] * 9 + 8] == tab[idx] &&
			(uint)this->colors[tab[(idx + 1) % 4] * 9 + 6] == tab[(idx + 1) % 4] &&
			this->colors[DOWN * 9 + resolution_down[tab[idx]]] == DOWN));
}

bool	Rubik::all_down_corner_in_right_place(void)
{
	uint	i;

	i = 0;
	while (i < 4)
	{
		if (!this->down_corner_in_right_place(i))
			return (false);
		++i;
	}
	return (true);
}

void	Rubik::put_right_down_corner(void)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	i;

	while (!this->all_down_corner_in_right_place())
	{
		i = 0;
		while (i < 4)
		{
			if (!this->down_corner_in_right_place(i))
			{
				if (!this->down_corner_in_right_place((i + 3) % 4))
					make_instructions("R D2 R' D' R D' R' L' D2 L D L' D L", tab[(i + 3) % 4]);
				else
					make_instructions("R D2 R' D' R D' R' L' D2 L D L' D L", tab[i]);
				break;
			}
			++i;
		}
	}
}

void	Rubik::resolve(void)
{
	this->solution = "";
	if (this->disp)
		this->display_color();
	if (this->chose_sol == 1)
	{
		this->format();
		return ;
	}
	this->sol = true;
	this->put_edges();
	this->put_corners();
	this->put_belges();
	this->cross();
	this->good_cross();
	this->put_cross_in_face();
	this->put_down_corner();
	this->put_right_down_corner();
}
