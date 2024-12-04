#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Struct to hold the Vertex and Frangment shader sources
struct ShaderProgramSource {
	string VertexSource;
	string FragmentSource;
};

// Function to parse the shader file and split it into vertex and fragment shader code
static ShaderProgramSource ParseShader(const string& filepath) {
	ifstream stream(filepath);

	// Enum to represent the type of shader being read
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	// Read the shader file line by line
	while (getline(stream, line)) {

		// Check for shader type directives in the shader file
		if (line.find("#shader") != string::npos) {

			// Determine whether the line indicates a vertex or fragment shader
			if (line.find("vertex") != string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			// Append the shader code to the corresponding stringstream based on the shader type
			ss[(int)type] << line << '\n';
		}
	}

	// Return the parsed vertex and fragment shader sources
	return { ss[0].str(), ss[1].str() };
}

// Function to compile a shader (either vertex or fragment)
static unsigned int CompileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	// Provide the shader source code to OpenGL
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling for shader compilation
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		// Get the length of the error message
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		// Allocate space for the error message
		char* message = (char*)alloca(length * sizeof(char));
		// Retrieve the error message
		glGetShaderInfoLog(id, length, &length, message);

		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	// Return the shader ID if compilation was successful
	return id;
}

// Function to create a shader program (compiles vertex and fragment shaders and links them into a program)
static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram(); //Create shader program
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//Attach the vertex and fragment shader to the program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	
	//Link the shaders into a complete program and validate the program to ensure that it's working correctly
	glLinkProgram(program);
	glValidateProgram(program);

	//Delete the shaders to clear up space
	glDeleteShader(vs);
	glDeleteShader(fs);

	// Return the created and linked shader program
	return program;
}
