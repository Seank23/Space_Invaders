#include "pch.h"
#include "Application.h"
#include "Log.h"

#include <windows.h>

#include <chrono>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Engine/VertexBuffer.h"
#include "Engine/VertexBufferLayout.h"
#include "Engine/IndexBuffer.h"
#include "Engine/VertexArray.h"
#include "Engine/Shader.h"
#include "Engine/BinaryTexture.h"
#include <Engine/SpriteRenderer.h>
#include "Game/SpriteData.h"

namespace SpaceInvaders
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		ERROR("GLFW Error: ({0}): {1}", error, description);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	Application::Application()
	{
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
		SpaceInvaders::Log::Init();
		Init();
	}

	Application::~Application()
	{
		Shutdown();
	}

	void Application::Init()
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		INFO("Creating window {0} ({1}, {2})", m_WindowData.Title, m_WindowData.Width, m_WindowData.Height);
		m_Window = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);

		if (m_Window == NULL) {
			ERROR("Failed to open GLFW window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Game = std::make_shared<Game>();
		m_Game->Init(new int[2]{ (int)m_WindowData.Width, (int)m_WindowData.Height });
		
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Application* app = (Application*)glfwGetWindowUserPointer(window);
				app->GetGame().InputListener(key, action);
			}
		);

		double prevTime = glfwGetTime();
		while (!glfwWindowShouldClose(m_Window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			double deltaTime = glfwGetTime() - prevTime;
			m_Game->Update(deltaTime);
			prevTime = glfwGetTime();

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	void Application::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_Game->InputListener(key, action);
	}
}
