
#ifndef _AUDIOENGINE_H_
#define _AUDIOENGINE_H_

#include <string>
#include <SDL/SDL_mixer.h>
#include <map>
namespace Feintgine
{
	class SoundEffect
	{
	public:
		friend class AudioEngine;
		SoundEffect()
		{
			
		}
		void play(int loop = 0); // plays sound , default for no loop ( int ) 

		void playInChannel(int loop, int channel);
		void stahp(); // stahp the sound :))

	private:


		Mix_Chunk * m_chunk = nullptr; // a chunk is require for sound effect
	};

	class Music
	{
	public:
		friend class AudioEngine;
		Music()
		{
			
		}
		void play(int loop = 1); // play music , default is 1 , -1 for infinity loop
		static void pause(); // pause the music 
		static void resume(); // resume from the pause
		static void stahp(); // stahp the music :))
	private:

		Mix_Music * m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();
		void init(); // init , require before playing any sound or music 
		void destroy(); // like destructor
		SoundEffect loadSoundEffect(const std::string  & filePath); // load sound effect as a chunk 
		Music loadMusic(const std::string & filePathj); // load music 
		static AudioEngine * getInstance()
		{
			if (p_Instance == 0)
			{
				p_Instance = new AudioEngine;
				return p_Instance;
			}
			return p_Instance;
		}
	private:
		bool m_isInitialized = false;
		std::map <std::string, Mix_Chunk * > m_soundEffectMap;
		std::map <std::string, Mix_Music * > m_musicMap;
		static AudioEngine * p_Instance ;
	};
}

#endif
