/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 14:18:27 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include "fdf.h"

int rect(t_mlx m, t_xy from, t_xy l, int color)
{

	ligne(m, (t_xy){.x = from.x + l.x, .y = from.y},
		(t_xy){.x = from.x + l.x, .y =from.y + l.y}, color);
	ligne(m, (t_xy){.x = from.x, .y = from.y},
		(t_xy){.x = from.x + l.x, .y = from.y}, color);
	ligne(m, (t_xy){.x = from.x, .y = from.y},
		(t_xy){.x = from.x, .y = from.y + l.y}, color);
	ligne(m, (t_xy){.x = from.x, .y = from.y + l.y},
		(t_xy){.x = from.x + l.x, .y = from.y}, color);
	return (0);
}
int fill_rect(t_mlx m, t_xy from, t_xy l, int color)
{
	int i;

	i = 0;
	while (i++ < l.y)
		ligne(m, (t_xy){.x = from.x, .y = from.y + i},
			(t_xy){.x = from.x + l.x, .y = from.y}, color);
	return (0);
}
int rectangle(t_mlx m, t_xy from, t_xy l, int color)
{
	rect(m, from, l, color);
	fill_rect(m, from, l, color);
	return (0);
}

int clear(t_mlx m)
{
	mlx_clear_window(m.i, m.w);
	//rectangle(m, (t_xy){.x = 0, .y = 0}, (t_xy){.x = 2000, .y = 1600}, BLUE2);
	return (menu(m));
}

int menu(t_mlx m)
{
	(void)m;
	//rect(m, (t_xy){.x = 300, .y = 300}, (t_xy){.x = 60, .y  = 20}, PURPLE1);
	//fill_rect(m, (t_xy){.x = 300, .y = 300}, (t_xy){.x = 60, .y  = 20}, PURPLE1);
	rectangle(m, (t_xy){.x = 0, .y = 0}, (t_xy){.x = 2000, .y  = 300}, BLUE2);
	circle_midpoint(m, (t_xy){.x = 200, .y = 1600 - 200}, 180, GREEN);
	return (0);
}

int		fdf(void)
{
	t_mlx m;

	m.i = mlx_init();
	m.w = mlx_new_window(m.i, 2000, 1600, "GROS DELIRES");
	clear(m);
	mlx_hook(m.w, KPRESS, 0, evt_live_key_pressed, &m);
	mlx_hook(m.w, KCLICK, 0, evt_live_key_clicked, &m);
	mlx_hook(m.w, MMOVE, 0, evt_live_mouse_move, &m);
	mlx_hook(m.w, MCLICK, 0, evt_live_mouse_clicked, &m);
	mlx_hook(m.w, MPRESS, 0, evt_live_mouse_pressed, &m);
	mlx_loop(m.i);
	return (18);
}
