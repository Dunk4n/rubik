/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:57:23 by niduches          #+#    #+#             */
/*   Updated: 2021/05/21 12:36:29 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <math.h>
#include <string>
#include <exception>
#include <GL/glew.h>
#include "display.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "obj.hpp"
#include "Rubik.hpp"
#include "graphique.hpp"

void    put_cube(Transform *tab, int nb_cube)
{
    float centre = (NB - 1) * 0.5;
    int nb = 0;
    int i = 0;
    int j;
    int k;

    while (i < nb_cube)
        tab[i++] = Transform();
    i = 0;
    while (i < NB)
	{
        j = 0;
        while (j < NB)
		{
            k = 0;
            while (k < NB)
			{
                if (i == 0 || j == 0 || k == 0 || i == NB - 1 || j == NB - 1 || k == NB - 1)
				{
					tab[nb].getTran() *= glm::translate(glm::vec3((j - centre) *
					1.02, (i - centre) * 1.02, (k - centre) * 1.02));
                    nb++;
                }
                k++;
            }
            j++;
        }
        i++;
    }
}

uint64_t	get_time(void)
{
	struct timeval	tp;
	uint64_t		time;

	if (gettimeofday(&tp, NULL) == -1)
		return (0);
	time = tp.tv_sec * 1000000 + tp.tv_usec;
	return (time);
}

void	Rubik::set_rubik(Transform *tab, int nb_cube)
{
	char		*instr = (char*)this->instruction.c_str();
	s_anim		anim;

	anim.start = false;
	while (*instr)
	{
		make_new_instruction(instr, &anim, tab, nb_cube);
		make_rotation(&anim, 1.f);
	}
}

void	Rubik::make_window(void)
{
	int i = 0;
	int nb_cube = NB * NB * NB;

	if (NB < 1)
		return ;
	if (NB > 2)
		nb_cube -= (NB - 2) * (NB - 2) * (NB - 2);

	try
	{
	Display		win(WIDTH, HEIGHT, "RUBIK");
	Camera		camera(glm::vec3(0, 0, 8), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Obj			cube = Obj();
	Transform   tab[nb_cube];
	s_anim		anim;
	char		*instr = (char*)this->solution.c_str();
	uint64_t	last = 0;

	anim.start = false;
	put_cube(tab, nb_cube);

	SDL_ShowCursor(SDL_DISABLE);
	set_rubik(tab, nb_cube);
	make_new_instruction(instr, &anim, tab, nb_cube);
	while (!win.isClosed())
	{
		uint64_t	act_time = get_time();

		if (act_time >= last)
		{
			win.clear(0.9f, 0.9f, 0.9f, 1.0f);
			last = act_time + 16666;
			if (anim.start)
			{
				if (anim.instr >= 0)
				{
					make_rotation(&anim, (double)(act_time  - (anim.time_end -
					(ROTATION_TIME * (anim.factor == 2 ? 2 : 1)))) /
					(double)(ROTATION_TIME * (anim.factor == 2 ? 2 : 1)));
					if (act_time >= anim.time_end)
						make_new_instruction(instr, &anim, tab, nb_cube);
				}
			}
			i = 0;
			while (i < nb_cube)
			{
				cube.setTransform(tab[i]);
				cube.draw(camera);
				++i;
			}
			win.update(&camera, &anim);
		}
	}
	}
	catch (std::exception &e)
	{
		(void)e;
		std::cout << "WINDOW ERROR" << std::endl;
	}
}
