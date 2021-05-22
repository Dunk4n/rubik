/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:01 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 23:01:49 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtx/transform.hpp>

class Camera
{
    public:
    Camera(const glm::vec3 &pos, float fov, float aspect, float zNear, float zFar)
    {
        m_perspective = glm::perspective(fov, aspect, zNear, zFar);
        m_position = pos;
        m_right = glm::vec3(1, 0, 0);
        m_up = glm::vec3(0, 1, 0);
        m_forward = glm::vec3(0, 0, 1);
        m_yaw = -90;
        m_pitch = 0;
        m_mouseSenstivity = 0.25;
        update();
    }
    inline glm::mat4 getViewProjection() const
    {
        return (m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up));
    }
    void processMouseMovement(float xOffset, float yOffset, bool blockPitch = true);
    inline void go_forward(float fact) { m_position += m_forward * fact; }
    inline void go_up(float fact) { m_position += m_up * fact; }
    inline void go_right(float fact) { m_position += m_right * fact; }

    private:
    void update();
    glm::mat4   m_perspective;
    glm::vec3   m_position;
    glm::vec3   m_right;
    glm::vec3   m_up;
    glm::vec3   m_forward;
    float       m_yaw;
    float       m_pitch;
    float       m_mouseSenstivity;
};

#endif
