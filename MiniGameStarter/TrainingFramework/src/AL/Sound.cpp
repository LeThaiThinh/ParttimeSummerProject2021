#include "Sound.h"
#include <thread>

Sound::Sound(const std::string& path) {
	m_path = path;
	m_song = SoundBuffer::get()->addSoundEffect(m_path.c_str());
	LOGI("Load sound:%s\t\t", path.c_str());

}
void Sound::PlaySound() {
	//m_soundSource.Play(m_song);
	auto thread = std::thread(&Sound::Play, this);
	thread.detach();
}
void Sound::Play() {
	m_soundSource.Play(m_song);
}
void Sound::PlayLoopSound() {
	//m_soundSource.Play(m_song);
	auto thread = std::thread(&Sound::PlayLoop, this);
	thread.detach();
}
void Sound::PlayLoop() {
	m_soundSource.PlayLoop(m_song);
}
void Sound::Stop() {
	m_soundSource.Stop(m_song);
}