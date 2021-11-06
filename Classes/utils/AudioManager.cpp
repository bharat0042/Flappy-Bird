#include "AudioManager.h"

bool AudioManager::soundEnabled{ true };

void AudioManager::muteSounds()
{
	soundEnabled = false;
	cocos2d::AudioEngine::pauseAll();
}

void AudioManager::unmuteSounds()
{
	soundEnabled = true;
	cocos2d::AudioEngine::resumeAll();
}

void AudioManager::playBackgroundMusic(const std::string& filePath, bool loop, float volume)
{
	cocos2d::AudioEngine::play2d(filePath, loop, volume);
}

void AudioManager::playSoundEffect(const std::string& filePath, float volume)
{
	if (soundEnabled)
	{
		cocos2d::AudioEngine::play2d(filePath, false, volume);
	}
}

void AudioManager::pause()
{
	cocos2d::AudioEngine::pauseAll();
}

void AudioManager::resume()
{
	cocos2d::AudioEngine::resumeAll();
}

void AudioManager::end()
{
	cocos2d::AudioEngine::end();
}