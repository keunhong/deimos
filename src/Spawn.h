/*
 * Spawn.h
 *
 *  Created on: 03-Mar-2009
 *      Author: Keunhong Park
 */

#ifndef SPAWN_H_
#define SPAWN_H_

// [ class prototypes
	template<class T>
	class Bullet;
	template<class T>
	class Entity;
	template<class T>
	class Player;
	template<class T>
	class Enemy;
// class prototype ]

/*
 * Spawn class
 * 	- A static class for spawning thing
 * 		ex. Player, Enemy, Bullet, Boss
 *  - This is a static class. DO NOT ADD DATA MEMBERS.
 */
template<class T>
class Spawn{
	public:
		// spawn bullet
		static Bullet<T> * bullet(
				World<T>	*_world,
				const Entity<T> *_owner,
				T 				_min_speed,
				T				_max_speed,
				T				_acceleration,
				int 			_power,
				T				_x_offset,
				T				_y_offset,
				float 			_angle,
				SDL_Surface		*_sprite
		)
		{
			//T _x_offset, T _y_offset, T _speed, T _acceleration, T _power, float _angle, SDL_Surface *_sprite
			Bullet<T> *new_bullet = new Bullet<T>(
					_world ,
					_owner,
					_min_speed,
					_max_speed,
					_acceleration,
					_power,
					_x_offset,
					_y_offset,
					_angle,
					_sprite
			);
			return new_bullet;
		}

		// spawn player
		// max_speed, acceleration, bullet speed, bullet power, bullet delay, bullet_sprite
		static Player<T> * player
		(
				World<T>	*_world,
				SDL_Surface *_sprite,
				T			_min_speed,
				T 			_max_speed,
				T			_acceleration,
				T 			_x_offset,
				T			_y_offset,
				SDL_Surface *_bullet_sprite,
				T			_bullet_speed,
				int			_bullet_power,
				Uint 		_bullet_delay
		)
		{
			Player<T> *new_player = new Player<T>(_world, _sprite, _min_speed, _max_speed, _acceleration, _x_offset, _y_offset, _bullet_sprite, _bullet_speed, _bullet_power, _bullet_delay );
			return new_player;
		}

		// spawn enemy
		static Enemy<T> * enemy(
				SDL_Surface *sprite,
				T 			spawn_x_offset,
				T			spawn_y_offset,
				bool 		can_shoot
		)
		{
			Enemy<T> *new_enemy = new Enemy<T>(sprite , 5, can_shoot, spawn_x_offset, spawn_y_offset);
			return new_enemy;
		}

		// spawn boss
		static void boss(){ }
};

#endif /* SPAWN_H_ */
