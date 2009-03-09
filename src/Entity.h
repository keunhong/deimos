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
	World<T> 	*world;
	int 		x_offset;
	int 		y_offset;
	int 		min_speed;
	int 		max_speed;
	int 		acceleration;
	Sprite 		*sprite;
	SDL_Rect 	*collision_box;

public:
	World<T> * get_world() const{ return world; }
	int get_x_offset() const{ return x_offset; }
	int get_y_offset() const{ return y_offset; }
	int get_min_speed() const{ return min_speed; }
	int get_max_speed()  const{ return max_speed; }
	int get_acceleration() const{ return acceleration; }
	int get_sprite() const{ return sprite; }
	Uint get_width() const{ return sprite->surface->w; }
	Uint get_height() const{ return sprite->surface->h; }
	SDL_Rect * get_collision_box() const{ return collision_box; }

	void set_world(World<T> *_world){ world = _world; }
	void set_x_offset(int _x_offset){ x_offset = _x_offset; }
	void set_y_offset(int _y_offset){ y_offset = _y_offset; }
	void set_min_speed(int _min_speed){ min_speed = _min_speed; }
	void set_max_speed(int _max_speed){ max_speed = _max_speed; }
	void set_acceleration(int _acceleration){ acceleration = _acceleration; }
	void set_sprite( Sprite *_sprite ){ sprite = _sprite; }
	void update_sprite( int _x_offset = -1, int _y_offset = -1, std::string _file = "" ){
		if(_x_offset != -1){
			sprite->x_offset = _x_offset;
		}
		if(_y_offset != -1){
			sprite->y_offset = _y_offset;
		}
		if(_file != ""){
			SDL_FreeSurface( sprite->surface );

			sprite->file = _file;
			sprite->surface = SDL::load_image(_file);
		}
	}

	void set_collision_box(){
		collision_box = new SDL_Rect;
		collision_box->x = Sint16(x_offset);
		collision_box->y = Sint16(y_offset);
		collision_box->w = get_width();
		collision_box->h = get_height();
	}

	bool check_collision(Entity<T> *other){
		this->set_collision_box();
		other->set_collision_box();

		int this_north 	= this->get_collision_box()->y;
		int this_south	= this->get_collision_box()->y + this->get_collision_box()->h;
		int this_east	= this->get_collision_box()->x + this->get_collision_box()->w;
		int this_west 	= this->get_collision_box()->x;

		int other_north = other->get_collision_box()->y;
		int other_south	= other->get_collision_box()->y + other->get_collision_box()->h;
		int other_east	= other->get_collision_box()->x + other->get_collision_box()->w;
		int other_west 	= other->get_collision_box()->x;

		return ( this_north >= other_south ||
				this_south <= other_north ||
				this_east <= other_west ||
				this_west >= other_east )? false : true ;
	}
};

#endif /* ENTITY_H_ */
