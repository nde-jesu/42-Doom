/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:38:11 by kibotrel          #+#    #+#             */
/*   Updated: 2020/03/15 22:20:25 by vivi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "clean.h"
#include "libft.h"
#include "utils.h"
#include "parse.h"
#include "settings.h"

static void	multithreaded_engine(t_env *env)
{
	int	i;

	i = -1;
	env->data.sky = 0;
	while (++i < NB_THREADS)
		if (pthread_create(&env->sdl.thread[i], NULL, (void*)graphics, env))
			clean(env, E_THREAD);
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(env->sdl.thread[i], NULL);
	if (env->crash)
		clean(env, E_MALLOC);
	if (env->data.sky)
		draw_skybox(env);
}

static void	params_reset(t_env *env)
{
	env->data.money = 0;
	env->data.life = 100;
	env->data.ammos = 5;
	env->data.fall_height = INT_MIN;
	env->data.height_end = 0;
	env->data.height_start = 0;
	env->data.hud.coin.frame = 0;
	env->data.hud.shotgun.frame = 0;
	env->data.shot = 0;
	env->audio.fire = 0;
	env->data.magazines = (env->setting.mode == HARD ? 10 : 20);
	env->setup = 1;
	env->track_fall = 0;
	env->cam.fly = -1;
	env->cam.cos = cos(env->cam.angle);
	env->cam.sin = sin(env->cam.angle);
	env->cam.pos.z = env->sector[env->cam.sector].floor + CAM_H;
}

void		game(t_env *env)
{
	if (!env->setup)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetWindowTitle(env->sdl.win, TITLE_GAME);
		params_reset(env);
		if (pthread_create(&env->sound, NULL, (void*)audio, env))
			clean(env, E_THREAD);
	}
	multithreaded_engine(env);
	hud(env);
	sector_triger(env);
	fall_damage(env);
	if (env->tuto == 1)
		tuto(env);
}
