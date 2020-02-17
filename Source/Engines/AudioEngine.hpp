#ifndef AudioEngine_hpp
#define AudioEngine_hpp
#include <vector>

class Scene;
class AudioComponent;

class AudioEngine
{
private:
	static AudioEngine* instance;
	std::vector<AudioComponent*> m_pAudioTarget;
public:
	AudioEngine();
	~AudioEngine();
	static AudioEngine* Instance();
	void RegisterAudioTarget(AudioComponent* aItem);

};

#endif /* AudioEngine_hpp */
