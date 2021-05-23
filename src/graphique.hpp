/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphique.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:41:05 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 13:14:53 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIQUE_HPP
# define GRAPHIQUE_HPP

# include <sys/time.h>
# include "transform.hpp"

# define WIDTH 600
# define HEIGHT 400
# define NB 3

// 1000000 == 5s
// 500000  == 0.5s
// 10000   == 0.01s
# define ROTATION_TIME (500000) // 0.5s

struct	s_anim
{
	Transform	*act[NB * NB];
	Transform	save[NB * NB];
	uint64_t	time_end;
	int			instr;
	int			factor;
	bool		start;
};

uint64_t	get_time(void);
void		make_new_instruction(char *&instr, s_anim *anim);
void		make_rotation(s_anim *anim, double ratio);

#endif /* GRAPHIQUE_HPP */
