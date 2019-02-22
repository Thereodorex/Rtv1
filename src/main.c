/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:41:55 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 17:03:32 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void			cam_init(t_param *param)
{
	param->ray.ray = vec_frompoint(param->ray.scene, param->ray.cam);
	param->ray.ray.y = 0;
	param->ray.cos_a = vec_scal(vec_new(0, 0, 1), param->ray.ray) /
												vec_len(param->ray.ray);
	param->ray.ray2 = vec_frompoint(vec_new(0, 0, 0), param->ray.cam);
	param->ray.cos_b = vec_scal(param->ray.ray2, param->ray.ray) /
						vec_len(param->ray.ray) / vec_len(param->ray.ray2);
	param->ray.ray = vec_new(0, 1, 0);
	param->ray.ray2 = vec_cross(param->ray.ray, param->ray.ray2);
	if (vec_len(param->ray.ray2) == 0)
		param->ray.ray2 = vec_new(0, 1, 0);
}

static void		param_del(t_param *p)
{
	free(p->plane);
	free(p->l);
	free(p->sp);
	free(p->con);
	free(p->cyl);
}

static void		param_init(t_param *param)
{
	param->ray.cam = vec_new(0, 0, -1);
	param->ray.scene = vec_new(0, 0, 1);
	param->plane = NULL;
	param->l = NULL;
	param->sp = NULL;
	param->con = NULL;
	param->cyl = NULL;
	param->l_count = 0;
	param->sp_count = 0;
	param->plane_count = 0;
	param->con_count = 0;
	param->cyl_count = 0;
}

static int		catch_event(t_sdl *sdl, SDL_Event *event)
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
	}
	return (1);
}

int				main(int argc, char **argv)
{
	t_sdl		*sdl;
	SDL_Event	event;
	int			running;
	t_param		param;

	running = 1;
	if (argc != 2)
		return (0);
	param_init(&param);
	read_file(&param, argv[1]);
	cam_init(&param);
	sdl = sdl_init(700, 200, WIDTH, HEIGHT);
	render(sdl, &param, acos(param.ray.cos_a), acos(param.ray.cos_b));
	sdl_print(sdl);
	while (running)
		running = catch_event(sdl, &event);
	sdl = sdl_destroy(sdl);
	param_del(&param);
	return (0);
}
