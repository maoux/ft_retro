/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:07:36 by arobion           #+#    #+#             */
/*   Updated: 2019/03/31 21:42:32 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

Map::Map(void):
	_sizeY(FT_LINES),
	_sizeX(COLUMNS),
	_firstShot(NULL),
	_firstEnemy(NULL),
	_firstAsteroid(NULL),
	_boss(NULL),
	_totalEnemy(0),
	_bossPhase(false)
{
	this->_player = new Player;
}

Map::~Map(void)
{
}

Map::Map(Map const &src)
{
	*this = src;
}

Map		&Map::operator=(Map const &src)
{
	if (&src != this)
	{
		this->_sizeY = src._sizeY;
		this->_sizeX = src._sizeX;
	}
	return (*this);
}

int		Map::getSizeY(void) const
{
	return (this->_sizeY);
}

int		Map::getSizeX(void) const
{
	return (this->_sizeX);
}

EntityList			*Map::getFirstShot(void) const
{
	return (this->_firstShot);
}

EntityList			*Map::getFirstEnemy(void) const
{
	return (this->_firstEnemy);
}

Player				*Map::getPlayer(void) const
{
	return (this->_player);
}

int					Map::getInput(void) const
{
	int		c = getch();
	flushinp();
	return (c);
}

int					Map::getTotalEnemy(void) const
{
	return (this->_totalEnemy);
}

bool				Map::getBossPhase(void) const
{
	return (this->_bossPhase);
}

void				Map::checkColisions(void)
{
	// Check player vs enemies
	EntityList *current_enemy = this->_firstEnemy;
	while (current_enemy)
	{
		if ((current_enemy->content->getPosx() == this->_player->getPosx()) && (current_enemy->content->getPosy() == this->_player->getPosy())) {
			this->_player->setLives(this->_player->getLives() - 1);
			this->deleteEnemy(current_enemy->content);
		}
		current_enemy = current_enemy->next;
	}
	// Check any shot vs any enemy
	EntityList *current_shot = this->_firstShot;
	EntityList *save_next_shot;
	EntityList *save_next_enemy;
	EntityList *current_boss;
	bool enemy_destroyed = false;
	while (current_shot)
	{
		current_enemy = this->getFirstEnemy();
		save_next_shot = current_shot->next;

		while (current_enemy)
		{
			save_next_enemy = current_enemy->next;
			if ((current_enemy->content->getPosx() == current_shot->content->getPosx()) && (current_enemy->content->getPosy() == current_shot->content->getPosy()))
			{
				if (current_shot->content->getColor() == FT_YELLOW)
				{
					this->_player->setScore(this->_player->getScore() + 1);
					this->deleteEnemy(current_enemy->content);
					enemy_destroyed = true;
				}
			}
			current_enemy = save_next_enemy;
		}
		// Check any shot vs our position
		if ((current_shot->content->getPosx() == this->_player->getPosx()) && (current_shot->content->getPosy() == this->_player->getPosy())) {
			this->_player->setLives(this->_player->getLives() - 1);
			//this->deleteShot(current_shot->content);
		}
		// Check any shot vs boss position
		current_boss = this->_boss;
		while(current_boss)
		{
			if ((current_shot->content->getPosx() == current_boss->content->getPosx()) && (current_shot->content->getPosy() == current_boss->content->getPosy())) 
			{
				current_boss->content->setGlobalLives(current_boss->content->getGlobalLives() - 1);
				enemy_destroyed = true;
			}
			current_boss = current_boss->next;
		}
		if (this->_boss)
		{
			APhysicalEntity *to_del;
			if(this->_boss->content->isAlive() == false)
			{
				this->_player->setScore(this->_player->getScore() + BOSS_SCORE + (this->_player->getScore() / 5));
				this->_bossPhase = false;
				this->_boss->content->setGlobalLives(this->_player->getScore() * 2);
				this->_boss->content->setPhase(0);
				current_boss = this->_boss;
				while (current_boss)
				{
					to_del = current_boss->content;
					current_boss = current_boss->next;
					this->deleteBoss(to_del);
				}
			}
		}

		if (enemy_destroyed == true)
		{
			this->deleteShot(current_shot->content);
			enemy_destroyed = false;
		}
		current_shot = save_next_shot;
		enemy_destroyed = false;
	}
	// Check any asteroid vs our position
	EntityList *current_asteroid = this->_firstAsteroid;
	while (current_asteroid)
	{
		if ((current_asteroid->content->getPosx() == this->_player->getPosx()) && (current_asteroid->content->getPosy() == this->_player->getPosy())) {
			this->_player->setLives(0);
			this->deleteAsteroid(current_asteroid->content);
		}
		current_asteroid = current_asteroid->next;
	}
	// Check any Boss vs our position
	current_boss = this->_boss;
	while (current_boss)
	{
		if ((current_boss->content->getPosx() == this->_player->getPosx()) && (current_boss->content->getPosy() == this->_player->getPosy())) {
			this->_player->setLives(0);
		}
		current_boss = current_boss->next;
	}
	// Check any asteroid vs enemy + shots
	current_asteroid = this->_firstAsteroid;
	while (current_asteroid)
	{
		current_enemy = this->getFirstEnemy();

		while (current_enemy)
		{
			save_next_enemy = current_enemy->next;
			if ((current_enemy->content->getPosx() == current_asteroid->content->getPosx()) && (current_enemy->content->getPosy() == current_asteroid->content->getPosy()))
			{
				this->deleteEnemy(current_enemy->content);
			}
			current_enemy = save_next_enemy;
		}

		current_shot = this->getFirstShot();

		while (current_shot)
		{
			save_next_shot = current_shot->next;
			if ((current_shot->content->getPosx() == current_asteroid->content->getPosx()) && (current_shot->content->getPosy() == current_asteroid->content->getPosy()))
			{
				this->deleteShot(current_shot->content);
			}
			current_shot = save_next_shot;
		}
		current_asteroid = current_asteroid->next;
	}
}

void				Map::createAsteroid( void ) {
	int				randPt;
	srand(time(NULL));

	randPt = rand() % (FT_LINES - 3);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(this->_firstAsteroid))
			{
				this->_firstAsteroid = new EntityList(new Asteroid(randPt, COLUMNS, '*'));
			} else {
				EntityList	*tmp = new EntityList(new Asteroid(randPt + j, COLUMNS - i, '*'));
				tmp->next = this->_firstAsteroid;
				this->_firstAsteroid = tmp;
			}
		}
	}
}

void				Map::updateAsteroid( void ) {
	EntityList		*current = this->_firstAsteroid;

	while (current)
	{
		current->content->display();
		if ((current->content->getPosy() >= COLUMNS) || current->content->getPosy() <= 0)
			this->deleteAsteroid(current->content);
		current = current->next;
	}
}

void				Map::deleteAsteroid(APhysicalEntity *to_del)
{
	EntityList *next;
	EntityList *current;
	if (this->_firstAsteroid->content == to_del)
	{
		next = this->_firstAsteroid->next;
		move(this->_firstAsteroid->content->getPosx(), this->_firstAsteroid->content->getPosy());
		addch(' ');
		delete this->_firstAsteroid->content;
		delete this->_firstAsteroid;
		this->_firstAsteroid = next;
		return ;
	}

	current = this->_firstAsteroid;
	while (current->next->content != to_del)
		current = current->next;
	next = current->next->next;
	move(current->next->content->getPosx(), current->next->content->getPosy());
	addch(' ');
	delete current->next->content;
	delete current->next;
	current->next = next;
}

void				Map::createEnemy(void)
{
	if (!(this->_firstEnemy))
	{
		this->_firstEnemy = new EntityList(new Monster);
		return ;
	}
	EntityList *tmp;
	Monster	*tmpMonster = new Monster;
	tmp = new EntityList(tmpMonster);
	tmp->next = this->getFirstEnemy();
	this->_firstEnemy = tmp;
	this->_totalEnemy++;
	this->addShot(tmpMonster->shoot());
}

// Attention on part du principe to_Del est dans la liste
void				Map::deleteEnemy(APhysicalEntity *to_del)
{
	this->_totalEnemy--;
	EntityList *next;
	EntityList *current;
	if (this->_firstEnemy->content == to_del)
	{
		next = this->getFirstEnemy()->next;
		move(getFirstEnemy()->content->getPosx(), getFirstEnemy()->content->getPosy());
		addch(' ');
		delete this->getFirstEnemy()->content;
		delete this->getFirstEnemy();
		this->_firstEnemy = next;
		return ;
	}

	current = this->getFirstEnemy();
	while (current->next->content != to_del)
		current = current->next;
	next = current->next->next;
	move(current->next->content->getPosx(), current->next->content->getPosy());
	addch(' ');
	delete current->next->content;
	delete current->next;
	current->next = next;

}

void				Map::addShot(EntityList *shot)
{
	if (!(shot))
		return ;

	if (!(this->_firstShot))
	{
		this->_firstShot = shot;
		return ;
	}
	shot->next = this->getFirstShot();
	this->_firstShot = shot;
}

void				Map::deleteShot(APhysicalEntity *to_del)
{
	EntityList *next;
	EntityList *current;
	if (this->_firstShot->content == to_del)
	{
		next = this->getFirstShot()->next;
		move(getFirstShot()->content->getPosx(), getFirstShot()->content->getPosy());
		addch(' ');
		delete this->getFirstShot()->content;
		delete this->getFirstShot();
		this->_firstShot = next;
		return ;
	}

	current = this->getFirstShot();
	while (current->next->content != to_del)
		current = current->next;
	next = current->next->next;
	move(current->next->content->getPosx(), current->next->content->getPosy());
	addch(' ');
	delete current->next->content;
	delete current->next;
	current->next = next;
}


void				Map::updateShot(EntityList *current)
{
	while (current)
	{
		current->content->display();
		if ((current->content->getPosy() >= COLUMNS) || current->content->getPosy() <= 0)
			this->deleteShot(current->content);
		current = current->next;
	}
}

void				Map::updateEnemy(EntityList *current)
{
	while (current)
	{
		current->content->display();
		if (current->content->getPosy() <= 0)
			this->deleteEnemy(current->content);
		current = current->next;
	}
}

void				Map::createBoss(void)
{
	APhysicalEntity *to_del;
	EntityList *tmp = this->getFirstEnemy();
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteEnemy(to_del);
	}
	tmp = this->getFirstShot();
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteShot(to_del);
	}
	this->_bossPhase = true;
	this->_boss = new EntityList(new Boss((FT_LINES / 2) - 2, COLUMNS - 5, FT_WEST, FT_RED, '='));

	tmp = new EntityList(new Boss((FT_LINES / 2) - 2, COLUMNS - 4, FT_WEST, FT_RED, '='));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 2, COLUMNS - 3, FT_WEST, FT_RED, 'A'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 1, COLUMNS - 4, FT_WEST, FT_RED, '/'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 1, COLUMNS - 3, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 1, COLUMNS - 2, FT_WEST, FT_RED, '\\'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 0, COLUMNS - 5, FT_WEST, FT_RED, '/'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 0, COLUMNS - 4, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 0, COLUMNS - 3, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 0, COLUMNS - 2, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) - 0, COLUMNS - 1, FT_WEST, FT_RED, '\\'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 1, COLUMNS - 5, FT_WEST, FT_RED, '\\'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 1, COLUMNS - 4, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 1, COLUMNS - 3, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 1, COLUMNS - 2, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 1, COLUMNS - 1, FT_WEST, FT_RED, '/'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 2, COLUMNS - 4, FT_WEST, FT_RED, '\\'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 2, COLUMNS - 3, FT_WEST, FT_RED, '*'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 2, COLUMNS - 2, FT_WEST, FT_RED, '/'));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 3, COLUMNS - 5, FT_WEST, FT_RED, '='));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 3, COLUMNS - 4, FT_WEST, FT_RED, '='));
	tmp->next = this->_boss;
	this->_boss = tmp;
	tmp = new EntityList(new Boss((FT_LINES / 2) + 3, COLUMNS - 3, FT_WEST, FT_RED, 'V'));
	tmp->next = this->_boss;
	this->_boss = tmp;

}

void				Map::displayBoss(void)
{
	EntityList *tmp = this->_boss;
	Boss		*boss;
	while (tmp)
	{
		tmp->content->erase();
		tmp = tmp->next;
	}
	tmp = this->_boss;
	while (tmp)
	{
		tmp->content->display();
		boss = static_cast<Boss*>(tmp->content);
		this->addShot(boss->shoot());
		tmp = tmp->next;
	}
}

void				Map::deleteBoss(APhysicalEntity *to_del)
{
	EntityList *next;
	EntityList *current;
	if (this->_boss->content == to_del)
	{
		next = this->_boss->next;
		move(this->_boss->content->getPosx(), this->_boss->content->getPosy());
		addch(' ');
		delete this->_boss->content;
		delete this->_boss;
		this->_boss = next;
		return ;
	}

	current = this->_boss;
	while (current->next->content != to_del)
		current = current->next;
	next = current->next->next;
	move(current->next->content->getPosx(), current->next->content->getPosy());
	addch(' ');
	delete current->next->content;
	delete current->next;
	current->next = next;
}

void				Map::deleteMap(void)
{
	APhysicalEntity *to_del;
	// delete remaining enemy
	EntityList *tmp = this->getFirstEnemy();
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteEnemy(to_del);
	}

	// delete remaining shots
	tmp = this->getFirstShot();
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteShot(to_del);
	}


	// delete remaining asteroids
	tmp = this->_firstAsteroid;
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteAsteroid(to_del);
	}

	// delete remaining boss
	tmp = this->_boss;
	while (tmp)
	{
		to_del = tmp->content;
		tmp = tmp->next;
		this->deleteBoss(to_del);
	}
	//delete player
	delete this->_player;

	// delete map
	delete this;
}
