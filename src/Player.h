/*********************************************
*** PLAYER CLASS
*** implements the spaceship
*********************************************/

#ifndef PLAYER_H_
#define PLAYER_H_


// [ class prototypes
	template<class T> class Bullet;
// class prototypes  ]

/*
 * Player class
 * 	- A child class of Entity.
 * 	- This implements the Player as an Entity
 *  - You must use "this->" when accessing parent class data members
 */
template<class T>
class Player : public Entity<T>{
	Uint shield;
	Uint health;
	Uint points;

	// bullet variables
	T bullet_speed;
	Uint bullet_last_shot;
	int bullet_power;
	Uint bullet_width;
	Uint bullet_height;
	Uint bullet_delay;
	Uint bullet_streams;		// number of bullet streams, in addition to the main stream which has to always be there
	SDL_Surface *bullet_sprite;

public:
	Player(
			World<T>	*_world,
			SDL_Surface *_sprite,
			T			_min_speed,
			T 			_max_speed,
			T			_acceleration,
			T			_x_offset,
			T			_y_offset,
			SDL_Surface *_bullet_sprite,
			T 			_bullet_speed,
			int 		_bullet_power,
			Uint		_bullet_delay
	)
	{

		// [ these are in the parent object
			// ! this-> is needed to access the parent object data items
			this->set_world( _world );
			this->set_x_offset( T(_x_offset) );
			this->set_y_offset( T(_y_offset) );
			this->set_min_speed( _min_speed );
			this->set_max_speed( _max_speed );
			this->set_acceleration( _acceleration );
			this->set_sprite( _sprite );
			this->set_collision_box(); // MUST come after sprite is defined or game will crash
		// these are in the parent object ]

		points = 0;

		bullet_power 	= _bullet_power;
		bullet_speed 	= _bullet_speed;
		bullet_delay 	= _bullet_delay;
		bullet_streams 	= 0;
		bullet_sprite 	= _bullet_sprite;

		points = 0;
		health = 100;
		shield = 0;
	}
	~Player(){}

	std::vector< Bullet<T> > bullets; // just make it public for now..

	Uint get_bullet_last_shot() const{ return bullet_last_shot; }
	Uint get_streams() 	const{ return bullet_streams; }
	Uint get_points() 	const{ return points; }
	Uint get_shield() 	const{ return shield; }
	Uint get_health()	const{ return health; }
private:
	void set_bullet_last_shot(){ bullet_last_shot = SDL_GetTicks(); }

public:
	bool can_shoot() const{ return (SDL_GetTicks() - bullet_last_shot > bullet_delay); }
	// shoot a bullet
	void base_shot(float angle){
		set_bullet_last_shot();

		Spawn<T>::bullet(
				this->get_world(),
				this,			// owner
				bullet_speed,	// min_speed (bullets wont accelerate just yet..)
				bullet_speed,	// max_speed
				0,				// acceleration
				10,				// power
				this->get_x_offset() + this->get_width(),						// x_offset
				this->get_y_offset() + this->get_height() / 2 - bullet_sprite->h / 2,	// y_offset
				angle,			// angle
				bullet_sprite	// bullet_sprite
		);

		//Bullet<T> temp_bullet( *this, bullet_speed, 10, angle, bullet_width, bullet_height );
		//bullets.push_back(temp_bullet);
	}

	// sets the amount of bullet streams
	void update_streams(bool action){		// 0 stands for addition, 1 for subtraction
		if(action == 0 && bullet_streams < 47){
			bullet_streams += 2;	// add 2
		}
		if(action == 1 && bullet_streams > 0){
			bullet_streams -=2;			// subtract 2
		}
	}

	void shoot(){
		if(bullet_streams == 0){
			base_shot( 0 );	// simple straight shot
		}
		if(bullet_streams %2 == 0){		// must be even amount of streams
			base_shot( 0 ); 						// base shot is always there
			for(Uint i = 1; i<= bullet_streams/2; i++){
				base_shot( PI/24 * i );		// bullets go up
				base_shot( -PI/24 * i );	// bullets go down
			}
		}
	}

	void move_up(){
		if( this->get_y_offset() >= this->get_max_speed() ){ this->set_y_offset(this->get_y_offset() - this->get_max_speed() ); }
		// handle the difference if it's less than then speed
		else if( this->get_y_offset() < this->get_max_speed() && this->get_y_offset() >= 0 ){ this->set_y_offset(0); }
	}
	void move_down(){
		if( this->get_y_offset() <= (SCREEN_HEIGHT - this->get_height() - this->get_max_speed() ) ){ this->set_y_offset( this->get_y_offset() + this->get_max_speed()) ; }
		// handle the difference if it's less than then speed
		else if( (this->get_y_offset() > (SCREEN_HEIGHT - this->get_height() - this->get_max_speed())) && (this->get_y_offset() <= (SCREEN_HEIGHT - this->get_height() )) ){
			this->set_y_offset( this->get_y_offset() + (SCREEN_HEIGHT - this->get_height() - this->get_y_offset()) );
		}
	}
	void move_left(){
		if(this->get_x_offset() >= this->get_max_speed()){ this->set_x_offset( this->get_x_offset() - this->get_max_speed() ); }
		// handle the difference if it's less than then speed
		else if(this->get_x_offset() < this->get_max_speed() && this->get_x_offset() >= 0){ this->set_x_offset( this->get_x_offset() - this->get_x_offset() ); }
	}
	void move_right(){
		if( this->get_x_offset() <= (SCREEN_WIDTH - this->get_width() - this->get_max_speed()) ){ this->set_x_offset( this->get_x_offset() + this->get_max_speed() ); }
		// handle the difference if it's less than then speed
		else if( (this->get_x_offset() > (SCREEN_WIDTH - this->get_width() - this->get_max_speed())) && (this->get_x_offset() <= (SCREEN_WIDTH - this->get_width() )) ){
			this->set_x_offset( this->get_x_offset() + (SCREEN_WIDTH - this->get_width() - this->get_x_offset()) );
		}
	}
};
/********************************************/

#endif /* PLAYER_H_ */
