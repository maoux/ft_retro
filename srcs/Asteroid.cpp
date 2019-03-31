/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Asteroid.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:25:34 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 17:41:46 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Asteroid.hpp"

Asteroid::Asteroid( void ) {
	this->_posx = 10;
	this->_posy = 140;	
	this->_direction = FT_EAST;
	this->_appearance = '*';
}

Asteroid::Asteroid( int posx, int posy, char ap ) {
	this->_posx = posx;
	this->_posy = posy;
	this->_direction = FT_EAST;
	this->_appearance = ap;
}

Asteroid::Asteroid( Asteroid const & cp ) {
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '*';
}

Asteroid::~Asteroid( void ) {
	return ;
}

Asteroid &		Asteroid::operator=( Asteroid const & cp ) {
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '*';
	return *this;
}

void			Asteroid::display( void ) {
	move(this->_posx, this->_posy);
	addch(' ');
	this->_move(FT_LINES, COLUMNS);
	move(this->_posx, this->_posy);
	attron(COLOR_PAIR(FT_BLUE));
	addch(this->_appearance);
	attroff(COLOR_PAIR(FT_BLUE));
}

void			Asteroid::_move( int const max_x, int const max_y ) {
	switch (this->_direction) {
		case FT_FIXED: // do nothing
			break ;
		case FT_WEST: // to the right
			if (this->_posy < max_y - 1) { this->_posy++; }
			break ;
		case FT_SOUTH: // to below
			if (this->_posx < max_x - 1) { this->_posx++; }
			break ;
		case FT_EAST: // to the left
			this->_posy--;
			break ;
		case FT_NORTH: // to above
			if ( this->_posx > 1) { this->_posx--; }
			break ;
		case FT_SOUTH_WEST: // sud-ouest
			if (this->_posx < max_x - 1) { this->_posx++; }
			this->_posy--;
			break;
		case FT_SOUTH_EAST: // sud est
			if (this->_posx < max_x - 1) { this->_posx++; }
			if (this->_posy < max_y - 1) { this->_posy++; }
			break;
		case FT_NORTH_EAST: // nord est
			if ( this->_posx > 1) { this->_posx--; }
			if (this->_posy < max_y - 1) { this->_posy++; }
			break;
		case FT_NORTH_WEST: // nord ouest
			if ( this->_posx > 1) { this->_posx--; }
			this->_posy--;
			break;
	}
}

