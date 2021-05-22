/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:01:58 by niduches          #+#    #+#             */
/*   Updated: 2020/09/16 12:28:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

Rubik::mat4	Rubik::identity_matrix(void) const
{
	Rubik::mat4	mat;

	for (uint i = 0; i < 4; ++i)
	{
		for (uint j = 0; j < 4; ++j)
		{
			if (i == j)
				mat.value[i][j] = 1;
			else
				mat.value[i][j] = 0;
		}
	}
	return (mat);
}

Rubik::vec3	Rubik::normalize_vector(Rubik::vec3 vec) const
{
	float	length;

	length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	if (length == 0)
		return (vec);
	if (length < 0)
		length = -length;
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return (vec);
}

//Rubik::mat4	Rubik::rotation_matrix(float angl, Rubik::vec3 vec) const
//{
//	Rubik::mat4	mat;
//	Rubik::vec2	rot;
//	Rubik::vec3	tmp;
//
//	rot.x = cos(angl);
//	rot.y = sin(angl);
//	vec = Rubik::normalize_vector(vec);
//	tmp = (1.f - rot.x) * vec;
//
//	mat.value[0][0] = rot.x + tmp.x * vec.x;
//	mat.value[0][1] = tmp.x * vec.y + rot.y * vec.z;
//	mat.value[0][2] = tmp.x * vec.z - rot.y * vec.y;
//
//	mat.value[1][0] = tmp.y * vec.x - rot.y * vec.z;
//	mat.value[1][1] = rot.x + tmp.y * vec.y;
//	mat.value[1][2] = tmp.y * vec.z + rot.y * vec.x;
//
//	mat.value[2][0] = tmp.z * vec.x + rot.y * vec.y;
//	mat.value[2][1] = tmp.z * vec.y - rot.y * vec.x;
//	mat.value[2][2] = rot.x + tmp.z * vec.z;
//	return (mat);
//}

Rubik::mat4 Rubik::rotation_matrix(float angle, Rubik::vec3 v) const
{
    float const c = cos(angle);
    float const s = sin(angle);
    Rubik::vec3 axis(Rubik::normalize_vector(v));
    Rubik::vec3 temp(axis * (float(1) - c));

    Rubik::mat4 Rotate = Rubik::identity_matrix();
    Rotate.value[0][0] = c + temp.x * axis.x;
    Rotate.value[0][1] = temp.x * axis.y + s * axis.z;
    Rotate.value[0][2] = temp.x * axis.z - s * axis.y;

    Rotate.value[1][0] = temp.y * axis.x - s * axis.z;
    Rotate.value[1][1] = c + temp.y * axis.y;
    Rotate.value[1][2] = temp.y * axis.z + s * axis.x;

    Rotate.value[2][0] = temp.z * axis.x + s * axis.y;
    Rotate.value[2][1] = temp.z * axis.y - s * axis.x;
    Rotate.value[2][2] = c + temp.z * axis.z;
    return (Rotate);
}
