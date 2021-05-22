/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 23:28:50 by niduches          #+#    #+#             */
/*   Updated: 2020/11/12 00:02:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rubik.hpp"

void	Rubik::display_square(char *color, int nb, int offset)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < offset; ++j)
			std::cout << ' ';
		std::cout << Rubik::colors_code[(int)color[nb * 9 + i * 3]] << "  ";
		std::cout << Rubik::colors_code[(int)color[nb * 9 + i * 3 + 1]] << "  ";
		std::cout << Rubik::colors_code[(int)color[nb * 9 + i * 3 + 2]] << "  ";
		std::cout << Rubik::colors_code[NB_COLOR] << std::endl;
	}
}

void	Rubik::display_multiple_square(char *color, int *tab, int size, int offset)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < offset; ++k)
				std::cout << ' ';
			std::cout << Rubik::colors_code[(int)color[tab[j] * 9 + i * 3]] << "  ";
			std::cout << Rubik::colors_code[(int)color[tab[j] * 9 + i * 3 + 1]] << "  ";
			std::cout << Rubik::colors_code[(int)color[tab[j] * 9 + i * 3 + 2]] << "  ";
			std::cout << Rubik::colors_code[NB_COLOR];
		}
		std::cout << std::endl;
	}
}

void	Rubik::display_color(void)
{
	int	tab[] = {ORANGE, BLUE, RED, GREEN};

	this->display_square(this->colors, YELLOW, 10);
	std::cout << std::endl;
	this->display_multiple_square(this->colors, tab, 4, 2);
	std::cout << std::endl;
	this->display_square(this->colors, WHITE, 10);
}
