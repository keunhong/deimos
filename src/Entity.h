/*
 * Entity.h
 *
 *  Created on: Mar 7, 2009
 *      Author: Keunhong Park
 */

#ifndef ENTITY_H_
#define ENTITY_H_

/*
 * Entity class
 * 	- A parent class for all sorts of entities.
 * 		ex. Player, Enemy, Bullet
 *  - This is a parent class
 */
template<class T>
class Entity{
	World<T> *world;
	T x_offset;
	T y_offset;
	T min_speed;
	T max_speed;
	T acceleration;
	SDL_Surface *sprite;

public:
	World<T> * get_world() const{ return world; }
	T get_x_offset() const{ return x_offset; }
	T get_y_offset() const{ return y_offset; }
	T get_min_speed() const{ return min_speed; }
	T get_max_speed()  const{ return max_speed; }
	T get_acceleration() const{ return acceleration; }
	T get_sprite() const{ return sprite; }
	Uint get_width() const{ return sprite->w; }
	Uint get_height() const{ return sprite->h; }

	void set_world(World<T> *_world){ world = _world; }
	void set_x_offset(T _x_offset){ x_offset = _x_offset; }
	void set_y_offset(T _y_offset){ y_offset = _y_offset; }
	void set_min_speed(T _min_speed){ min_speed = _min_speed; }
	void set_max_speed(T _max_speed){ max_speed = _max_speed; }
	void set_acceleration(T _acceleration){ acceleration = _acceleration; }
	void set_sprite( SDL_Surface *_sprite ){ sprite = _sprite; }
};

#endif /* ENTITY_H_ */
