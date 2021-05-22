/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:30:52 by niduches          #+#    #+#             */
/*   Updated: 2020/09/19 12:09:06 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

void	Rubik::cross(void)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	pos[4][2] = {{1, 5}, {5, 7}, {3, 7}, {1, 3}};
	uint	i;

	if (this->colors[DOWN * 9 + 1] == DOWN && this->colors[DOWN * 9 + 7] == DOWN &&
	this->colors[DOWN * 9 + 3] == DOWN && this->colors[DOWN * 9 + 5] == DOWN)
		return ;
	i = 0;
	while (i < 4)
	{
		if (this->colors[DOWN * 9 + pos[i][0]] != DOWN &&
		this->colors[DOWN * 9 + pos[i][1]] != DOWN)
			this->make_instructions("R D F D' F' R'", tab[i]);
		++i;
	}
	if (this->colors[DOWN * 9 + 1] == DOWN && this->colors[DOWN * 9 + 7] == DOWN &&
	this->colors[DOWN * 9 + 3] == DOWN && this->colors[DOWN * 9 + 5] == DOWN)
		return ;
	if (this->colors[DOWN * 9 + 1] == DOWN && this->colors[DOWN * 9 + 7] == DOWN)
	{
		this->make_instructions("R F D F' D' R'");
		return ;
	}
	if (this->colors[DOWN * 9 + 5] == DOWN && this->colors[DOWN * 9 + 3] == DOWN)
	{
		this->make_instructions("R F D F' D' R'", LEFT);
		return ;
	}
}

static uint	get_idx(uint color, uint *tab)
{
	uint	i;

	i = 0;
	while (i < 4)
	{
		if (tab[i] == color)
			return (i);
		++i;
	}
	return (0);
}

void	Rubik::good_cross(void)
{
	uint	tab[4] = {FRONT, RIGHT, BACK, LEFT};
	uint	pos[4] = {0, 2, 3, 3};
	uint	pos_double[4] = {0, 1, 1, 2};
	uint	i;
	uint	j;
	uint	idx = get_idx(this->colors[FRONT * 9 + 7], tab);
	bool	good;

	good = true;
	j = 1;
	while (j < 4 && good)
	{
		if (this->colors[tab[j] * 9 + 7] !=
		static_cast<char>(tab[(idx + j) % 4]))
			good = false;
		++j;
	}
	if (good)
		return ;
	i = 0;
	while (i < 4)
	{
		idx = get_idx(this->colors[tab[i] * 9 + 7], tab);
		good = true;
		j = 1;
		while (j < 4 && good)
		{
			if (this->colors[tab[(i + j + pos[j]) % 4] * 9 + 7] !=
			static_cast<char>(tab[(idx + j) % 4]))
				good = false;
			++j;
		}
		if (good)
		{
			make_instructions("L D2 L' D' L D' L'", tab[i]);
			return ;
		}

		good = true;
		j = 1;
		while (j < 4 && good)
		{
			if (this->colors[tab[(i + j + pos_double[j]) % 4] * 9 + 7] !=
			static_cast<char>(tab[(idx + j) % 4]))
				good = false;
			++j;
		}
		if (good)
		{
			make_instructions("L D2 L' D' L D' L' L D2 L' D' L D' L'", tab[i]);
			return ;
		}
		++i;
	}
	make_instructions("L D2 L' D' L D' L'", FRONT);
	make_instructions("L D2 L' D' L D' L'", BACK);
	make_instructions("L D2 L' D' L D' L'", BACK);
}

void	Rubik::put_cross_in_face(void)
{
	uint		tab[4] = {FRONT, RIGHT, BACK, LEFT};
	std::string	rotation[4] = {"", " D'", " D2", " D"};
	uint		i;

	i = 0;
	while (i < 4)
	{
		if ((uint)(this->colors[tab[i] * 9 + 7]) == FRONT)
		{
			make_instructions(rotation[i]);
			return ;
		}
		++i;
	}
}
