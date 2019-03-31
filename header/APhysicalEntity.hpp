/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhysicalEntity.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:29:20 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:12:48 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICAL_ENTITY_H
# define PHYSICAL_ENTITY_H

# include "IGameEntity.hpp"
# include <ncurses.h>
//# include "EntityList.hpp"
//# include "Shot.hpp"


class	APhysicalEntity : public IGameEntity {

	private:
		virtual void		_move( int const, int const ) = 0;
		int					_color;

	protected:

	public:
		APhysicalEntity( void );
		APhysicalEntity( APhysicalEntity const & );
		virtual ~APhysicalEntity( void );

		APhysicalEntity &	operator=( APhysicalEntity const & );

		virtual void		display( void ) = 0;
		virtual	void		erase( void );

		virtual int			getPosx( void ) const;
		virtual int			getPosy( void ) const;
		virtual int			getDirection( void ) const;
		virtual int			getColor( void ) const;
		virtual void		setGlobalLives(int n);
		virtual int			getGlobalLives(void) const;
		virtual bool		isAlive(void) const;
		virtual void		setPhase(int);

		virtual void		setPosx( int );
		virtual void		setPosy( int );
		virtual void		setDirection( int );
//		virtual	EntityList	*shoot(void);

};

#endif
