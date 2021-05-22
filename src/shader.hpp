/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:59:16 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 22:52:16 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "transform.hpp"
#include "camera.hpp"

class Shader
{
    public:
    Shader(void);
    void bind();
    void update(const Transform &transform, const Camera &camera);
    ~Shader();

    private:
    static const unsigned int NUM_SHADERS = 2;

    enum
    {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_SHADERS];
};

#endif
