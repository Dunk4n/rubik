/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphique_instruction.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:40:02 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 17:17:25 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.hpp"
#include "Rubik.hpp"
#include "graphique.hpp"

bool	cube_in_face(Transform *cube, const int *face)
{
	if (face[0] == 1 && cube->getPos().x >= 1)
		return (true);
	if (face[0] == -1 && cube->getPos().x <= -1)
		return (true);
	if (face[1] == 1 && cube->getPos().y >= 1)
		return (true);
	if (face[1] == -1 && cube->getPos().y <= -1)
		return (true);
	if (face[2] == 1 && cube->getPos().z >= 1)
		return (true);
	if (face[2] == -1 && cube->getPos().z <= -1)
		return (true);
	return (false);
}

int		Rubik::get_instruction_graphique(char *&instructions) const
{
	uint	i;
	const char	*name[e_instructions::NB_INSTRUCTIONS] =
{"B", "R", "U", "F", "L", "D"};

	if (!instructions)
		return (-1);
	i = 0;
	while (i < NB_INSTRUCTIONS)
	{
		if (!this->strncmp(instructions, name[i], this->strlen(name[i])))
		{
			instructions += this->strlen(name[i]);;
			return (i);
		}
		++i;
	}
	return (-1);
}


void	Rubik::make_new_instruction(char *&instr, s_anim *anim, Transform *tab, int nb_cube)
{
	int	nb = 0;

	Rubik::pass_spaces(instr);
	anim->instr = Rubik::get_instruction_graphique(instr);
	anim->factor = Rubik::get_factor(instr);
	Rubik::pass_spaces(instr);
	if (anim->instr == -1)
		return ;
	for (int i = 0; i < nb_cube; ++i)
	{
		if (cube_in_face(tab + i, Rubik::face[anim->instr]))
		{
			anim->act[nb] = tab + i;
			anim->save[nb++] = tab[i];
		}
	}
	if (nb != 9)
	{
		anim->instr = -1;
		return ;
	}
	anim->time_end = get_time() + ROTATION_TIME * (anim->factor == 2 ? 2 : 1);
}

void	make_rotation(s_anim *anim, double ratio)
{
	if (ratio > 1.0)
		ratio = 1.0;

	float		angl = ((90.f * (float)anim->factor * ratio) * M_PI / 180.f) *
	((anim->instr == Rubik::BACK || anim->instr == Rubik::UP ||
	anim->instr == Rubik::RIGHT) ? -1 : 1);

	for (int i = 0; i < 9; ++i)
	{
		if (anim->instr == Rubik::FRONT || anim->instr == Rubik::BACK)
		{
			anim->act[i]->getTran() =
			glm::rotate(angl, glm::vec3(0.0, 0.0, 1.0)) * anim->save[i].getModel();
		}
		if (anim->instr == Rubik::UP || anim->instr == Rubik::DOWN)
		{
			anim->act[i]->getTran() =
			glm::rotate(angl, glm::vec3(0.0, 1.0, 0.0)) * anim->save[i].getModel();
		}
		if (anim->instr == Rubik::RIGHT || anim->instr == Rubik::LEFT)
		{
			anim->act[i]->getTran() =
			glm::rotate(angl, glm::vec3(1.0, 0.0, 0.0)) * anim->save[i].getModel();
		}
	}
}
