/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:18:31 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 20:52:26 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOSS_H
# define BOSS_H

#include "Monster.hpp"

class	Boss : public Monster {

	private:

		static int			_globalLives;
		static int			_bossPhase;
		int					_color;
		int					_directionBuf[20];



	protected:

		virtual void		_move( int const, int const );

	public:

		Boss( void );
		Boss( int, int, int, int, char);
		Boss( Boss const & );
		virtual ~Boss( void );

		Boss &	operator=( Boss const & );

		virtual void		display( void );
		virtual void		erase(void);
		virtual EntityList	*shoot( void ) const;
		virtual	bool		isAlive(void) const;

		int					getColor( void ) const;
		void				setColor( int );
		int					getGlobalLives( void ) const;
		void				setGlobalLives( int );
		void				setPhase(int);

		void				changeDirection( void );

};

#endif
