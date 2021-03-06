/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:11:44 by kibotrel          #+#    #+#             */
/*   Updated: 2020/03/15 22:06:01 by vivi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean.h"

void	game_keyboard(t_env *env)
{
	env->tick.back.new = SDL_GetTicks();
	if (env->input[SDL_SCANCODE_BACKSPACE]
		&& env->tick.back.new > env->tick.back.old + 250)
	{
		env->setup = 0;
		env->win = MENU;
		SDL_ShowCursor(SDL_ENABLE);
		env->tick.back.old = env->tick.back.new;
		pthread_join(env->sound, NULL);
		sf_seek(env->audio.stream[0], 0, SEEK_SET);
		sf_seek(env->audio.stream[1], 0, SEEK_SET);
		return ;
	}
	if (env->input[SDL_SCANCODE_SPACE])
		jump(env, &env->cam);
	env->setup ? cam_height(env, env->input[SDL_SCANCODE_LSHIFT]) : 0;
	if (env->input[SDL_SCANCODE_GRAVE])
		toggle_infos(env);
	if (env->input[SDL_SCANCODE_F] && !env->tuto && env->setting.fly_mode)
		fly(env);
	if (env->input[SDL_SCANCODE_R])
		reload(env);
	if (env->input[SDL_SCANCODE_F1])
		toggle_hud(env);
}
