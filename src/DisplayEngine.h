/*
 * DisplayEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

template<class T>
struct Text{
	std::string text;
	TTF_Font 	*font;
	SDL_Color	color;
	T 			x_offset;
	T 			y_offset;
};

template<class T>
class DisplayEngine : public Engine<T>{
	std::vector< Text<T>* >	*text;

	public:
		DisplayEngine(){
			text = new std::vector< Text<T>* >;
		}

		void add_text(std::string _text, TTF_Font *_font, SDL_Color _color, T _x_offset, T _y_offset){
			Text<T> *new_text = new Text<T>;
			new_text.text = _text;
			new_text.font = _font;
			new_text.color = _color;
			new_text.x_offset = _x_offset;
			new_text.y_offset = _y_offset;

			text.push_back(new_text);
		}
		std::vector< Text<T>* >	* get_text() const{ return text; }


};

#endif /* DISPLAY_H_ */
