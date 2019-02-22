/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:57:39 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:33:13 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		*sdl_destroy(t_sdl *sdl)
{
	if (!sdl)
		return (NULL);
	if (sdl->surf)
		SDL_FreeSurface(sdl->surf);
	if (sdl->img.img)
		free(sdl->img.img);
	if (sdl->tex)
		SDL_DestroyTexture(sdl->tex);
	if (sdl->ren)
		SDL_DestroyRenderer(sdl->ren);
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	free(sdl);
	SDL_Quit();
	return (NULL);
}

t_sdl		*sdl_init(int x, int y, int w, int h)
{
	t_sdl	*sdl;

	if ((sdl = (t_sdl *)malloc(sizeof(t_sdl))) == NULL)
		return (NULL);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (sdl_destroy(sdl));
	if (!(sdl->win = SDL_CreateWindow("RTv1", x, y, w, h, SDL_WINDOW_SHOWN |
					SDL_WINDOW_RESIZABLE)))
		return (sdl_destroy(sdl));
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	if (sdl->ren == NULL)
		return (sdl_destroy(sdl));
	sdl->tex = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
									SDL_TEXTUREACCESS_TARGET, w, h);
	if (sdl->tex == NULL)
		return (sdl_destroy(sdl));
	sdl->img.img = (unsigned int *)malloc(sizeof(unsigned int) * (w * h));
	if (sdl->img.img == NULL)
		return (sdl_destroy(sdl));
	sdl->img.h = h;
	sdl->img.w = w;
	if (!(sdl->surf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)))
		return (sdl_destroy(sdl));
	return (sdl);
}

void		sdl_print(t_sdl *sdl)
{
	if (sdl->tex)
		SDL_DestroyTexture(sdl->tex);
	sdl->tex = SDL_CreateTextureFromSurface(sdl->ren, sdl->surf);
	if (!sdl->tex)
		STOP;
	if (SDL_RenderCopy(sdl->ren, sdl->tex, NULL, NULL))
		STOP;
	SDL_RenderPresent(sdl->ren);
}

void		sdl_putpix(t_sdl *sdl, int x, int y, unsigned int color)
{
	unsigned int	*ptr;

	ptr = (unsigned int *)sdl->surf->pixels;
	if (x < sdl->surf->w && y < sdl->surf->h)
		*(ptr + y * sdl->surf->w + x) = color;
}
