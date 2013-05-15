#pragma once
#include <allegro5/allegro_audio.h>
class AudioManager
{
public:
	AudioManager(void);
	~AudioManager(void);

	static AudioManager& GetInstance();
	void Update();

	void Init();

	void PlaySoundEffect(int soundNum);
	void PlaySong(int songNum);
	void StopSong();
	void PauseSong();
	void ToggleMusic() {if(musicEnabled){musicEnabled=false;} else {musicEnabled=true;}}
	void ToggleSoundFX() {if(soundFXEnabled){soundFXEnabled=false;} else {soundFXEnabled=true;}}

	void ChangeMusicVolume();
	void ChangeSoundFXVolume();

	bool GetMusicEnabled()		{return musicEnabled;}
	bool GetSoundFXEnabled()	{return soundFXEnabled;}

	float GetMusicVolume()		{return musicVolume;}
	float GetSoundFXVolume()	{return soundFXVolume;}

private:
	ALLEGRO_AUDIO_STREAM *song;
	ALLEGRO_MIXER *mixer;
	ALLEGRO_VOICE *voice;

	ALLEGRO_SAMPLE *snd_click;
	ALLEGRO_SAMPLE *snd_bubble1;
	ALLEGRO_SAMPLE *snd_bubble2;
	ALLEGRO_SAMPLE *snd_bubble3;

	bool paused;
	
	bool musicEnabled;
	bool soundFXEnabled;

	float musicVolume;
	float soundFXVolume;
};

