/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:25:34 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:15:13 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Monster.hpp"

int Monster::_rcp = 0;

Monster::Monster( void ) {
	
	Monster::_rcp += time( NULL );

	srand(time( NULL ) + Monster::_rcp);
	
	this->_lives = 1;
	this->_posx = rand() % FT_LINES + 1;
	this->_posy = COLUMNS - 2;
	this->_direction = FT_EAST; // to the left by default
	this->_appearance = 'x';
	this->_directionSize = 12;
	this->_directionIndex = 0;
	this->_directionBuf[0] = FT_NORTH_WEST;
	this->_directionBuf[1] = FT_NORTH_WEST;
	this->_directionBuf[2] = FT_NORTH_WEST;
	this->_directionBuf[3] = FT_SOUTH_WEST;
	this->_directionBuf[4] = FT_SOUTH_WEST;
	this->_directionBuf[5] = FT_SOUTH_WEST;
	this->_directionBuf[6] = FT_SOUTH_WEST;
	this->_directionBuf[7] = FT_SOUTH_WEST;
	this->_directionBuf[8] = FT_SOUTH_WEST;
	this->_directionBuf[9] = FT_NORTH_WEST;
	this->_directionBuf[10] = FT_NORTH_WEST;
	this->_directionBuf[11] = FT_NORTH_WEST;
}

Monster::Monster( Monster const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = 'x';
}

Monster::~Monster( void ) {
	return ;
}

Monster &		Monster::operator=( Monster const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = 'x';
	return *this;
}

bool			Monster::isAlive( void ) const {
	if (this->_lives > 0) {
		return true;
	} else {
		return false;
	}
}

int				Monster::getLives( void ) const {
	return this->_lives;
}

void			Monster::display( void ) {
	move(this->_posx, this->_posy);
	addch(' ');
	this->_move(FT_LINES, COLUMNS);
	move(this->_posx, this->_posy);
	addch(this->_appearance);
	//this->_direction = 3;
}

void			Monster::_move( int const max_x, int const max_y ) {
	this->changeDirection();
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
			if (this->_posy < 1) { this->_lives = 0; }
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

void			Monster::changeDirection( void ) {
	
	this->_direction = this->_directionBuf[this->_directionIndex];
	this->_directionIndex++;
	if (this->_directionIndex >= this->_directionSize)
		this->_directionIndex = 0;
}

EntityList			*Monster::shoot( void ) const {
	return (new EntityList(new Shot( this->getPosx(), this->getPosy() - 1 , 3, 1, '-')));
}
