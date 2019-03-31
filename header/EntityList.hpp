/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EntityList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:51:22 by arobion           #+#    #+#             */
/*   Updated: 2019/03/31 21:03:14 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_LIST_HPP
# define ENTITY_LIST_HPP

# include "ft_retro.h"
//# include "APhysicalEntity.hpp"

struct EntityList
{

	EntityList(void);
	EntityList(APhysicalEntity *);
	APhysicalEntity		*content;
	EntityList			*next;
};

#endif
