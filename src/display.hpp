/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:58:15 by niduches          #+#    #+#             */
/*   Updated: 2021/05/22 22:46:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include "camera.hpp"
#include "graphique.hpp"

class Display
{
    public:
    Display(int width, int height, std::string title);
    void clear(float r, float g, float b, float a);
    void update(Camera *camera, s_anim *anim);
    bool isClosed(void);
    ~Display();

    private:
    SDL_Window      *m_window;
    SDL_GLContext   m_glContext;
    bool            m_isClosed;
};

#endif
