#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace SpaceInvaders
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int v0);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_RendererID;
		const std::string& m_Filepath;
		std::unordered_map<std::string, int> m_UniformLocationCache;

		int GetUniformLocation(const std::string& name);
		ShaderProgramSource ParseShader(const std::string& file);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	};
}
