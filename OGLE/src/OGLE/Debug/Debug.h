#ifndef DEBUG_HEADER
#define DEBUG_HEADER

class Exception : public std::runtime_error
{
public:
	Exception(std::string const& msg) :
		std::runtime_error(msg)
	{}
};

#define ASSERT(x) if (!())

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
	}
}

#endif