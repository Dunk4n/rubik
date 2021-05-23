/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:32 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 15:33:17 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <GL/glew.h>

class vertex
{
    public:
    vertex(const glm::vec3 &pos, const glm::vec2 &texCoord,
const glm::vec3 &normal = glm::vec3(0, 0, 0))
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
    }
    inline glm::vec3 *getPos() { return &pos; }
    inline glm::vec2 *getTextCoord() { return &texCoord; }
    inline glm::vec3 *getNormal() { return &normal; }

    private:

    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Mesh
{
    public:
    Mesh(void);
    void draw();
    ~Mesh();

    private:

    void InitMesh(void);

    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif
