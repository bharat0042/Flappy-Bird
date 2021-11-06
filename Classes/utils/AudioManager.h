#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class AudioManager
{
private:
	static bool soundEnabled;

	AudioManager() {};
public:
	static bool getSoundState() { return soundEnabled; };
	static void muteSounds();
	static void unmuteSounds();
	static void playBackgroundMusic(const std::string& filePath, bool loop = true, float volume = 1.0);
	static void playSoundEffect(const std::string& filePath, float volume = 1.0);
	static void pause();
	static void resume();
	static void end();
};

#endif // _AUDIO_MANAGER_H_
