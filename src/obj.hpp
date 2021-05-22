/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:50 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 22:50:26 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
#define OBJ_H

#include "shader.hpp"
#include "mesh.hpp"

class Obj
{
    public:
    Obj(const glm::vec3 &pos = glm::vec3(),
const glm::vec3 &rot = glm::vec3(),
const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
m_mesh(), m_shader(),
m_transform(pos, rot, scale) { m_shader.bind(); }
    void draw(Camera &camera);
    inline Transform *getTransform() { return &m_transform; }
	void	setTransform(Transform &transform) { m_transform = transform; }

    private:
    Mesh        m_mesh;
    Shader      m_shader;
    Transform   m_transform;
};

#endif
