#pragma once

#include <stdexcept>
#include <string>
#include <vector>

//TODO: rename with prefix

namespace lua {
	class LuaError : public std::runtime_error {
	public:
		explicit LuaError (std::string const &msg) : std::runtime_error (msg) {};
		explicit LuaError (char const *msg) : std::runtime_error (msg) {};
	};
}

namespace file {
	class FileNotFound : public std::runtime_error {

		static std::string fileNotFoundMsg (std::string const &fname,
				std::vector<std::string> const &dirs_searched);

	public:
		explicit FileNotFound (std::string const &fname,
				std::vector<std::string> const &dirs_searched);
	};
}

#include <SDL.h>
#include <GL/glu.h>

namespace video {
	class SDL_Error : std::runtime_error {
		std::string SDL_ErrorMsg (std::string msg);

	public:
		explicit SDL_Error (int category, std::string msg);
	};


	class GL_Error : std::runtime_error {
		std::string GL_ErrorMsg (std::string msg);

	public:
		GL_Error (std::string msg);
		GL_Error (char const *msg);
	};
}
