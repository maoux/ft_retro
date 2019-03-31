/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shot.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:18:31 by heynard           #+#    #+#             */
/*   Updated: 2019/03/31 16:06:29 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOT_H
# define SHOT_H

# include "APhysicalEntity.hpp"
# include <ncurses.h>
# include "ft_retro.h"

class	Shot : public APhysicalEntity {

	private:
		
		virtual void		_move( int const, int const );
		int					_color;

	public:

		Shot( void );
		Shot( int, int );
		Shot( int, int, int, int, char);
		Shot( Shot const & );
		virtual ~Shot( void );

		Shot &	operator=( Shot const & );

		virtual void		display( void );
		void				setColor( int );
		virtual int			getColor( void ) const;

};

#endif
