/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:25 by niduches          #+#    #+#             */
/*   Updated: 2020/11/11 19:58:27 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "mesh.hpp"

Mesh::Mesh(void)
{
    InitMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

float	cube_pos[108] =
{
	0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	-0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	-0.5, 0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	-0.5, 0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	-0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,
	-0.5, 0.5, 0.5,
	-0.5, -0.5, 0.5,
	0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, -0.5,
	0.5, 0.5, 0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5,
	0.5, 0.5, 0.5,
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	-0.5, -0.5, 0.5,
	0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, -0.5, -0.5,
};

float	cube_tex[] =
{
	0.5, 0.5,
	0.5, -0.5,
	-0.5, -0.5,
	0.5, 0.5,
	-0.5, -0.5,
	-0.5, 0.5,
	-0.5, -0.5,
	-0.5, 0.5,
	-0.5, 0.5,
	-0.5, -0.5,
	-0.5, 0.5,
	-0.5, -0.5,
	0.5, -0.5,
	0.5, 0.5,
	-0.5, -0.5,
	0.5, 0.5,
	-0.5, 0.5,
	-0.5, -0.5,
	0.5, -0.5,
	0.5, 0.5,
	0.5, -0.5,
	0.5, 0.5,
	0.5, 0.5,
	0.5, -0.5,
	0.5, 0.5,
	-0.5, 0.5,
	0.5, 0.5,
	-0.5, 0.5,
	-0.5, 0.5,
	0.5, 0.5,
	0.5, -0.5,
	0.5, -0.5,
	-0.5, -0.5,
	0.5, -0.5,
	-0.5, -0.5,
	-0.5, -0.5,
};

float	cube_norm[] =
{
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
};

unsigned int	cube_indices[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
};

void Mesh::InitMesh()
{
    m_drawCount = 36;

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, 432, cube_pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, 288, cube_tex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, 432, cube_norm, GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 144, cube_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
