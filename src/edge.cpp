/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:43:47 by niduches          #+#    #+#             */
/*   Updated: 2020/09/17 17:44:22 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

static uint	resolution_edge_up[6] = {7, 5, 0, 1, 3, 0};
static uint	resolution_edge_down[6] = {1, 5, 0, 7, 3, 0};

void	Rubik::put_edge_down(uint face)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	i;

	i = 0;
	while (i < 4)
	{
		if (((uint)(this->colors[UP * 9 + resolution_edge_up[tab[i]]]) == UP &&
		(uint)(this->colors[tab[i] * 9 + 1]) == face) ||
		((uint)(this->colors[UP * 9 + resolution_edge_up[tab[i]]]) == face &&
		(uint)(this->colors[tab[i] * 9 + 1]) == UP))
		{
			make_instructions(std::string(Rubik::instructions_name[tab[i]]) + "2");
			return ;
		}
		++i;
	}
	i = 0;
	while (i < 4)
	{
		if (((uint)(this->colors[tab[i] * 9 + 5]) == UP &&
		(uint)(this->colors[tab[(i + 1) % 4] * 9 + 3]) == face) ||
		((uint)(this->colors[tab[i] * 9 + 5]) == face &&
		(uint)(this->colors[tab[(i + 1) % 4] * 9 + 3]) == UP))
		{
			make_instructions(std::string(Rubik::instructions_name[tab[(i + 1) % 4]]) +
			"\' D " + std::string(Rubik::instructions_name[tab[(i + 1) % 4]]));
			return ;
		}
		++i;
	}
}

void	Rubik::put_edge_in_face(uint face)
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
		if (((uint)(this->colors[DOWN * 9 + resolution_edge_down[tab[i]]]) == UP &&
		(uint)(this->colors[tab[i] * 9 + 7]) == face) ||
		((uint)(this->colors[DOWN * 9 + resolution_edge_down[tab[i]]]) == face &&
		(uint)(this->colors[tab[i] * 9 + 7]) == UP))
		{
			make_instructions(rotation[(i + offset[idx]) % 4]);
			return ;
		}
		++i;
	}
}

void	Rubik::put_edge(uint face)
{
	if ((uint)(this->colors[face * 9 + 1]) == face &&
	(uint)(this->colors[UP * 9 + resolution_edge_up[face]]) == UP)
		return ;
	this->put_edge_down(face);
	this->put_edge_in_face(face);
	if ((uint)(this->colors[face * 9 + 7]) == UP)
		make_instructions("D' R L' F R' L", face);
	else
		make_instructions("R L' F2 R' L", face);
}

void	Rubik::put_edges(void)
{
	this->put_edge(FRONT);
	this->put_edge(RIGHT);
	this->put_edge(BACK);
	this->put_edge(LEFT);
}
