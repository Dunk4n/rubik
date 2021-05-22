/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   belge.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 00:08:02 by niduches          #+#    #+#             */
/*   Updated: 2020/09/18 17:13:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

static uint	resolution_belge_down[6] = {1, 5, 0, 7, 3, 0};

void	Rubik::put_belge_down(uint face, uint idx)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	i;

	i = 0;
	while (i < 4)
	{
		uint	x = (uint)(this->colors[tab[i] * 9 + 5]);
		uint	y = (uint)(this->colors[tab[(i + 1) % 4] * 9 + 3]);

		if ((x == face && y == tab[(idx + 1) % 4]) ||
		(x == tab[(idx + 1) % 4] && y == face))
		{
			make_instructions("D' R' D R D F D' F'", tab[i]);
			return ;
		}
		++i;
	}
}

bool	Rubik::put_belge_in_face(uint face, uint idx)
{
	uint		tab[4] = {FRONT, RIGHT, BACK, LEFT};
	std::string	rotation[4] = {"", " D'", " D2", " D"};
	int			offset[4] = {0, 3, 2, 1};
	uint		i;

	i = 0;
	while (i < 4)
	{
		uint	x = (uint)(this->colors[tab[i] * 9 + 7]);
		uint	y = (uint)(this->colors[DOWN * 9 + resolution_belge_down[tab[i]]]);

		if (x == face && y == tab[(idx + 1) % 4])
		{
			make_instructions(rotation[(i + offset[idx]) % 4]);
			return (true);
		}
		if (y == face && x == tab[(idx + 1) % 4])
		{
			make_instructions(rotation[(i + offset[(idx + 1) % 4]) % 4]);
			return (false);
		}
		++i;
	}
	return (true);
}

void	Rubik::put_belge(uint face)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	idx;

	idx = 0;
	while (idx < 4)
	{
		if (tab[idx] == face)
			break ;
		++idx;
	}
	if ((uint)(this->colors[face * 9 + 5]) == face &&
	(uint)(this->colors[tab[(idx + 1) % 4] * 9 + 3]) == tab[(idx + 1) % 4])
		return ;
	this->put_belge_down(face, idx);
	if (this->put_belge_in_face(face, idx))
		this->make_instructions("D' R' D R D F D' F'", face);
	else
		this->make_instructions("D L D' L' D' F' D F", tab[(idx + 1) % 4]);
}

void	Rubik::put_belges(void)
{
	this->put_belge(FRONT);
	this->put_belge(RIGHT);
	this->put_belge(BACK);
	this->put_belge(LEFT);
}
