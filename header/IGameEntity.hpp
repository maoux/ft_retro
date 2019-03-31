/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGameEntity.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 12:21:42 by heynard           #+#    #+#             */
/*   Updated: 2019/03/30 20:32:07 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IGAME_ENTITY_H
# define IGAME_ENTITY_H

class	IGameEntity {

	private:
	
		virtual void		_move( int const, int const ) = 0;

	protected:

		int		_posx;
		int		_posy;
		int		_direction;
		char	_appearance;

	public:

		virtual ~IGameEntity( void ) {}
		
		virtual void		display( void ) = 0;
		

		virtual int			getPosx( void ) const = 0;
		virtual int			getPosy( void ) const = 0;
		virtual int			getDirection( void ) const = 0;

		virtual void		setPosx( int ) = 0;
		virtual void		setPosy( int ) = 0;
		virtual void		setDirection( int ) = 0;

};

#endif
