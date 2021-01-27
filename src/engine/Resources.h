#pragma once

#include "renderer/OpenGL/Shader.h"
#include "renderer/OpenGL/Texture.h"
#include "AL/al.h"
#include <string>

namespace engine
{

	/*
		Singleton
	*/
	class Resources
	{
	private:
		//Singleton Stuff
		Resources(){}
		Resources(Resources const&) = delete;
		void operator = (Resources const&) = delete;
	public:
		static Resources& getInstance() { static Resources instance; return instance; }
		//Class stuff

		static gl::Shader* GetShader(const char* name);
		static gl::Texture* GetTexture(const char* name);
		static ALuint GetSound(const char* name);

		static void LoadShader(const char* name, const char* path, int count = 1);
		static void LoadTexture(const char* name, const char* path, int count = 1);
		static void LoadSound(const char* name, const char* path);
		static void Clear();

	private:
		
		gl::Shader* IGetShader(const char* name);
		gl::Texture* IGetTexture(const char* name);
		ALuint IGetSound(const char* name);
		void IClear();
		void ILoadShader(const char* name, const char* path, int count);
		void ILoadTexture(const char* name, const char* path, int count);
		void ILoadSound(const char* name, const char* path);
		std::vector<std::pair<std::string, gl::Shader*>> shaders_list;
		std::vector<std::pair<std::string, gl::Texture*>> texture_list;
		std::vector<std::pair<std::string, ALuint>> sound_list;
	};
}