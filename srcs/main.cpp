/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:54:39 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 21:35:20 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "Monster.hpp"
#include "Map.hpp"
#include <ncurses.h>

void		handleKeys(Map *map, int c) {
	switch (c) {
		case KEY_UP:
			map->getPlayer()->setDirection(FT_NORTH);
			break ;
		case KEY_LEFT:
			map->getPlayer()->setDirection(FT_EAST);
			break ;
		case KEY_DOWN:
			map->getPlayer()->setDirection(FT_SOUTH);
			break ;
		case KEY_RIGHT:
			map->getPlayer()->setDirection(FT_WEST);
			break ;
		case 32:
			map->addShot(map->getPlayer()->shoot());
			break ;
	}
}

void		one_frame(Map *m, int key, int fc)
{
		handleKeys(m, key);
		if (((fc % 3) == 0) || ((fc % 3 ) == 1))
			m->getPlayer()->display();
		
		if (m->getBossPhase() == true)
			if (((fc % 5) == 0))
				m->displayBoss();
		if (((fc % 4) == 0) || ((fc % 4) == 1) || ((fc % 4) == 2))
			m->updateAsteroid();
		m->updateShot(m->getFirstShot());
		m->checkColisions();

		if ((m->getTotalEnemy() < MAX_ENEMY) && (m->getBossPhase() == false))
			m->createEnemy();
		if (((fc % 3) == 0) || ((fc % 3 ) == 1))
			m->updateEnemy(m->getFirstEnemy());
		m->checkColisions();

		refresh();
}

void		mainLoop(void)
{
	Map		*m = new Map;
	int		sleepingTime;
	int		input;
	int		fc; //frame counter
	int		bc; // boss counter

	sleepingTime = 1000000 / FRAMRATE;
	
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	start_color();
	init_pair(FT_RED, COLOR_RED, COLOR_BLACK);
	init_pair(FT_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(FT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(FT_BLUE, COLOR_BLUE, COLOR_BLACK);

	keypad(stdscr,TRUE);
	m->getPlayer()->display();
	refresh();

	
	fc = 0;
	bc = 0;
	while (m->getPlayer()->isAlive()) {
		fc++;
		if (m->getBossPhase() == true)
			bc = 0;
		bc++;
		input = m->getInput();
		if (input == 27)
			break;
		if ((fc % 200 == 0) && (m->getBossPhase() == false))
			m->createAsteroid();
		if (bc == FRAMRATE * BOSS_APPEAR)
			m->createBoss();
		one_frame(m, input, fc);
		usleep(sleepingTime);
	}

	endwin();
	m->deleteMap();
}


int			main( void )
{
	mainLoop();
	
	return 0;
}
