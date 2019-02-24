/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/24 02:01:05 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_key g_key[] = {
	{HAUT, &key_up},
	{BAS, &key_down},
	{GAUCHE, &key_left},
	{DROITE, &key_right},
	{ESC, &key_esc}
};

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	(void)m;
	return (0);
}

int		evt_live_key_clicked(int key, t_mlx *m)
{
	int i;

	i = -1;
	while (g_key[++i].key)
		if (g_key[i].key == key)
			g_key[i].function && g_key[i].function(*m);
	(void)key;
	return (0);
}

int		evt_live_mouse_clicked(int x, int y, int z, t_mlx *m)
{
	int i;
	int color[3];

	(void)x;
	i = 0;
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
	clear(*m);
	while (i++ < 300)
	{
		(color[1] == 0 && color[0] == 255) && (color[2] += 5);
		(color[1] == 255 && color[0] == 0) && (color[2] -= 5);
		(color[1] == 0 && color[2] == 255) && (color[0] -= 5);
		(color[1] == 255 && color[2] == 0) && (color[0] += 5);
		(color[0] == 0 && color[2] == 255) && (color[1] += 5);
		(color[0] == 255 && color[2] == 0) && (color[1] -= 5);
		if (i == y - 300 && (z >= 300 && z <= 310))
			circle_midpoint(*m, (t_point){.x = 300 + i, .y = 305}, 10,
				rgb2dec(color[0], color[2], color[1]));
		rect(*m, (t_point){.x = 300 + i, .y = 300}, (t_point){.x = 1, .y = 10},
			rgb2dec(color[0], color[2], color[1]));
	}
	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)x;
	(void)y;
	(void)z;
	(void)m;
	return (0);
}
