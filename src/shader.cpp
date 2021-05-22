/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:59:03 by niduches          #+#    #+#             */
/*   Updated: 2020/11/13 15:24:25 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include "shader.hpp"

static  void    CheckShaderError(GLuint shader, GLuint flag,
bool isProgram, const std::string& errorMessage);
static  GLuint  CreateShader(const std::string &fileName, GLenum shaderType);

const char	*vertex_shader =
"#version 120\n\
\n\
attribute vec3 position;\n\
attribute vec2 texCoord;\n\
attribute vec3 normal;\n\
\n\
varying vec2 texCoord0;\n\
varying vec3 normal0;\n\
\n\
uniform mat4 transform;\n\
\n\
void main()\n\
{\n\
    gl_Position = transform * vec4(position, 1.0);\n\
    texCoord0 = texCoord;\n\
	normal0 = normal;\n\
}\n";

const char	*fragment_shader =
"#version 120\n\
\n\
varying vec2 texCoord0;\n\
varying vec3 normal0;\n\
\n\
void main()\n\
{\n\
	gl_FragColor = vec4(0, 0, 0, 1);\n\
	if (normal0 == vec3(0, 0, 1))\n\
		gl_FragColor = vec4(0, 0, 1, 1);\n\
	if (normal0 == vec3(0, 0, -1))\n\
		gl_FragColor = vec4(0, 1, 0, 1);\n\
	if (normal0 == vec3(-1, 0, 0))\n\
		gl_FragColor = vec4(1, 0.5, 0, 1);\n\
	if (normal0 == vec3(1, 0, 0))\n\
		gl_FragColor = vec4(1, 0, 0, 1);\n\
	if (normal0 == vec3(0, 1, 0))\n\
		gl_FragColor = vec4(1, 1, 0, 1);\n\
	if (normal0 == vec3(0, -1, 0))\n\
		gl_FragColor = vec4(1, 1, 1, 1);\n\
}\n";

Shader::Shader(void)
{
    unsigned int i = 0;

    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(vertex_shader, GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(fragment_shader, GL_FRAGMENT_SHADER);

    while (i < NUM_SHADERS)
        glAttachShader(m_program, m_shaders[i++]);

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true,
"Error: Program linking faild: ");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true,
"Error: Program is invalid: ");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
    unsigned int i = 0;

    while (i < NUM_SHADERS) {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i++]);
    }
    glDeleteProgram(m_program);
}

void    Shader::bind()
{
    glUseProgram(m_program);
}

void    Shader::update(const Transform &transform, const Camera &camera)
{
    glm::mat4 model = camera.getViewProjection() * transform.getModel();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &(model[0][0]));
}

static  GLuint  CreateShader(const std::string &text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "Error: shader creation failed!" << std::endl;
    const GLchar *shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false,
"Error: Program linking faild: ");

    return (shader);
}

static  void    CheckShaderError(GLuint shader, GLuint flag,
bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
