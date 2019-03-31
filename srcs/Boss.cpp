/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:25:34 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:01:28 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boss.hpp"

int	Boss::_globalLives = BOSS_LIVES;
int Boss::_bossPhase = 0;

Boss::Boss( void ) {
	
	Boss::_rcp += time( NULL );
	
	this->_lives = 50;
	this->_posx = (FT_LINES - 2) / 2;
	this->_posy = (COLUMNS - 2) / 2;
	this->_direction = FT_EAST; // to the left by default
	this->_appearance = 'x';
	this->_directionSize = 20;
	this->_directionIndex = 0;
	this->_color = FT_RED;
	this->_directionBuf[0] = FT_NORTH;
	this->_directionBuf[1] = FT_NORTH;
	this->_directionBuf[2] = FT_NORTH;
	this->_directionBuf[3] = FT_NORTH;
	this->_directionBuf[4] = FT_NORTH;

	this->_directionBuf[5] = FT_SOUTH;
	this->_directionBuf[6] = FT_SOUTH;
	this->_directionBuf[7] = FT_SOUTH;
	this->_directionBuf[8] = FT_SOUTH;
	this->_directionBuf[9] = FT_SOUTH;
	this->_directionBuf[10] = FT_SOUTH;
	this->_directionBuf[11] = FT_SOUTH;
	this->_directionBuf[12] = FT_SOUTH;
	this->_directionBuf[13] = FT_SOUTH;
	this->_directionBuf[14] = FT_SOUTH;

	this->_directionBuf[15] = FT_NORTH;
	this->_directionBuf[16] = FT_NORTH;
	this->_directionBuf[17] = FT_NORTH;
	this->_directionBuf[18] = FT_NORTH;
	this->_directionBuf[19] = FT_NORTH;
}

Boss::Boss( int posx, int posy, int direction, int color, char ap) {
	Boss::_rcp += time( NULL );
	
	this->_lives = 50;
	this->_posx = posx;
	this->_posy = posy;
	this->_direction = direction;
	this->_appearance = ap;
	this->_directionSize = 20;
	this->_directionIndex = 0;
	this->_color = color;
	this->_directionBuf[0] = FT_NORTH;
	this->_directionBuf[1] = FT_NORTH;
	this->_directionBuf[2] = FT_NORTH;
	this->_directionBuf[3] = FT_NORTH;
	this->_directionBuf[4] = FT_NORTH;

	this->_directionBuf[5] = FT_SOUTH;
	this->_directionBuf[6] = FT_SOUTH;
	this->_directionBuf[7] = FT_SOUTH;
	this->_directionBuf[8] = FT_SOUTH;
	this->_directionBuf[9] = FT_SOUTH;
	this->_directionBuf[10] = FT_SOUTH;
	this->_directionBuf[11] = FT_SOUTH;
	this->_directionBuf[12] = FT_SOUTH;
	this->_directionBuf[13] = FT_SOUTH;
	this->_directionBuf[14] = FT_SOUTH;

	this->_directionBuf[15] = FT_NORTH;
	this->_directionBuf[16] = FT_NORTH;
	this->_directionBuf[17] = FT_NORTH;
	this->_directionBuf[18] = FT_NORTH;
	this->_directionBuf[19] = FT_NORTH;

}

Boss::Boss( Boss const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = 'x';
}

Boss::~Boss( void ) {
	return ;
}

Boss &		Boss::operator=( Boss const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = 'x';
	return *this;
}
/*
bool			Boss::isAlive( void ) const {
	if (this->_lives > 0) {
		return true;
	} else {
		return false;
	}
}

int				Boss::getLives( void ) const {
	return this->_lives;
}
*/
int				Boss::getGlobalLives( void ) const {
	return Boss::_globalLives;
}

void			Boss::setGlobalLives( int n ) {
	Boss::_globalLives = n;
}

void			Boss::setPhase(int n)
{
	Boss::_bossPhase = n;
}

int				Boss::getColor( void ) const {
	return this->_color;
}

void			Boss::setColor( int color ) {
	this->_color = color;
}

bool			Boss::isAlive(void) const
{
	if (Boss::_globalLives == 0)
		return false;
	return true;
}

void			Boss::display( void ) {
	this->_move(FT_LINES, COLUMNS);
	move(this->_posx, this->_posy);
	addch(this->_appearance);
}

void			Boss::erase(void) {
	if (Boss::_bossPhase == 0 && this->_posy == (COLUMNS / 2))
		Boss::_bossPhase = 1;
	move(this->_posx, this->_posy);
	addch(' ');
}

void			Boss::_move( int const max_x, int const max_y ) {
	this->changeDirection();
	switch (this->_direction) {
		case FT_FIXED: // do nothing
			break ;
		case FT_EAST: // to the right
			if (this->_posy < max_y - 1) { this->_posy++; }
			break ;
		case FT_SOUTH: // to below
			if (this->_posx < max_x - 1) { this->_posx++; }
			break ;
		case FT_WEST: // to the left
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

void			Boss::changeDirection( void ) {
	if (Boss::_bossPhase == 0)
		return ;
	if (Boss::_bossPhase == 1)
	{
		this->_direction = this->_directionBuf[this->_directionIndex];
		this->_directionIndex++;
		if (this->_directionIndex >= this->_directionSize)
			this->_directionIndex = 0;
	}
}

EntityList			*Boss::shoot( void ) const {
	if (this->_appearance == '=')
		return (new EntityList(new Shot( this->getPosx(), this->getPosy() - 1 , 3, 1, '-')));
	else
		return (NULL);
}
