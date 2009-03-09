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
			World<float>	*_world,
			Sprite		*_sprite,
			int			_min_speed,
			int 			_max_speed,
			int			_acceleration,
			bool 		can_shoot,
			int			_x_offset,
			int			_y_offset
			)
	{
		// [ these are in the parent object
			// ! this-> is needed to access the private parent object data items
				this->set_world( _world );
				this->set_x_offset( int(_x_offset) );
				this->set_y_offset( int(_y_offset) );
				this->set_min_speed( _min_speed );
				this->set_max_speed( _max_speed );
				this->set_acceleration( _acceleration );
				this->set_sprite( _sprite );
				this->set_collision_box(); // MUST come after sprite is defined or game will crash
		// these are in the parent object ]

		points = 0;
	}
};

#endif /* ENEMY_H_ */
