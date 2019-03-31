/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:18:31 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 19:39:25 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONSTER_H
# define MONSTER_H

# include "APhysicalEntity.hpp"
# include "EntityList.hpp"
# include "Shot.hpp"
# include <ctime>
# include <ncurses.h>
# include <random>
# include "ft_retro.h"
# include <iostream>


class	Monster : public APhysicalEntity {

	protected:
		
		static int	_rcp;
		int			_lives;
		virtual void		_move( int const, int const );
		int					_directionBuf[12];
		int					_directionIndex;
		int					_directionSize;

	public:

		Monster( void );
		Monster( Monster const & );
		virtual ~Monster( void );

		Monster &	operator=( Monster const & );

		virtual void		display( void );
		virtual EntityList	*shoot( void ) const;

		bool				isAlive( void ) const;
		int					getLives( void ) const;

		void				changeDirection( void );
};

#endif
