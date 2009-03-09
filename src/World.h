/*
 * World.h
 *
 *  Created on: Mar 8, 2009
 *      Author: Keunhong Park
 */

#ifndef WORLD_H_
#define WORLD_H_

// [ class prototypes
	template<class T> class Spawn;
	template<class T> class Entity;
	template<class T> class Bullet;
	template<class T> class Enemy;
// class prototypes ]

/*
 * World class
 *	- It will contain information and objects that will exist within the world
 *	- Ex: Player, Enemy, Bullet
 *	- Other environment settings will also be set here
 */
template<class T>
class World{
	std::vector< Bullet<T>* >	*bullets;
	std::vector< Enemy<T>* >	*enemies;

	public:
		// constructor
		World(){
			bullets = new std::vector< Bullet<T>* >;
			enemies = new std::vector< Enemy<T>* >;
		}

		// destructor
		void delete_entity(Entity<T> * _entity){ delete _entity; }
		~World(){
			for_each(bullets->begin(), bullets->end(), delete_entity);
			delete bullets;
			for_each(enemies->begin(), enemies->end(), delete_entity);
			delete enemies;
		}

		// return pointer to bullets vector
		std::vector< Bullet<T>* > * get_bullets(){
			return bullets;
		}

		std::vector< Enemy<T>* > * get_enemies(){
			return enemies;
		}

		// add a bullet to the vector
		void add_bullet(Bullet<T> *_bullet){
			bullets->push_back( _bullet );
		}

		void spawn_enemy(SDL_Surface *_sprite){
			Enemy<T>* new_enemy = Spawn<T>::enemy(
					this,
					_sprite,
					10,
					10,
					0,
					0,
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2
			);
			enemies->push_back( new_enemy );
		}
};

#endif /* WORLD_H_ */
