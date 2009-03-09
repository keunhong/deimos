/*
 * SoundEngine.h
 *
 *  Created on: Mar 9, 2009
 *      Author: K
 */

#ifndef SOUND_H_
#define SOUND_H_

template<class T>
class SoundEngine : public Engine<T>{
	bool muted_status;

	Mix_Music *bg_music;
	Mix_Chunk *shoot_sound;

	public:
		SoundEngine(std::string bg_music_file, std::string shoot_sound_file){
			Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

			// create bg_music and set pointer to
			Mix_Music *new_bg_music = NULL;
			new_bg_music = Mix_LoadMUS( bg_music_file.c_str() );
			bg_music = new_bg_music;

			// shoot sound effect
			Mix_Chunk *new_shoot_sound = NULL;
			new_shoot_sound = Mix_LoadWAV( shoot_sound_file.c_str() );
			shoot_sound = new_shoot_sound;

			muted_status = false;
		}

		void set_muted_status(bool status){
			if(status == true){
				muted_status = true;

			}
		}
		bool get_muted_status() const{ return muted_status; }

		void play_bg_music(){
			Mix_PlayMusic( bg_music, -1 );
		}
		void play_shoot_sound(){
			Mix_PlayChannel( -1, shoot_sound, 0 );
		}
};

#endif /* SOUND_H_ */
