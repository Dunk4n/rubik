/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rubik.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:01:00 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 00:32:46 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include "Rubik.hpp"

Rubik::Rubik(void)
{
	this->disp = false;
	this->sol = false;
	this->solution = "";
	this->instruction = "";
	this->size = 3;
	this->graphique = false;
	this->human_readable = false;
	this->chose_sol = 1;
	this->nb_cube = this->size * this->size * this->size -
	(this->size - 2) * (this->size - 2) * (this->size - 2);
	this->center = (this->size - 1) * 0.5f;
	this->cubes = new Cube[this->nb_cube];
	this->colors = new char[this->size * this->size * 6];
	this->init_cubes();
	this->init_color();
}

Rubik::Rubik(char *instructions)
{
	this->size = 3;
	this->disp = false;
	this->instruction = instructions;
	this->graphique = false;
	this->human_readable = false;
	this->sol = false;
	this->solution = "";
	this->chose_sol = 1;
	this->nb_cube = this->size * this->size * this->size -
	(this->size - 2) * (this->size - 2) * (this->size - 2);
	this->center = (this->size - 1) * 0.5f;
	this->cubes = new Cube[this->nb_cube];
	this->colors = new char[this->size * this->size * 6];
	this->init_cubes();
	this->init_color();
	if (instructions)
		this->make_instructions(instructions);
}

Rubik::~Rubik(void)
{
	if (this->colors)
		delete[] this->colors;
	if (this->cubes)
		delete[] this->cubes;
}

void	Rubik::display_solution(void)
{
	std::cout << this->solution << std::endl;
	if (this->graphique)
		this->make_window();
}

void	Rubik::set_generateur(int nb)
{
	std::string	tab[] = {"F ", "F2 ", "F' ", "B ", "B2 ", "B' ", "R ", "R2 ", "R' ", "L ", "L2 ", "L' ", "U ", "U2 ", "U' ", "D ", "D2 ", "D' "};
	std::string	instructions = "";

	if (nb <= 0)
		return ;
	srand(time(NULL));
	if (nb > 100)
		nb = 100;
	for (int i = 0; i < nb; ++i)
		instructions += tab[rand() % 18];
	std::cout << "instructions:" << std::endl << instructions << std::endl << std::endl;
	this->init_cubes();
	this->init_color();
	this->instruction = instructions.c_str();
	this->make_instructions(instructions.c_str());
}

void	Rubik::init_cubes(void)
{
	int	nb;
	int	i;
	int	j;
	int	k;
	int	id[] = {17, 7, 18, 4, 20, 6, 16, 5, 19, 9, 20, 11, 20, 20, 8, 20, 10,
				15, 3, 14, 0, 20, 2, 12, 1, 13};

	nb = 0;
	i = 0;
	while (i < this->size)
	{
		j = 0;
		while (j < this->size)
		{
			k = 0;
			while (k < this->size)
			{
				if (i == 0 || j == 0 || k == 0 ||
			i == this->size - 1 || j == this->size - 1 || k == this->size - 1)
				{
					this->cubes[nb].pos.x = j - this->center;
					this->cubes[nb].pos.y = i - this->center;
					this->cubes[nb].pos.z = k - this->center;
					this->cubes[nb].rot = this->identity_matrix();
					this->cubes[nb].id = id[nb];
					this->cubes[nb].dir = 0;
					++nb;
				}
				++k;
			}
			++j;
		}
		++i;
	}
}

const char	*Rubik::instructions_name[e_instructions::NB_INSTRUCTIONS] =
{"F", "R", "U", "B", "L", "D"};

const int	Rubik::face_coords[NB_COLOR][6] = 
{
	{1, 0, 0, 0, -1, 0}, {0, 0, 1, 0, -1, 0}, {1, 0, 0, 0, 0, -1},
	{-1, 0, 0, 0, -1, 0}, {0, 0, -1, 0, -1, 0}, {1, 0, 0, 0, 0, 1}
};

const int	Rubik::face[NB_COLOR][3] =
{{0, 0, -1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}};

const int	Rubik::face_rotate[NB_COLOR][3] =
{{0, 0, 0}, {0, -1, 0}, {1, 0, 0}, {0, 2, 0}, {0, 1, 0}, {-1, 0, 0}};

const char	*Rubik::colors_code[NB_COLOR + 1] =
{
	"\033[48;5;26m",	//BLUE
	"\033[41m",			//RED
	"\033[48;5;226m",	//YELLOW
	"\033[42m",			//GREEN
	"\033[48;5;208m",	//ORANGE
	"\033[107m",		//WHITE
	"\033[0m"			//RESET
};
