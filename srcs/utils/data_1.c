/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:34:24 by kibotrel          #+#    #+#             */
/*   Updated: 2020/03/06 10:46:39 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		fps_counter(t_env *env)
{
	int32_t			index;
	uint32_t		ticks;
	static uint32_t	i = 0;

	env->tick.frame.new = SDL_GetTicks();
	env->frame[i] = env->tick.frame.new - env->tick.frame.old;
	i = (i + 1) % NB_FRAMES;
	index = -1;
	ticks = 0;
	env->tick.frame.old = env->tick.frame.new;
	env->tick.fps.new = env->tick.frame.new;
	if (env->tick.fps.new > env->tick.fps.old + 160)
	{
		while (++index < NB_FRAMES)
			if (env->frame[index])
				ticks += env->frame[index];
		env->data.fps = 1000 / (ticks / NB_FRAMES);
		env->tick.fps.old = env->tick.fps.new;
	}
}

void		side_infos(t_game *var)
{
	var->nearz = 0.0001;
	var->farz = 5;
	var->nearside = 0.00001;
	var->farside = 20;
}

t_item		item(uint32_t sector, uint32_t min, uint32_t max)
{
	t_item			item;

	item.sector = sector;
	item.min = min;
	item.max = max;
	return (item);
}

t_height	lim(int y1, int y2)
{
	t_height		h;

	h.top = y1;
	h.bottom = y2;
	return (h);
}

t_palette	flat(int top, int middle, int bottom)
{
	t_palette		c;

	c.top = top;
	c.middle = middle;
	c.bottom = bottom;
	return (c);
}
