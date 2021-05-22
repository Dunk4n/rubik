/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:39 by niduches          #+#    #+#             */
/*   Updated: 2020/11/11 19:58:44 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.hpp"

void    Obj::draw(Camera &camera)
{
    m_shader.update(m_transform, camera);
    m_mesh.draw();
}