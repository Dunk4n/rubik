/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:57:49 by niduches          #+#    #+#             */
/*   Updated: 2020/11/12 14:07:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.hpp"

void Camera::processMouseMovement(float xOffset, float yOffset,
bool blockPitch)
{
    m_yaw += xOffset * m_mouseSenstivity;
    m_pitch += yOffset * m_mouseSenstivity;

    if (blockPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch > -89.0f)
            m_pitch = -89.0f;
    }
    update();
}

void Camera::update()
{
    glm::vec3 front;

    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_forward = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0, 1.0, 0.0)));
    m_up = glm::normalize(glm::cross(m_right, m_forward));
}
