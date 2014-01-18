#ifndef letter_sounds_h
#define letter_sounds_h

#include <map>
#include <SFML/Audio.hpp>

using namespace sf;

class LetterSounds {
		public:
				static void play(char letter) {
						snd.setBuffer(sounds[letter]);
						snd.play();
				}
		protected:
				typedef std::map<char,SoundBuffer> SoundMap;
				static void make_buffer(char i,SoundBuffer& b) {
						std::string filename = "x.ogg";
						filename[0] = i;
						b.loadFromFile("letters/"+filename);
				}
				static SoundMap init_map() {
						SoundMap map;
						for (char i='a';i<='z';++i) {
								SoundBuffer b;
								make_buffer(i,b);
								map[i] = b;  
						}
						for (char i='0';i<='9';++i) {
								SoundBuffer b;
								make_buffer(i,b);
								map[i] = b;  
						}
						return map;
				}
				static SoundMap sounds;
				static Sound snd;
};
#endif
