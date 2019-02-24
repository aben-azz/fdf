/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/24 01:45:14 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point g_mouse = {
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



int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	//clear(*m);
	g_mouse = (t_point){.x = x, .y = y};
	// if (SHOW_LIVE_MOUSE)
	// {
	// 	string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 30}, 0xFFFF00,
	// 		ft_itoa_base(x, 10, 0));
	// 	string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 50}, 0xFFFF00,
	// 		ft_itoa_base(y, 10, 0));
	// }
	clear(*m);
	int i = 0;
	//int color = 0xFF0000;
	int red = 255;
	int blue = 0;
	int green = 0;
	while (i++ < 300)
	{
		(green == 0 && red == 255) && (blue += 5);
		(green == 255 && red == 0) && (blue -= 5);
		(green == 0 && blue == 255) && (red -= 5);
		(green == 255 && blue == 0) && (red += 5);
		(red == 0 && blue == 255) && (green += 5);
		(red == 255 && blue == 0) && (green -= 5);
		if(i == g_mouse.x - 300 && (g_mouse.y >= 300 && g_mouse.y <= 310)){
			circle_midpoint(*m, (t_point){.x = 300 + i, .y = 305}, 10, rgb2dec(red, blue, green));
			string(*m, (t_point){.x = 300 + i, .y = 400}, rgb2dec(red, blue, green), "PTDRRRRRR");
		}
		rect(*m, (t_point){.x = 300 + i, .y = 300}, (t_point){.x = 1, .y = 10},
			rgb2dec(red, blue, green));
	}
	string(*m, (t_point){.x = 300 + i, .y = 300}, 0xFF0000, ft_itoa(g_mouse.x));
	(void)m;


	return (0);
}

int		evt_live_key_clicked(int key, t_mlx *m)
{
	int i;

	i = -1;
	//clear(*m);
	while (g_key[++i].key)
		if (g_key[i].key == key)
			g_key[i].function && g_key[i].function(*m);
	if (SHOW_LIVE_KEY)
		string(*m, (t_point){.x = g_mouse.x + 40, .y = g_mouse.y}, 0x00FF00,
			ft_itoa_base(key, 10, 0));
	(void)key;
	return (0);
}


int		evt_live_mouse_clicked(int x, int y, int z, t_fdf *f)
{
	(void)x;
	(void)f;
	g_mouse = (t_point){.x = y, .y = z};
	// menu(*m);
	// g_mouse = (t_point){.x = y, .y = z};
	// if (SHOW_LIVE_MOUSE)
	// {
	// 	string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 30}, 0xFFFF00,
	// 		ft_itoa_base(y, 10, 0));
	// 	string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 50}, 0xFFFF00,
	// 		ft_itoa_base(z, 10, 0));
	// }

	//draw_picker(*m, 0, 0, 255);
		//printf("ds le y\n");

	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)x;
	g_mouse = (t_point){.x = y, .y = z};
	if (SHOW_LIVE_MOUSE)
	{
		string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 30}, 0xFFFF00,
			ft_itoa_base(y, 10, 0));
		string(*m, (t_point){.x = g_mouse.x, .y = g_mouse.y + 50}, 0xFFFF00,
			ft_itoa_base(z, 10, 0));
	}
	return (0);
}
