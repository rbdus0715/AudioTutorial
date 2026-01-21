/*
 * Copyright (c) 2015, Benny Bobaganoosh
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED ANDON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <SDL2/SDL.h>

#include "iaudiodevice.hpp"
#include "iaudiocontext.hpp"
#include "audioobject.hpp"

#include "sdl/sdlaudiodevice.hpp"
#include "sdl/sdlaudiocontext.hpp"

#define FILE_PATH "./res/audio/testClip.wav"

struct AudioData {
	Uint8* pos;
	Uint32 length;
};

void MyAudioCallBack(void* userdata, Uint8* stream, int streamLength)
{
	AudioData* audio = (AudioData*)userdata;

	if(audio->length == 0)
	{
		return;
	}

	Uint32 length = (Uint32)streamLength;
	// 하한선
	length = (length > audio->length ? audio->length : length);
	
	// stream에 오디오에 포지션 정보를 카피
	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;

	if(SDL_LoadWAV(FILE_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		std::cerr << "Error : " << FILE_PATH << " could not be loaded as an audio file" << std::endl;
		SDL_Quit();
		return 1;
	}

	AudioData audio;
	audio.pos = wavStart;
	audio.length = wavLength;

	wavSpec.callback = MyAudioCallBack;
	wavSpec.userdata = &audio;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if(device == 0) {
		std::cerr << "Error : " << SDL_GetError() << std::endl;
		SDL_FreeWAV(wavStart);
		SDL_Quit();
		return 1;
	}

	SDL_PauseAudioDevice(device, 0);
	while(audio.length > 0)
	{
		SDL_Delay(100);
	}

	SDL_CloseAudioDevice(device);
	SDL_FreeWAV(wavStart);
	SDL_Quit();
	return 0;
}
