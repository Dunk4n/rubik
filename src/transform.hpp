/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:59:22 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 22:54:37 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtx/transform.hpp>

class Transform
{
    public:
    Transform(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot =
glm::vec3(), const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
m_tran(1.f), m_pos(pos), m_rot(rot), m_scale(scale)
	{
	}

    inline glm::mat4 getModel() const { return (m_tran); }
	void	operator=(Transform const &copy)
	{
		m_tran = copy.m_tran;
		m_pos = copy.m_pos;
		m_rot = copy.m_rot;
		m_scale = copy.m_scale;
	}

    inline glm::mat4 &getTran() { return m_tran; }
    inline glm::vec3 &getPos()
	{
		m_pos = glm::vec3(m_tran[3][0], m_tran[3][1], m_tran[3][2]);
		return (m_pos);
	}
    inline glm::vec3 &getRot() { return m_rot; }
    inline glm::vec3 &getScale() { return m_scale; }

    inline void setTran(const glm::mat4 &tran) { m_tran = tran; }
    ~Transform() {}

    private:
    glm::mat4 m_tran;
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;
};

#endif
