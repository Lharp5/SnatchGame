///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
 
//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
 
 
///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
///////////////////////////////////////////////////////////////////////////////
class SoundClass
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();
	bool Initialize(HWND);
	void Shutdown();
 
	bool PlayWaveFile();
	void PlayDesiredFile(int, bool);
	void StopDesiredFile(int);

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
 
 
private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

	// Sound buffers for play back
	IDirectSoundBuffer8* stealthSong;
	IDirectSoundBuffer8* chaseSong;
	IDirectSoundBuffer8* doorOpen;
	IDirectSoundBuffer8* doorOpenSlam;
	IDirectSoundBuffer8* footstep;
	IDirectSoundBuffer8* unlockDoor;
	IDirectSoundBuffer8* lightsOn;
	IDirectSoundBuffer8* lightsOff;
};
 
#endif