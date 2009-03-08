/*
 * Enemy.h
 *
 *  Created on: 18-Feb-2009
 *      Author: Keunhong Park
 */

#ifndef ENEMY_H_
#define ENEMY_H_


/*
 * Enemy class
 * 	- A child class of Entity.
 * 	- This implements the Enemy as an Entity
 *  - You must use "this->" when accessing parent class data members
 */
template<class T>
class Enemy : public Entity<T>{

	Uint shield;
	Uint health;
	Uint points;

public:
	Enemy(
			World<T>	*_world,
			SDL_Surface *_sprite,
			T			_min_speed,
			T 			_max_speed,
			T			_acceleration,
			bool 		can_shoot,
			T			_x_offset,
			T			_y_offset
			)
	{
		// [ these are in the parent object
			// ! this-> is needed to access the private parent object data items
				this->set_world( _world );
				this->set_x_offset( T(_x_offset) );
				this->set_y_offset( T(_y_offset) );
				this->set_min_speed( _min_speed );
				this->set_max_speed( _max_speed );
				this->set_acceleration( _acceleration );
				this->set_sprite( _sprite );
		// these are in the parent object ]
		points = 0;
	}
};

#endif /* ENEMY_H_ */
