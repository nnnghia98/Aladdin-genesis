#include "Game.h"
#include "Sound.h"
#include <tchar.h>
Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::sound_ThrowApple, Convert(L"Resources/Sound/ThrowApple.wav"));
	AddSound(eSound::sound_AppleCollect, Convert(L"Resources/Sound/AppleCollect.wav"));
	AddSound(eSound::sound_GemCollect, Convert(L"Resources/Sound/GemCollect.wav"));
	AddSound(eSound::sound_HighSword, Convert(L"Resources/Sound/HighSword.wav"));
	AddSound(eSound::sound_ExtraHealth, Convert(L"Resources/Sound/ExtraHealth.wav"));
	AddSound(eSound::sound_GuardHit, Convert(L"Resources/Sound/GuardHit.wav"));
	AddSound(eSound::sound_AppleSplat, Convert(L"Resources/Sound/AppleSplat.wav"));
	AddSound(eSound::sound_Skeleton, Convert(L"Resources/Sound/SKeleton.wav"));
	AddSound(eSound::sound_StoneRumble, Convert(L"Resources/Sound/StoneRumble.wav"));
	AddSound(eSound::sound_BonesTinkle, Convert(L"Resources/Sound/BonesTinkle.wav"));
	AddSound(eSound::sound_AladinPush, Convert(L"Resources/Sound/AladdinPush.wav"));
	AddSound(eSound::sound_GuardBeckon, Convert(L"Resources/Sound/GuardBeckon.wav"));
	AddSound(eSound::sound_Storyline, Convert(L"Resources/Sound/Storyline.wav"));
	AddSound(eSound::sound_Story, Convert(L"Resources/Sound/Story.wav"));
	AddSound(eSound::sound_Wow, Convert(L"Resources/Sound/Wow!.wav"));
	AddSound(eSound::sound_ContinuePoint, Convert(L"Resources/Sound/ContinuePoint.wav"));
	AddSound(eSound::sound_Iiee, Convert(L"Resources/Sound/Iiee.wav"));
	AddSound(eSound::sound_BossTune, Convert(L"Resources/Sound/BossTune.wav"));
	AddSound(eSound::sound_LevelComplete, Convert(L"Resources/Sound/LevelComplete.wav"));
	AddSound(eSound::sound_JafarLaugh, Convert(L"Resources/Sound/JafarLaugh.wav"));
	AddSound(eSound::sound_JafarSnake, Convert(L"Resources/Sound/JafarSnake.wav"));
	AddSound(eSound::sound_AladdinHurt, Convert(L"Resources/Sound/AladdinHurt.wav"));
}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

LPTSTR Sound::Convert(LPCWSTR path)
{
	const wchar_t* c_str = path;
	LPTSTR str = const_cast<LPTSTR>(c_str);
	return str;
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound *wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{
	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(Game::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}