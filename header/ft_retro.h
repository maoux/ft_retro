/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retro.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:25:11 by arobion           #+#    #+#             */
/*   Updated: 2019/03/31 21:46:08 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RETRO_H
# define FT_RETRO_H

# include <iostream>
# include <unistd.h>
# include <stdio.h>
# include "APhysicalEntity.hpp"
# define FT_LINES 25
# define COLUMNS 100
# define FRAMRATE 40
# define MAX_ENEMY 15
# define BOSS_APPEAR 30
# define BOSS_LIVES 100
# define BOSS_SCORE 150

# define FT_RED 1
# define FT_GREEN 2 
# define FT_YELLOW 3
# define FT_BLUE 4

# define FT_FIXED 0
# define FT_WEST 1
# define FT_SOUTH 2
# define FT_EAST 3
# define FT_NORTH 4
# define FT_SOUTH_WEST 5
# define FT_SOUTH_EAST 6
# define FT_NORTH_EAST 7
# define FT_NORTH_WEST 8

#endif
