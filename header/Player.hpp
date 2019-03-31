/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:18:31 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 16:06:43 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "APhysicalEntity.hpp"
# include "Shot.hpp"
# include "EntityList.hpp"
# include <ncurses.h>

class	Player : public APhysicalEntity {

	private:
		int					_score;	
		int					_lives;
		virtual void		_move( int const, int const );

	public:

		Player( void );
		Player( Player const & );
		virtual ~Player( void );

		Player &	operator=( Player const & );

		virtual void		display( void );
		EntityList			*shoot( void ) const;

		bool				isAlive( void ) const;
		int					getLives( void ) const;
		void				setLives( int );

		int					getScore( void ) const;
		void				setScore( int );
};

#endif
