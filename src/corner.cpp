/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:26:29 by niduches          #+#    #+#             */
/*   Updated: 2020/09/17 22:02:03 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

static uint	resolution_corner_up[6] = {8, 2, 0, 0, 6, 0};
static uint	resolution_corner_down[6] = {2, 8, 0, 6, 0, 0};

void	Rubik::put_corner_down(uint face)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	i;
	uint	idx;

	idx = 4;
	i = 0;
	while (i < 4)
	{
		if (tab[i] == face)
		{
			idx = i;
			break ;
		}
		++i;
	}
	if (idx == 4)
		return ;
	i = 0;
	while (i < 4)
	{
		uint	x = (uint)(this->colors[UP * 9 + resolution_corner_up[tab[i]]]);
		uint	y = (uint)(this->colors[tab[i] * 9 + 2]);
		uint	z = (uint)(this->colors[tab[(i + 1) % 4] * 9]);

		if ((x == UP || x == face || x == tab[(idx + 1) % 4]) &&
			(y == UP || y == face || y == tab[(idx + 1) % 4]) &&
			(z == UP || z == face || z == tab[(idx + 1) % 4])) 
		{
			make_instructions(std::string(Rubik::instructions_name[tab[i]]) + " D " +
			std::string(Rubik::instructions_name[tab[i]]) + "\'");
			return ;
		}
		++i;
	}
}

void	Rubik::put_corner_in_face(uint face)
{
	uint		tab[4] = {FRONT, RIGHT, BACK, LEFT};
	std::string	rotation[4] = {"", " D'", " D2", " D"};
	int			offset[4] = {0, 3, 2, 1};
	uint		idx;
	uint		i;

	idx = 4;
	i = 0;
	while (i < 4)
	{
		if (tab[i] == face)
		{
			idx = i;
			break ;
		}
		++i;
	}
	if (idx == 4)
		return ;
	i = 0;
	while (i < 4)
	{
		uint	x = (uint)(this->colors[DOWN * 9 + resolution_corner_down[tab[i]]]);
		uint	y = (uint)(this->colors[tab[i] * 9 + 8]);
		uint	z = (uint)(this->colors[tab[(i + 1) % 4] * 9 + 6]);

		if ((x == UP || x == face || x == tab[(idx + 1) % 4]) &&
			(y == UP || y == face || y == tab[(idx + 1) % 4]) &&
			(z == UP || z == face || z == tab[(idx + 1) % 4]))
		{
			make_instructions(rotation[(i + offset[idx]) % 4]);
			return ;
		}
		++i;
	}
}

void	Rubik::put_corner(uint face)
{
	//TODO check 3 face
	if ((uint)(this->colors[face * 9 + 2]) == face &&
	(uint)(this->colors[UP * 9 + resolution_corner_up[face]]) == UP)
		return ;
	this->put_corner_down(face);
	this->put_corner_in_face(face);
	if ((uint)(this->colors[DOWN * 9 + resolution_corner_down[face]]) == UP)
		make_instructions("F D' F' R' D2 R", face);
	else if ((uint)(this->colors[face * 9 + 8] == UP))
		make_instructions("F D F'", face);
	else
		make_instructions("D F D' F'", face);
}

void	Rubik::put_corners(void)
{
	this->put_corner(FRONT);
	this->put_corner(RIGHT);
	this->put_corner(BACK);
	this->put_corner(LEFT);
}
