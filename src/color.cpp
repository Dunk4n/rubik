/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:14:13 by niduches          #+#    #+#             */
/*   Updated: 2020/09/16 13:05:31 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

int		Rubik::get_color(Cube cube, int face)
{
	Rubik::mat4	mat;
	uint		i;

	mat = cube.rot * rotation_matrix(static_cast<double>(Rubik::face_rotate[face][0] *
	90.f * (M_PI / 180.f)), Rubik::vec3(1.f, 0.f, 0.f));
	mat = mat * rotation_matrix(static_cast<double>(Rubik::face_rotate[face][1] *
	90.f * (M_PI / 180.f)), Rubik::vec3(0.f, 1.f, 0.f));
	mat = mat * rotation_matrix(static_cast<double>(Rubik::face_rotate[face][2] *
	90.f * (M_PI / 180.f)), Rubik::vec3(0.f, 0.f, 1.f));

	i = 0;
	while (i < NB_COLOR)
	{
		Rubik::vec3	vec(Rubik::face[i][0], Rubik::face[i][1], Rubik::face[i][2]);

		vec = vec * mat;
		if ((int)(vec.x + (vec.x < 0 ? -0.5 : 0.5)) == 0 &&
		(int)(vec.y + (vec.y < 0 ? -0.5 : 0.5)) == 0 &&
		(int)(vec.z + (vec.z < 0 ? -0.5 : 0.5)) == -1)
			return (i);
		++i;
	}
	return (0);
}

int		Rubik::get_pos_in_face(Cube cube, int face)
{
	int	u;
	int	v;

	u = (cube.pos.x * Rubik::face_coords[face][0] + cube.pos.y *
Rubik::face_coords[face][1] + cube.pos.z * Rubik::face_coords[face][2]);
	v = (cube.pos.x * Rubik::face_coords[face][3] + cube.pos.y *
Rubik::face_coords[face][4] + cube.pos.z * Rubik::face_coords[face][5]);
	return ((v + this->center) * 3 + u + this->center);
}

int		Rubik::get_face(Cube cube, int face)
{
	int	i;

	i = face + 1;
	while (i < NB_COLOR)
	{
		if ((Rubik::face[i][0] != 0 && Rubik::face[i][0] == cube.pos.x) ||
		(Rubik::face[i][1] != 0 && Rubik::face[i][1] == cube.pos.y) ||
		(Rubik::face[i][2] != 0 && Rubik::face[i][2] == cube.pos.z))
			return (i);
		++i;
	}
	return (-1);
}

void	Rubik::set_color(char *colors, Cube cube)
{
	int	face = -1;

	while ((face = get_face(cube, face)) != -1)
		colors[face * 9 + get_pos_in_face(cube, face)] = get_color(cube, face);
}

void	Rubik::init_color(void)
{
	uint	i;

	i = 0;
	while (i < this->nb_cube)
	{
		this->set_color(this->colors, this->cubes[i]);
		++i;
	}
}
