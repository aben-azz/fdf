/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/24 01:42:05 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx/mlx.h"
# include "custom.h"
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# define KPRESS 2
# define KCLICK	3
# define MCLICK	4
# define MPRESS 5
# define MMOVE 	6
# define DROITE 124
# define GAUCHE 123
# define HAUT 126
# define BAS 125
# define ESC 53
# define SHOW_LIVE_MOUSE 0
# define SHOW_LIVE_KEY 0


typedef struct	s_point
{
	int				x;
	int				y;
	int				z;

}				t_point;
typedef struct	s_mlx
{
	void			*i;
	void			*w;

}				t_mlx;
typedef struct	s_fdf
{
	t_mlx			m;
	int				r;
	int				g;
	int				b;

}				t_fdf;

typedef struct	s_key
{
	int				key;
	int				(*function)(t_mlx m);

}				t_key;
int				p(t_mlx m, t_point i, int color);
int				string(t_mlx m, t_point i, int color, char *string);
void			ligne(t_mlx m, t_point o, t_point f, int color);
void			circle_points(t_mlx m, t_point c, t_point o, int color);
void			circle_midpoint(t_mlx m, t_point c, int radius, int color);
int				evt_live_mouse_clicked(int x, int y, int z, t_fdf *f);
int				evt_live_key_pressed(int key, t_mlx *m);
int				evt_live_key_clicked(int key, t_mlx *m);
int				evt_live_mouse_move(int x, int y, t_mlx *m);
int				evt_live_mouse_pressed(int x, int y, int z, t_mlx *m);
int				fdf(void);
int				key_up(t_mlx m);
int				key_down(t_mlx m);
int				key_left(t_mlx m);
int				key_right(t_mlx m);
int				key_esc(t_mlx m);
int				clear(t_mlx m);
int				menu(t_mlx m);
t_point			*rotate(t_point a, t_point b, double angle);
int				rect(t_mlx m, t_point from, t_point l, int color);
int				rgb2dec(int red, int green, int blue);
#endif
