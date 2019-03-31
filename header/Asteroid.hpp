/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Asteroid.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:18:31 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 17:06:24 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTEROID_H
# define ASTEROID_H

# include "APhysicalEntity.hpp"
# include "EntityList.hpp"
# include <ncurses.h>
# include "ft_retro.h"

class	Asteroid : public APhysicalEntity {

	private:
		
		virtual void		_move( int const, int const );

	public:

		Asteroid( void );
		Asteroid( int, int, char );
		Asteroid( Asteroid const & );
		virtual ~Asteroid( void );

		Asteroid &	operator=( Asteroid const & );

		virtual void		display( void );

};

#endif
