/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:08 by niduches          #+#    #+#             */
/*   Updated: 2021/05/23 16:07:12 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <exception>
#include "display.hpp"

Display::Display(int width, int height, std::string title)
{
    SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_EVENTS);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		SDL_Quit();
		throw (std::exception());
	}
    m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_glContext)
	{
		if (m_window)
    		SDL_DestroyWindow(m_window);
		SDL_Quit();
		throw (std::exception());
	}

    GLenum status = glewInit();

    if (status != GLEW_OK)
	{
        std::cerr << "Glew faild to initialize!" << std::endl;
		if (m_glContext)
			SDL_GL_DeleteContext(m_glContext);
		if (m_window)
    		SDL_DestroyWindow(m_window);
		SDL_Quit();
		throw (std::exception());
    }

    m_isClosed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Display::~Display()
{
	if (m_glContext)
		SDL_GL_DeleteContext(m_glContext);
	if (m_window)
		SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool    Display::isClosed(void)
{
    return (m_isClosed);
}

#define WIDTH 600
#define WIDTH2 300
#define HEIGHT 400
#define HEIGHT2 200

void    Display::update(Camera *camera, s_anim *anim)
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;

	memset(&e, 0, sizeof(SDL_Event));
	e.key.keysym.sym = 0;
	e.key.keysym.sym = 0;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            m_isClosed = true;
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
            m_isClosed = true;
        if (e.key.keysym.sym == SDLK_w)
            camera->go_forward(0.1);
        if (e.key.keysym.sym == SDLK_s)
            camera->go_forward(-0.1);
        if (e.key.keysym.sym == SDLK_e)
            camera->go_up(0.1);
        if (e.key.keysym.sym == SDLK_q)
            camera->go_up(-0.1);
        if (e.key.keysym.sym == SDLK_d)
            camera->go_right(0.1);
        if (e.key.keysym.sym == SDLK_a)
            camera->go_right(-0.1);
        if (e.key.keysym.sym == SDLK_r && anim->start == false)
		{
            anim->start = true;
			anim->time_end = get_time() + ROTATION_TIME * (anim->factor == 2 ? 2 : 1);
		}
        if (e.type == SDL_MOUSEMOTION &&
e.motion.x != WIDTH2 && e.motion.y != HEIGHT2) {
            camera->processMouseMovement(e.motion.xrel, -e.motion.yrel, false);
            SDL_WarpMouseInWindow(m_window, WIDTH2, HEIGHT2);
        }
    }
}
