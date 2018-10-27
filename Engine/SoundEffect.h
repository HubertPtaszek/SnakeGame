#pragma once
#include "Sound.h"
#include <random>
#include <initializer_list>
#include <memory>

using namespace std;

class SoundEffect
{
	uniform_int_distribution<unsigned int> soundDist;
	normal_distribution<float> freqDist;
	vector<Sound> sounds;
public:
	SoundEffect(const initializer_list<wstring>& wavFiles, bool soft_fail = false, float freqStdDevFactor = 0.06f) : freqDist(0.0f, freqStdDevFactor), soundDist(0, unsigned int(wavFiles.size() - 1))
	{
		sounds.reserve(wavFiles.size());
		for (auto& f : wavFiles)
		{
			try
			{
				sounds.emplace_back(f);
			}
			catch (const SoundSystem::FileException& e)
			{
				if (soft_fail)
				{
					sounds.emplace_back();
				}
				else
				{
					throw e;
				}
			}
		}
	}
	template<class T>
	void Play(T& rng, float vol = 1.0f)
	{
		sounds[soundDist(rng)].Play(exp2(freqDist(rng)), vol);
	}
};