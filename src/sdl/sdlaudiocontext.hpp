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

#ifndef SDL_AUDIO_CONTEXT_INCLUDED_HPP
#define SDL_AUDIO_CONTEXT_INCLUDED_HPP

#include "../iaudiocontext.hpp"
#include <vector>
#include <SDL2/SDL.h>

class SDLAudioContext : public IAudioContext
{
public:
	SDLAudioContext();
	virtual ~SDLAudioContext();

	virtual void PlayAudio(AudioObject& ao);
	virtual void PauseAudio(AudioObject& ao);
	virtual void StopAudio(AudioObject& ao);

	void GenerateSamples(Uint8* stream, int streamLen);
private:
	SDL_AudioDeviceID         m_device;
	std::vector<float>        m_stream;
	std::vector<AudioObject*> m_playingAudio;

	bool RemoveAudio(AudioObject& ao);

	// 복사생성자와 대입생성자를 private 메소드로 지정함으로써
	// 자원 중복 해제 문제와 하나의 오디오 장치를 
	// 여러 객체가 소유한다는 것의 의미의 모호함을 없애기 위함
	SDLAudioContext(const SDLAudioContext& other) {(void)other;}
	void operator=(const SDLAudioContext& other) {(void)other;}
};

#endif
