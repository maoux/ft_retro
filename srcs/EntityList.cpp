/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EntityList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:46:03 by arobion           #+#    #+#             */
/*   Updated: 2019/03/30 17:05:41 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_retro.h"
#include "EntityList.hpp"

EntityList::EntityList(void):
	content(NULL),
	next(NULL)
{
}

EntityList::EntityList(APhysicalEntity *entity):
	next(NULL)
{
	this->content = entity;
}
