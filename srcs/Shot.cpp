/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shot.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:25:34 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 16:45:52 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shot.hpp"

Shot::Shot( void ) {
	this->_posx = 1;
	this->_posy = 1;
	this->_direction = FT_WEST;
	this->_appearance = '-';
	this->_color = FT_YELLOW;
}

Shot::Shot( int posx, int posy ) {
	this->_direction = 1;
	this->_posx = posx;
	this->_posy = posy;
	this->_appearance = '-';
	this->_color = FT_YELLOW;
}

Shot::Shot( Shot const & cp ) {
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '-';
	this->_color = cp.getColor();
}

Shot::Shot( int posx, int posy, int direction, int color, char ap) {
	this->_posx = posx;
	this->_posy = posy;
	this->_direction = direction;
	this->_appearance = ap;
	this->_color = color;
}

Shot::~Shot( void ) {
	return ;
}

Shot &		Shot::operator=( Shot const & cp ) {
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '-';
	this->_color = cp.getColor();
	return *this;
}

void			Shot::display( void ) {
	move(this->_posx, this->_posy);
	addch(' ');
	this->_move(FT_LINES, COLUMNS);
	move(this->_posx, this->_posy);
	attron(COLOR_PAIR(this->_color));
	addch(this->_appearance);
	attroff(COLOR_PAIR(this->_color));
}

void			Shot::_move( int const max_x, int const max_y ) {
	switch (this->_direction) {
		case FT_FIXED: // do nothing
			break ;
		case FT_WEST: // to the right - we must verify outside if the shot is still visible
			(void)max_y;
			this->_posy++;
			break ;
		case FT_SOUTH: // to below
			if (this->_posx < max_x - 1) { this->_posx++; }
			break ;
		case FT_EAST: // to the left
			if (this->_posy > 0) { this->_posy--; }
			break ;
		case FT_NORTH: // to above
			if ( this->_posx > 1) { this->_posx--; }
			break ;
	}
}

void			Shot::setColor( int c ) {
	this->_color = c;
}

int				Shot::getColor( void ) const {
	return this->_color;
}


