/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 09:42:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xy g_mouse = {
	.x = 0,
	.y = 0
};

t_key g_key[] = {
	{HAUT, &key_up},
	{BAS, &key_down},
	{GAUCHE, &key_left},
	{DROITE, &key_right},
	{ESC, &key_esc}
};

int		key_up(t_mlx m)
{
	(void)m;
	return (0);
}

int		key_down(t_mlx m)
{
	(void)m;
	return (0);
}

int		key_left(t_mlx m)
{
	(void)m;
	return (0);
}

int		key_right(t_mlx m)
{
	(void)m;
	return (0);
}

int		key_esc(t_mlx m)
{
	(void)m;
	exit(0);
	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)x;
	g_mouse = (t_xy){.x = y, .y = z};
	mlx_clear_window(m->i, m->w);
	if (SHOW_LIVE_MOUSE)
	{
		string(*m, (t_xy){.x = g_mouse.x, .y = g_mouse.y + 30}, 0xFFFF00,
			ft_itoa_base(y, 10, 0));
		string(*m, (t_xy){.x = g_mouse.x, .y = g_mouse.y + 50}, 0xFFFF00,
			ft_itoa_base(z, 10, 0));
	}
	return (0);
}

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	g_mouse = (t_xy){.x = x, .y = y};
	mlx_clear_window(m->i, m->w);
	if (SHOW_LIVE_MOUSE)
	{
		string(*m, (t_xy){.x = g_mouse.x, .y = g_mouse.y + 30}, 0xFFFF00,
			ft_itoa_base(x, 10, 0));
		string(*m, (t_xy){.x = g_mouse.x, .y = g_mouse.y + 50}, 0xFFFF00,
			ft_itoa_base(y, 10, 0));
	}
	(void)m;
	return (0);
}

int		evt_live_key_pressed(int key, t_mlx *m)
{
	int i = -1;

	while (g_key[++i].key)
		if (g_key[i].key == key)
			g_key[i].function && g_key[i].function(*m);
	mlx_clear_window(m->i, m->w);
	if (SHOW_LIVE_KEY)
		string(*m, (t_xy){.x = g_mouse.x + 40, .y = g_mouse.y}, 0x00FF00,
			ft_itoa_base(key, 10, 0));
	(void)key;
	return (0);
}

int		evt_live_key_move(int key, t_mlx *m)
{
	int i = -1;

	while (g_key[++i].key)
		if (g_key[i].key == key)
			g_key[i].function && g_key[i].function(*m);
	mlx_clear_window(m->i, m->w);
	if (SHOW_LIVE_KEY)
	{
		string(*m, (t_xy){.x = g_mouse.x + 40, .y = g_mouse.y}, 0x00FF00,
			ft_itoa_base(key, 10, 0));
	}
	return (0);
}
