/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 00:23:04 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 16:25:04 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

char	Rubik::get_factor(char *&instructions) const
{
	char	factor;

	factor = 1;
	if (this->is_space(*instructions) || !*instructions)
		return (1);
	if (*instructions == '2')
	{
		factor = 2;
		++instructions;
	}
	if (*instructions == '\'')
	{
		factor *= -1;
		++instructions;
	}
	if (*instructions && !this->is_space(*instructions))
		return (0);
	return (factor);
}

static int	transform_instruction[Rubik::NB_INSTRUCTIONS][Rubik::NB_INSTRUCTIONS] =
{
	{Rubik::FRONT, Rubik::RIGHT, Rubik::UP, Rubik::BACK, Rubik::LEFT, Rubik::DOWN},
	{Rubik::RIGHT, Rubik::BACK, Rubik::UP, Rubik::LEFT, Rubik::FRONT, Rubik::DOWN},
	{Rubik::UP, Rubik::RIGHT, Rubik::BACK, Rubik::DOWN, Rubik::LEFT, Rubik::FRONT},
	{Rubik::BACK, Rubik::LEFT, Rubik::UP, Rubik::FRONT, Rubik::RIGHT, Rubik::DOWN},
	{Rubik::LEFT, Rubik::FRONT, Rubik::UP, Rubik::RIGHT, Rubik::BACK, Rubik::DOWN},
	{Rubik::DOWN, Rubik::RIGHT, Rubik::FRONT, Rubik::UP, Rubik::LEFT, Rubik::BACK},
};

int		Rubik::get_instruction(char *&instructions, int face) const
{
	uint	i;

	if (!instructions)
		return (-1);
	i = 0;
	while (i < NB_INSTRUCTIONS)
	{
		if (!this->strncmp(instructions, this->instructions_name[i],
		this->strlen(this->instructions_name[i])))
		{
			instructions += this->strlen(this->instructions_name[i]);;
			return (transform_instruction[face][i]);
		}
		++i;
	}
	return (-1);
}

void	Rubik::display_instruction(int instr, int factor)
{
	std::string new_instruction = "";
	std::string direction[6] = {"front", "right", "up", "back", "left", "down"};

	if (!this->sol)
		return ;
	new_instruction = this->instructions_name[instr % 6];
	if (factor == 2)
		new_instruction += '2';
	else if (factor < 0)
		new_instruction += '\'';
	if (this->human_readable == true)
	{
		std::cout << new_instruction << ':' << std::endl;
		std::cout << "Rotate the " << direction[instr % 6] << " face ";
		if (factor == 2)
			std::cout << "two times ";
		else
			std::cout << "one time ";
		if (factor < 0)
			std::cout << "cunter";
		std::cout << "clockwise." << std::endl;
		std::cout << std::endl;
	}
	this->solution += new_instruction;
	this->solution += ' ';
}

void	Rubik::make_instruction(char *&instructions, int face)
{
	int		instr;
	char	factor;

	this->pass_spaces(instructions);
	if (!*instructions)
		return ;
	instr = this->get_instruction(instructions, face);
	if (instr == -1)
	{
		this->destroy();
		throw std::exception();
		return ;
	}
	factor = this->get_factor(instructions);
	if (!factor)
	{
		this->destroy();
		throw std::exception();
		return ;
	}
	this->display_instruction(instr, factor);
	switch (instr)
	{
		case FRONT:
			this->rotate_front(factor);
			break;
		case RIGHT:
			this->rotate_right(factor);
			break;
		case UP:
			this->rotate_up(factor);
			break;
		case BACK:
			this->rotate_back(factor);
			break;
		case LEFT:
			this->rotate_left(factor);
			break;
		case DOWN:
			this->rotate_down(factor);
			break;
		default:
			break;
	}
	this->pass_spaces(instructions);
}

bool	Rubik::is_another_instruction(char *instructions) const
{
	return (instructions && *instructions);
}

void	Rubik::make_instructions(char *instructions, int face)
{
	while (this->is_another_instruction(instructions))
		this->make_instruction(instructions, face);
}

void	Rubik::make_instructions(const char *instructions, int face)
{
	char	*tmp = (char*)(instructions);

	while (this->is_another_instruction(tmp))
		this->make_instruction(tmp, face);
}

void	Rubik::make_instructions(std::string instructions, int face)
{
	char	*tmp = (char*)(instructions.c_str());

	while (this->is_another_instruction(tmp))
		this->make_instruction(tmp, face);
}

bool	Rubik::is_space(char c) const
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	Rubik::pass_spaces(char *&instructions) const
{
	while (is_space(*instructions))
		++(instructions);
}
