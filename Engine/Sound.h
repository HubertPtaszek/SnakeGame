#pragma once
#include "ChiliWin.h"
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "ChiliException.h"
#include <wrl\client.h>

using namespace std;

// forward declare WAVEFORMATEX so we don't have to include kbullshit headers
struct tWAVEFORMATEX;
typedef tWAVEFORMATEX WAVEFORMATEX;

class SoundSystem
{
	class XAudioDll
	{
		HMODULE hModule = 0;
		static constexpr wchar_t* systemPath = L"XAudio2_7.dll";
#ifdef _M_X64
		static constexpr wchar_t* folderPath = L"XAudio\\XAudio2_7_64.dll";
		static constexpr wchar_t* localPath = L"XAudio2_7_64.dll";
#else
		static constexpr wchar_t* folderPath = L"XAudio\\XAudio2_7_32.dll";
		static constexpr wchar_t* localPath = L"XAudio2_7_32.dll";
#endif
		enum class LoadType
		{
			Folder,
			Local,
			System,
			Invalid
		};
		static const wchar_t* GetDllPath(LoadType type);
	public:
		XAudioDll();
		~XAudioDll();
		operator HMODULE() const;
	};
public:
	class APIException : public ChiliException
	{
		HRESULT hr;
	public:
		APIException(HRESULT hr, const wchar_t * file, unsigned int line, const std::wstring& note);
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	};
	class FileException : public ChiliException
	{
		wstring filename;
	public:
		FileException(const wchar_t* file, unsigned int line, const std::wstring& note, const std::wstring& filename);
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	};
	class Channel
	{
		friend class Sound;
		void RetargetSound(const Sound* pOld, Sound* pNew);
		unique_ptr<struct XAUDIO2_BUFFER> xaBuffer;
		struct IXAudio2SourceVoice* pSource = nullptr;
		class Sound* pSound = nullptr;
	public:
		Channel(SoundSystem& sys);
		Channel(const Channel&) = delete;
		~Channel();
		void PlaySoundBuffer(class Sound& s, float freqMod, float vol);
		void Stop();
	};
	SoundSystem(const SoundSystem&) = delete;
	static SoundSystem& Get();
	static void SetMasterVolume(float vol = 1.0f);
	static const WAVEFORMATEX& GetFormat();
	void PlaySoundBuffer(class Sound& s, float freqMod, float vol);
private:
	SoundSystem();
	void DeactivateChannel(Channel& channel);  // private bo uzywa chaneli zadklarowanych pozniej w public
	XAudioDll xaudio_dll;
	Microsoft::WRL::ComPtr<struct IXAudio2> pEngine;
	struct IXAudio2MasteringVoice* pMaster = nullptr;
	unique_ptr<WAVEFORMATEX> format;
	mutex mutex;
	vector<std::unique_ptr<Channel>> idleChannelPtrs;
	vector<std::unique_ptr<Channel>> activeChannelPtrs;
	// change these values to match the format of the wav files you are loading
	// all wav files must have the same format!! (no mixing and matching)
	static constexpr WORD nChannelsPerSound = 2u;
	static constexpr DWORD nSamplesPerSec = 44100u;
	static constexpr WORD nBitsPerSample = 16u;
	// change this value to increase/decrease the maximum polyphony	
	static constexpr size_t nChannels = 64u;
};

class Sound
{
	friend SoundSystem::Channel;
	UINT32 nBytes = 0u;
	bool looping = false;
	unsigned int loopStart;
	unsigned int loopEnd;
	unique_ptr<BYTE[]> pData;
	mutex mutex;
	condition_variable cvDeath;
	vector<SoundSystem::Channel*> activeChannelPtrs;
	static constexpr unsigned int nullSample = 0xFFFFFFFFu;
	static constexpr float nullSeconds = -1.0f;
public:
	enum class LoopType
	{
		NotLooping,
		AutoEmbeddedCuePoints,
		AutoFullSound,
		ManualFloat,
		ManualSample,
		Invalid
	};
	Sound() = default;
	// for backwards compatibility--2nd parameter false -> NotLooping
	Sound(const wstring& fileName, bool loopingWithAutoCueDetect);
	// do not pass this function Manual LoopTypes!
	Sound(const wstring& fileName, LoopType loopType = LoopType::NotLooping);
	Sound(const wstring& fileName, unsigned int loopStart, unsigned int loopEnd);
	Sound(const wstring& fileName, float loopStart, float loopEnd);
	Sound(Sound&& donor);
	Sound& operator=(Sound&& donor);
	void Play(float freqMod = 1.0f, float vol = 1.0f);
	void StopOne();
	void StopAll();
	~Sound();
private:
	Sound(const std::wstring& fileName, LoopType loopType, unsigned int loopStartSample, unsigned int loopEndSample, float loopStartSeconds, float loopEndSeconds);
};