/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:07:13 by arobion           #+#    #+#             */
/*   Updated: 2019/03/31 20:45:31 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_HPP
# define TERRAIN_HPP

# include "ft_retro.h"
# include "Player.hpp"
# include "Monster.hpp"
# include "EntityList.hpp"
# include "Shot.hpp"
# include "Boss.hpp"
# include <ctime>
# include <random>
# include "Asteroid.hpp"

class Map
{
	public:
		Map(void);
		~Map(void);
		Map(Map const &src);
		Map &operator=(Map const &src);

		int					getSizeY(void) const;
		int					getSizeX(void) const;
		EntityList			*getFirstShot(void) const;
		EntityList			*getFirstEnemy(void) const;
		Player				*getPlayer(void) const;
		int					getInput(void) const;
		int					getTotalEnemy(void) const;
		bool				getBossPhase(void) const;

		void				checkColisions(void);

		void				createEnemy(void);
		void				deleteEnemy(APhysicalEntity *);
		void				updateEnemy(EntityList *);

		void				addShot(EntityList *);
		void				deleteShot(APhysicalEntity *);
		void				updateShot(EntityList *);

		void				createAsteroid( void );
		void				deleteAsteroid( APhysicalEntity * );
		void				updateAsteroid( void );

		void				createBoss( void );
		void				displayBoss( void );
		void				deleteBoss( APhysicalEntity * );

		void				deleteMap(void);

	private:
		int				_sizeY;
		int				_sizeX;
		EntityList		*_firstShot;
		EntityList		*_firstEnemy;
		EntityList		*_firstAsteroid;
		EntityList		*_boss;
		Player			*_player;
		int				_totalEnemy;
		bool			_bossPhase;


};

#endif
