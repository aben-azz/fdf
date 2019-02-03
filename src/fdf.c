/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:26:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/03 11:01:04 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include <stdio.h>
#include "fdf.h"

int	fdf(void)
{
	void *m;
	void *windows;

	m = mlx_init();
	windows = mlx_new_window(m, 2000, 2000, "GROS DELIRES");
	int i = 1000;
	while (i-- > 0)
		mlx_pixel_put(m, windows, 200, 200 + i, 0xFFFF00);
	i = 1000;
	while (i-- > 0)
		mlx_pixel_put(m, windows, 200 + i, 200, 0xFFFF00);
	mlx_string_put(m, windows, 250, 200 + i, 0xFFFF00, "0xFFFF00");
	mlx_string_put(m, windows, 300, 200 + i, 0xFF00FF, "0xFFFF00");
	mlx_string_put(m, windows, 200, 250 + i, 0x00FF00, "0xFFFF00");
	mlx_string_put(m, windows, 200, 300 + i, 0x2F2F2F, "0xFFFF00");
	mlx_loop(m);
	return (18);
}
