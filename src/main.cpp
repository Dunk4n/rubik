/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:55:45 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 13:13:45 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "Rubik.hpp"

int		get_flag(int ac, char **av, Rubik *ru)
{
	while (ac)
	{
		if (!strcmp("-d", av[0]))
			ru->set_display(!ru->get_display());
		else if (!strcmp("-s", av[0]))
			ru->chage_resolve(!ru->get_resolve());
		else if (!strncmp("-g", av[0], 2))
			ru->set_generateur(atoi(av[0] + 2));
		else if (!strcmp("-w", av[0]))
			ru->set_graphique(!ru->get_graphique());
		else if (!strcmp("-h", av[0]))
			ru->set_human_readable(!ru->get_human_readable());
		else
			return (0);
		ac--;
		av++;
	}
	return (1);
}

void	rubik_program_usage(void)
{
	std::cout << "./rubik \"F R2 U' ...\" OPTIONS" << std::endl << std::endl <<
	"OPTIONS" << std::endl <<
	"-d\t\tdisplay rubik" << std::endl <<
	"-s\t\tchange algorithme" << std::endl <<
	"-g[0-100]\tgenerate instructions" << std::endl <<
	"-w\t\tdisplay 3d rubik" << std::endl <<
	std::endl <<
	"WINDOW COMMAND" << std::endl <<
	"\t'r' to start to resolve the rubik" << std::endl <<
	"\t'w' to go forward and      's' to go backward" << std::endl <<
	"\t'd' to go to the right and 'a' to go to the left" << std::endl <<
	"\t'e' to go up and           'q' to go down" << std::endl;
	return ;
}

int		check_define_range(void)
{
	if (NB != 3)
	{
		std::cerr << "The macro NB is not in the authorized value in the file \"graphique.hpp\", it must be the constant value 3" << std::endl << std::endl;
		return (1);
	}
	if (HEIGHT != 400)
	{
		std::cerr << "The macro HEIGHT is not in the authorized value in the file \"graphique.hpp\", it must be the constant value 400" << std::endl << std::endl;
		return (1);
	}
	if (WIDTH != 600)
	{
		std::cerr << "The macro WIDTH is not in the authorized value in the file \"graphique.hpp\", it must be the constant value 600" << std::endl << std::endl;
		return (1);
	}
	if (ROTATION_TIME < 10000 || ROTATION_TIME > 5000000)
	{
		std::cerr << "The macro ROTATION_TIME is not in the authorized range in the file \"graphique.hpp\", it must be (ROTATION_TIME >= 10000) and (ROTATION_TIME <= 5000000)" << std::endl << std::endl;
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (check_define_range() == 1)
	{
		rubik_program_usage();
		return (0);
	}
	if (ac <= 1)
	{
		rubik_program_usage();
		return (0);
	}
	try
	{
		Rubik	ru(av[1]);
		if (!get_flag(ac - 2, av + 2, &ru))
		{
			std::cerr << "ERROR arguments" << std::endl << std::endl;
			rubik_program_usage();
			return (0);
		}
		ru.resolve();
		ru.display_solution();
	}
	catch (std::exception &e)
	{
		std::cerr << "ERROR parsing" << std::endl;
		return (0);
	}
	catch (...)
	{
		std::cerr << "ERROR" << std::endl;
		return (0);
	}
	return (0);
}
