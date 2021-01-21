#pragma once
#include "GLFW/glfw3.h"
#include <vector>
#include <functional>
#include <iostream>

namespace input
{
	class Keyboard {
	private:
		//Singleton stuff
		Keyboard();
		Keyboard(Keyboard const&) = delete;
		void operator = (Keyboard const&) = delete;
	public:
		static Keyboard& getInstance() { static Keyboard instance; return instance; }
		//Class stuff

	private:
		static std::vector<std::function<void()>> clickedFunction;
		static std::vector<bool> pressedKeys;
		static std::vector<bool> clickedKeys;
	
	public:

		static enum ky : uint8_t {
			INVALID,
			ARROW_RIGHT,
			ARROW_LEFT,
			ARROW_UP,
			ARROW_DOWN,
			W_KEY,
			A_KEY,
			S_KEY,
			D_KEY,
			SPACEBAR,
			PLUS_KEY,
			MINUS_KEY,
			ESC_KEY,
			F11_KEY
		};

		static void Init();
		static void Clear();
		static void handleInputs(GLFWwindow* window, int key, int scancode, int action, int mods);
		static bool isPress(const ky& k);
		static void clicked(const ky& k, const std::function<void()>& func);
	private:
		static inline int keyAssociated(int key);
	};
}