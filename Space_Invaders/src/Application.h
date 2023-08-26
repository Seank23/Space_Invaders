#pragma once
#include <GLFW/glfw3.h>
#include <memory>

#include "Game/Game.h"

namespace SpaceInvaders
{
	class Application
	{
	public:
		Application();
		~Application();

		void Init();
		void Shutdown();

		Game& GetGame() { return *m_Game; }

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			WindowData(const std::string& title = "Space Invaders",
				unsigned int width = 800, unsigned int height = 600, bool vSync = 1)
				: Title(title), Width(width), Height(height), VSync(vSync)
			{}
		};

		GLFWwindow* m_Window;
		WindowData m_WindowData;
		std::shared_ptr<Game> m_Game;

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	};
}

int main(int argc, char** argv)
{
	auto app = SpaceInvaders::Application();
}