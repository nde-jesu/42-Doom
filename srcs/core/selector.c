/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kibotrel <kibotrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:21:13 by kibotrel          #+#    #+#             */
/*   Updated: 2020/03/06 11:24:14 by reda-con         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "clean.h"

void	selector(t_env *env, int ac, char **av)
{
	env->tick.frame.old = env->tick.frame.new;
	if (env->win == MENU)
		menu(env);
	else if (env->win == GAME)
	{
		SDL_WarpMouseInWindow(env->sdl.win, env->w / 2, env->h / 2);
		game(env);
	}
	else if (env->win == EDITOR)
		editor(env, ac, av);
	else if (env->win == SETTINGS)
		settings(env);
	else if (env->win == QUIT)
		clean(env, NOTHING);
}
