/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APhysicalEntity.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:36:52 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:15:15 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "APhysicalEntity.hpp"

APhysicalEntity::APhysicalEntity( void ) {
	this->_posx = 1;
	this->_posy = 1;
	this->_direction = 1;
	this->_appearance = 'x';
	this->_color = 0;
}

APhysicalEntity::~APhysicalEntity( void ) {}

APhysicalEntity &	APhysicalEntity::operator=( APhysicalEntity const & cp ) {
	this->_posx = cp.getPosx();
	this->_posy = cp.getPosy();
	this->_direction = cp.getDirection();
	return *this;
}

int			APhysicalEntity::getPosx( void ) const {
	return this->_posx;
}

int			APhysicalEntity::getPosy( void ) const {
	return this->_posy;
}

int			APhysicalEntity::getDirection( void ) const {
	return this->_direction;
}

void		APhysicalEntity::setPosx( int pos ) {
	this->_posx = pos;
}

void		APhysicalEntity::setPosy( int pos ) {
	this->_posy = pos;
}

int			APhysicalEntity::getColor(void) const
{
	return (this->_color);
}

void		APhysicalEntity::setPhase(int n)
{
	(void)n;
}

void		APhysicalEntity::setGlobalLives(int n)
{
	(void)n;
}

int			APhysicalEntity::getGlobalLives(void) const
{
	return (0);
}

bool		APhysicalEntity::isAlive(void) const
{
	return false;
}

void		APhysicalEntity::erase(void)
{
	move(this->_posx, this->_posy);
	addch(' ');
}

void		APhysicalEntity::setDirection( int direction ) {
	if (direction < 0 || direction > 4) {
		return ;
	}
	this->_direction = direction;
}
