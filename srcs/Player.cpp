/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:25:34 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:40:14 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player( void ) {
	this->_score = 0;
	this->_lives = 10;
	this->_posx = 12;
	this->_posy = 1;
	this->_direction = FT_FIXED;
	this->_appearance = '>';
}

Player::Player( Player const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '>';
}

Player::~Player( void ) {
	return ;
}

Player &		Player::operator=( Player const & cp ) {
	this->_lives = cp.getLives();
	this->setPosx(cp.getPosx());
	this->setPosy(cp.getPosy());
	this->setDirection(cp.getDirection());
	this->_appearance = '>';
	return *this;
}

bool			Player::isAlive( void ) const {
	if (this->_lives > 0) {
		return true;
	} else {
		return false;
	}
}

int				Player::getLives( void ) const {
	return this->_lives;
}

void			Player::setLives(int n)  
{
	this->_lives = n;
}

int				Player::getScore( void ) const {
	return this->_score;
}

void			Player::setScore( int s ) {
	this->_score = s;
}

void			Player::display( void ) {
	move(this->_posx, this->_posy); // ncurses cursor
	addch(' ');
	this->_move(FT_LINES, COLUMNS);  // update posx posy
	move(this->_posx, this->_posy); // ncurses cursor
	addch(this->_appearance);
	this->_direction = 0;
	move(FT_LINES + 1, 2);
	addstr("                            ");
	move(FT_LINES + 1, 2);
	attron(COLOR_PAIR(FT_GREEN));
	addstr("LIVES : ");
	for (int i = 0; i < this->_lives; i++) {
		addch('+' | COLOR_GREEN);
	}
	attroff(COLOR_PAIR(FT_GREEN));
	move(FT_LINES + 1, 12 + this->_lives);
	addstr("                          ");
	move(FT_LINES + 1, 12 + this->_lives);
	attron(COLOR_PAIR(FT_BLUE));
	addstr("SCORE : ");
	{
		int			n = this->_score;
		int			tmp, len, neg;
		char		ret[10];

		tmp = n;
		neg = 0;
		len = 2;
		if (n < 0) {
			n *= 1;
			neg = 1;
		}
		while (tmp /= 10) {
			len++;
		}
		len += neg;
		for (int i = 0; i < len;i++) {
			ret[len] = 0;
		}
		while (len--) {
			ret[len] = n % 10 + '0';
			n = n / 10;
		}
		if (neg) {
			ret[0] = '-';
		}
		addstr(ret);
	}
	attroff(COLOR_PAIR(FT_BLUE));
}

void			Player::_move( int const max_x, int const max_y ) {
	switch (this->_direction) {
		case FT_FIXED: // do nothing
			return ;
		case FT_WEST: // to the right
			if (this->_posy < max_y - 1) { this->_posy++; }
			break ;
		case FT_SOUTH: // to below
			if (this->_posx < max_x - 1) { this->_posx++; }
			break ;
		case FT_EAST: // to the left
			if (this->_posy > 1) { this->_posy--; }
			break ;
		case FT_NORTH: // to above
			if ( this->_posx > 1) { this->_posx--; }
			break ;
	}
}

EntityList			*Player::shoot( void ) const {
	return (new EntityList(new Shot( this->getPosx(), this->getPosy() + 1 )));
}
