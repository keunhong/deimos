/*
 * World.h
 *
 *  Created on: Mar 8, 2009
 *      Author: Keunhong Park
 */

#ifndef WORLD_H_
#define WORLD_H_

// [ class prototypes
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
		}

		// destructor
		void delete_bullet(Bullet<T> *_bullet){ delete _bullet; }
		~World(){
			for_each(bullets->begin(), bullets->end(), delete_bullet);
			delete bullets;
		}

		// return pointer to bullets vector
		std::vector< Bullet<T>* > * get_bullets(){
			return bullets;
		}

		// add a bullet to the vector
		void add_bullet(Bullet<T> *_bullet){
			bullets->push_back( _bullet );
		}
};

#endif /* WORLD_H_ */
