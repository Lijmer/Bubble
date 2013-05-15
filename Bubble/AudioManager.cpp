#include "AudioManager.h"
#include <allegro5/allegro_acodec.h>
#include "globals.h"
AudioManager::AudioManager(void)
{
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);
	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	snd_click = al_load_sample("sound/click.wav");
	snd_bubble1 = al_load_sample("sound/bubble1.wav");
	snd_bubble2 = al_load_sample("sound/bubble2.wav");
	snd_bubble3 = al_load_sample("sound/bubble3.wav");
	paused=false;
	musicEnabled=true;
	soundFXEnabled=true;
	musicVolume=1;
	soundFXVolume=1;
}


AudioManager::~AudioManager(void)
{
	al_detach_audio_stream(song);
	al_destroy_audio_stream(song);
	al_detach_mixer(mixer);
	al_destroy_mixer(mixer);
	al_detach_voice(voice);
	al_destroy_voice(voice); 

	al_destroy_sample(snd_click);
	al_destroy_sample(snd_bubble1);
	al_destroy_sample(snd_bubble2);
	al_destroy_sample(snd_bubble3);
	
}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager instance;
	return instance;
}
void AudioManager::Update()
{
	if(musicEnabled && !paused)
		al_set_audio_stream_playing(song, true);
	else if(!musicEnabled || paused)
		al_set_audio_stream_playing(song, false);
	al_set_audio_stream_gain(song, musicVolume);

}

void AudioManager::Init()
{
	
}

void AudioManager::PlaySoundEffect(int soundNum)
{
	if(soundFXEnabled)
	{
		if(soundNum==0)
			al_play_sample(snd_click,soundFXVolume,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
		else if(soundNum==1)
			al_play_sample(snd_bubble1,soundFXVolume,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
		else if(soundNum==2)
			al_play_sample(snd_bubble2,soundFXVolume,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);
		else if(soundNum==3)
			al_play_sample(snd_bubble3,soundFXVolume,0,1,ALLEGRO_PLAYMODE_ONCE,NULL);

	}
}

void AudioManager::PlaySong(int songNum)
{
	if(song!=NULL)
		al_detach_audio_stream(song);
	if(songNum ==0)
		song = al_load_audio_stream("music/fall.ogg", 4, 2048);
	//loop the song
	al_set_audio_stream_loop_secs(song, 0., al_get_audio_stream_length_secs(song));
	al_set_audio_stream_playmode(song, ALLEGRO_PLAYMODE_LOOP);
	al_attach_audio_stream_to_mixer(song, mixer);
	al_attach_mixer_to_voice(mixer,voice);
}
void AudioManager::StopSong()
{
	al_detach_audio_stream(song);	
}

void AudioManager::PauseSong()
{
	if(!paused)
		paused=true;
	else if(paused)
		paused=false;
}

void AudioManager::ChangeMusicVolume()
{
	musicVolume+=0.1;
	if(musicVolume >= 1.1)
		musicVolume=0;
}

void AudioManager::ChangeSoundFXVolume()
{
	soundFXVolume+=0.1;
	if(soundFXVolume >= 1.1)
		soundFXVolume=0;
}