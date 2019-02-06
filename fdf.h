/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 09:45:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx/mlx.h"
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>

# define KPRESS	3
# define KMOVE 	2
# define MPRESS	4
# define MMOVE 	6
# define DROITE 124
# define GAUCHE 123
# define HAUT 126
# define BAS 125
# define ESC 53
# define SHOW_LIVE_MOUSE 1
# define SHOW_LIVE_KEY 1

typedef struct	s_xy
{
	int				x;
	int				y;

}				t_xy;
typedef struct	s_mlx
{
	void			*i;
	void			*w;

}				t_mlx;
typedef struct	s_key
{
	int				key;
	int				(*function)(t_mlx m);

}				t_key;
int				p(t_mlx m, t_xy i, int color);
int				string(t_mlx m, t_xy i, int color, char *string);
void			ligne(t_mlx m, t_xy o, t_xy f);
void			circle_points(t_mlx m, t_xy c, t_xy o, int color);
void			circle_midpoint(t_mlx m, t_xy c, int radius, int color);
int				evt_live_mouse_pressed(int x, int y, int z, t_mlx *m);
int				evt_live_key_move(int key, t_mlx *m);
int				evt_live_key_pressed(int key, t_mlx *m);
int				evt_live_mouse_move(int x, int y, t_mlx *m);
int				fdf(void);
int				key_up(t_mlx m);
int				key_down(t_mlx m);
int				key_left(t_mlx m);
int				key_right(t_mlx m);
int				key_esc(t_mlx m);
#endif
