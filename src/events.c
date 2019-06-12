/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/12 05:57:53 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	if (m->is_pressed)
	{
		put_rainbow(m, x, y, m->is_ok);
		process(m);
	}
	return (0);
}

int		evt_live_key_pressed(int key, t_mlx *m)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == RIGHT_KEY || key == D_KEY)
		m->xo += 5;
	else if (key == LEFT_KEY || key == A_KEY)
		m->xo -= 5;
	else if (key == UP_KEY || key == W_KEY)
		m->yo -= 5;
	else if (key == DOWN_KEY || key == S_KEY)
		m->yo += 5;
	else if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 1;
	else if (49 == key)
	{
		m->zoom = 100;
		m->xo = 500;
		m->yo = 400;
		m->altitude = 1;
	}
	process(m);
	return (0);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY)
		m->is_shift = 0;
	process(m);
	return (0);
}

int		evt_live_mouse_clicked(int x, int y, int z, t_mlx *m)
{
	if (m->is_shift)
	{
		if (x == 6)
			m->altitude++;
		else if (x == 7)
			m->altitude--;
	}
	else
	{
		if (x == WHEELUP)
			m->zoom += 5;
		else if (x == WHEELDOWN)
			m->zoom -= 5;
		else if (x == BUT1_KEY)
			m->is_pressed = 1;
		else if (x == BUT1_KEY && (y >= WIN_H - 25 && y <= WIN_H - 5))
			m->is_ok = 1;
		else if (x == BUT3_KEY)
			m->iso = !m->iso;
	}
	put_rainbow(m, y, z, 0);
	process(m);
	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)y;
	(void)z;
	(void)m;
	if (x == WHEELUP)
		m->zoom++;
	else if (x == WHEELDOWN)
		m->zoom--;
	else if (x == BUT1_KEY && !(m->is_ok = 0))
	{
		m->is_pressed = 0;
		m->rotation_offset = (t_point){.x = x - 500, .y = y};
	}
	put_rainbow(m, y, z, 0);
	process(m);
	return (0);
}
