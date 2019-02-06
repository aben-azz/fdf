/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 11:25:48 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include "fdf.h"


int clear(t_mlx m)
{
	mlx_clear_window(m.i, m.w);
	return (menu(m));
}

int menu(t_mlx m)
{
	string(m, (t_xy){.x = 250, .y = 200}, 0xFFFF00, "Gros delire ca");
	string(m, (t_xy){.x = 300, .y = 200}, 0xFF00FF, "mec je suis ou");
	string(m, (t_xy){.x = 200, .y = 250}, 0x00FF00, "PTDR JFKOI LA");
	string(m, (t_xy){.x = 200, .y = 300}, 0x2F2F2F, "JFK LA OSSI XD");
	return (0);
}

int		fdf(void)
{
	t_mlx m;

	m.i = mlx_init();
	m.w = mlx_new_window(m.i, 2000, 2000, "GROS DELIRES");
	clear(m);
	mlx_hook(m.w, KPRESS, 0, evt_live_key_pressed, &m);
	mlx_hook(m.w, KCLICK, 0, evt_live_key_clicked, &m);
	mlx_hook(m.w, MMOVE, 0, evt_live_mouse_move, &m);
	mlx_hook(m.w, MCLICK, 0, evt_live_mouse_clicked, &m);
	mlx_hook(m.w, MPRESS, 0, evt_live_mouse_pressed, &m);
	mlx_loop(m.i);
	return (18);
}
