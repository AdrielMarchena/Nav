#pragma once

#include "renderer/OpenGL/Shader.h"
#include "renderer/OpenGL/Texture.h"
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

		static void LoadShader(const char* name, const char* path, int count = 1);
		static void LoadTexture(const char* name, const char* path, int count = 1);

		static void Clear();

	private:
		
		gl::Shader* IGetShader(const char* name);
		gl::Texture* IGetTexture(const char* name);
		void IClear();
		void ILoadShader(const char* name, const char* path, int count);
		void ILoadTexture(const char* name, const char* path, int count);

		std::vector<std::pair<std::string, gl::Shader*>> shaders_list;
		std::vector<std::pair<std::string, gl::Texture*>> texture_list;
	};
}