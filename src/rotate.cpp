/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:17:45 by niduches          #+#    #+#             */
/*   Updated: 2020/11/11 12:27:32 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

void	Rubik::round_vec3(Rubik::vec3 &vec)
{
	vec.x = (int)(vec.x + (vec.x < 0 ? -0.5 : 0.5));
	vec.y = (int)(vec.y + (vec.y < 0 ? -0.5 : 0.5));
	vec.z = (int)(vec.z + (vec.z < 0 ? -0.5 : 0.5));
}

void	Rubik::rotate_front(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(0.f, 0.f, 1.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.z == -1)
		{
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.x == 1 && this->cubes[i].pos.y == 1) ||
			(this->cubes[i].pos.x == -1 && this->cubes[i].pos.y == -1)))
				this->cubes[i].dir += 1;
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.x == 1 && this->cubes[i].pos.y == -1) ||
			(this->cubes[i].pos.x == -1 && this->cubes[i].pos.y == 1)))
				this->cubes[i].dir += 2;
			if (this->cubes[i].id < 12)
				this->cubes[i].dir += (factor <= 1 ? 1 : 2);
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}

void	Rubik::rotate_right(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(-factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(1.f, 0.f, 0.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.x == 1)
		{
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.z == 1 && this->cubes[i].pos.y == 1) ||
			(this->cubes[i].pos.z == -1 && this->cubes[i].pos.y == -1)))
				this->cubes[i].dir += 1;
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.z == 1 && this->cubes[i].pos.y == -1) ||
			(this->cubes[i].pos.z == -1 && this->cubes[i].pos.y == 1)))
				this->cubes[i].dir += 2;
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}

void	Rubik::rotate_up(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(-factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(0.f, 1.f, 0.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.y == 1)
		{
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}

void	Rubik::rotate_back(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(-factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(0.f, 0.f, 1.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.z == 1)
		{
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.x == 1 && this->cubes[i].pos.y == 1) ||
			(this->cubes[i].pos.x == -1 && this->cubes[i].pos.y == -1)))
				this->cubes[i].dir += 1;
			if (this->cubes[i].id < 12)
				this->cubes[i].dir += (factor <= 1 ? 2 : 0);
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->cubes[i].dir += (factor <= 1 ? 1 : 0);
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}

void	Rubik::rotate_left(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(1.f, 0.f, 0.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.x == -1)
		{
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.z == 1 && this->cubes[i].pos.y == 1) ||
			(this->cubes[i].pos.z == -1 && this->cubes[i].pos.y == -1)))
				this->cubes[i].dir += 2;
			if (factor < 2 && this->cubes[i].id >= 12 &&
			((this->cubes[i].pos.z == 1 && this->cubes[i].pos.y == -1) ||
			(this->cubes[i].pos.z == -1 && this->cubes[i].pos.y == 1)))
				this->cubes[i].dir += 1;
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}

void	Rubik::rotate_down(char factor)
{
	Rubik::mat4	mat;
	uint		i;

	mat = rotation_matrix(static_cast<double>(factor * 90.0 * (M_PI / 180.0)),
	Rubik::vec3(0.f, 1.f, 0.f));
	i = 0;
	while (i < this->nb_cube)
	{
		if (this->cubes[i].pos.y == -1)
		{
			this->cubes[i].pos *= mat;
			round_vec3(this->cubes[i].pos);
			this->cubes[i].rot *= mat;
			this->set_color(this->colors, this->cubes[i]);
		}
		++i;
	}
}
