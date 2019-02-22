/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:55:20 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 20:19:25 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_cam(t_param *p, double x, double z)
{
	p->ray.cam.x = x;
	p->ray.cam.z = z;
}

static void		set_camxz(t_param *p, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_KP_1)
		set_cam(p, -4999, -4999);
	else if (event->key.keysym.sym == SDLK_KP_2)
		set_cam(p, 0, -4999);
	else if (event->key.keysym.sym == SDLK_KP_3)
		set_cam(p, 4999, -4999);
	else if (event->key.keysym.sym == SDLK_KP_6)
		set_cam(p, 4999, 0);
	else if (event->key.keysym.sym == SDLK_KP_9)
		set_cam(p, 4999, 4999);
	else if (event->key.keysym.sym == SDLK_KP_8)
		set_cam(p, 0, 4999);
	else if (event->key.keysym.sym == SDLK_KP_7)
		set_cam(p, -4999, 4999);
	else if (event->key.keysym.sym == SDLK_KP_4)
		set_cam(p, -4999, 0);
	else if (event->key.keysym.sym == SDLK_KP_5)
	{
		p->ray.scene = vec_new(0, 0, 1);
		p->ray.cam = vec_new(0, 0, 0);
	}
}

static void		catch_key(t_param *p, t_sdl *sdl, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN)
	{
		p->ray.scene = vec_new(0, 0, 0);
		if (event->key.keysym.sym == SDLK_KP_MINUS)
			p->ray.cam.y += p->ray.cam.y == -680 ? 0 : -680;
		else if (event->key.keysym.sym == SDLK_KP_PLUS)
			p->ray.cam.y += p->ray.cam.y == 680 ? 0 : 680;
		else
			set_camxz(p, event);
	}
	else if (event->type == SDL_KEYUP)
		if (event->key.keysym.sym == SDLK_KP_PLUS ||
				event->key.keysym.sym == SDLK_KP_MINUS ||
				(event->key.keysym.sym >= SDLK_KP_1 &&
				event->key.keysym.sym <= SDLK_KP_9))
		{
			cam_init(p);
			go(sdl, p);
			sdl_print(sdl);
		}
}

int				catch_event(t_param *p, t_sdl *sdl, SDL_Event *event)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			return (0);
		else if (event->type == SDL_WINDOWEVENT)
		{
			if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_DestroyRenderer(sdl->ren);
				sdl->ren = SDL_CreateRenderer(sdl->win, -1,
						SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				sdl_print(sdl);
			}
		}
		else
			catch_key(p, sdl, event);
	}
	return (1);
}
