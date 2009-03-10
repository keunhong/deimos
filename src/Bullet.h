/*********************************************
*** BULLET CLASS
*** implements the bullets
*** heavily depends on the Player class
*********************************************/


#ifndef BULLET_H_
#define BULLET_H_

/*
 * Bullet class
 * 	- A child class of Entity.
 * 	- This implements Bullets as an Entities
 *  - You must use "this->" when accessing parent class data members
 */
template<class T>
class Bullet : public Entity<T>{
	const Entity<T>	*owner;
	int 			power;
	float			angle;

public:
	Bullet(
			World<T>		*_world,
			const Entity<T> *_owner,
			T	 			_min_speed,
			T				_max_speed,
			T 				_acceleration,
			int				_power,
			T				_x_offset,
			T	 			_y_offset,
			float			_angle,
			SDL_Surface		*_sprite
	)
	{
		// [ these are in the parent object
			// ! this-> is needed to access the private parent object data items
			this->set_world( _world );
			this->set_x_offset( _x_offset );
			this->set_y_offset( _y_offset );
			this->set_min_speed( _min_speed );
			this->set_max_speed( _max_speed );
			this->set_acceleration( _acceleration );
			this->set_collision_box(); // MUST come after sprite is defined or game will crash
		// these are in the parent object ]

		owner			= _owner;
		power			= _power;
		angle 			= _angle;

	}
	~Bullet(){}

	float get_angle() const{ return angle; }

	void move(){
		this->set_x_offset( int( this->get_x_offset() + this->get_max_speed() * cos( this->get_angle() ) ) );
		this->set_y_offset( int( this->get_y_offset() + T(this->get_max_speed() * sin( this->get_angle() )) ) );
	}
};
/********************************************/
#endif /* BULLET_H_ */
