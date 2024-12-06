#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define ASSERT(x) if ((!x)) __debugbreak();
#define GLCall(x) GLClearError();\
 x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {

	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		cout << "OpenGL Error: (" << error << ") : File (" << file << ") : Line (" << line << ")" << endl;
		return false;
	}
	return true;
}
