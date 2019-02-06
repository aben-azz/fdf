/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 09:44:54 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/06 13:39:38 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_up(t_mlx m)
{
	(void)m;
	string(m, (t_xy){.x = 300, .y = 600}, RED, "EN HAUT");
	return (0);
}

int		key_down(t_mlx m)
{
	(void)m;
	string(m, (t_xy){.x = 380, .y = 600}, RED, "EN BAS");
	return (0);
}

int		key_left(t_mlx m)
{
	(void)m;
	string(m, (t_xy){.x = 460, .y = 600}, RED, "GAUCHE");
	return (0);
}

int		key_right(t_mlx m)
{
	(void)m;
	string(m, (t_xy){.x = 540, .y = 600}, RED, "DROITE");
	return (0);
}

int		key_esc(t_mlx m)
{
	(void)m;
	exit(0);
	return (0);
}
