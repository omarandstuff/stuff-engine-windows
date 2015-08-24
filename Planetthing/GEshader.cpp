#include "GEshader.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEShader::loadShaderWithFileName(wstring filename, GE_BUFFER_MODE buffermode)
{
	GLuint vertShader, fragShader;

	// Create shader program.
	m_programID = glCreateProgram();

	// Create and compile vertex shader.
	vertShader = compileShader(GL_VERTEX_SHADER, filename + L".vsh");
	if (!vertShader)
	{
		OutputDebugString(L"Filed to compile vertex shader");
		return;
	}

	// Create and compile fragment shader.
	fragShader = compileShader(GL_FRAGMENT_SHADER, filename + L".fsh");
	if (!vertShader)
	{
		OutputDebugString(L"Filed to compile fragment shader");
		return;
	}

	// Attach vertex shader to program.
	glAttachShader(m_programID, vertShader);

	// Attach fragment shader to program.
	glAttachShader(m_programID, fragShader);

	// Bind attribute locations.
	// This needs to be done prior to linking.
	if (buffermode == GE_BUFFER_MODE_ALL)
	{
		glBindAttribLocation(m_programID, 0, "positionCoord");
		glBindAttribLocation(m_programID, 2, "normalCoord");
		glBindAttribLocation(m_programID, 1, "textureCoord");
	}
	else if (buffermode == GE_BUFFER_MODE_POSITION)
	{
		glBindAttribLocation(m_programID, 0, "positionCoord");
	}
	else if (buffermode == GE_BUFFER_MODE_POSITION_TEXTURE)
	{
		glBindAttribLocation(m_programID, 0, "positionCoord");
		glBindAttribLocation(m_programID, 1, "textureCoord");
	}
	else if (buffermode == GE_BUFFER_MODE_POSITION_NORMAL)
	{
		glBindAttribLocation(m_programID, 0, "positionCoord");
		glBindAttribLocation(m_programID, 2, "normalCoord");
	}

	// Link program.
	if (!linkProgram())
	{
		OutputDebugString(L"Filed to link program.");

		if (vertShader)
		{
			glDeleteShader(vertShader);
			vertShader = 0;
		}
		if (fragShader)
		{
			glDeleteShader(fragShader);
			fragShader = 0;
		}
		if (m_programID)
		{
			glDeleteProgram(m_programID);
			m_programID = 0;
		}

		return;
	}

	// Release vertex and fragment shaders.
	if (vertShader)
	{
		glDetachShader(m_programID, vertShader);
		glDeleteShader(vertShader);
	}
	if (fragShader)
	{
		glDetachShader(m_programID, fragShader);
		glDeleteShader(fragShader);
	}
}

GLuint GEShader::compileShader(GLenum type, wstring filename)
{
	const char* shaderBuffer;
	GLuint shader;
	GLint status;

	// Load file into the buffer
	shaderBuffer = loadShaderSourceFile(filename);
	if (!shaderBuffer)
	{
		OutputDebugString(L"Filed to load file.");
		return 0;
	}

	// Genrate and pass the buffer to a OpenGL shader.
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderBuffer, NULL);

	// Free the buffer.
	delete[] shaderBuffer;

	// Compile
	glCompileShader(shader);

#if defined(_DEBUG)
	GLint logLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = new GLchar[logLength];
		glGetShaderInfoLog(shader, logLength, &logLength, log);
		OutputDebugString((LPCWSTR)log);
		delete[] log;
	}
#endif

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

bool GEShader::linkProgram()
{
	GLint status;
	glLinkProgram(m_programID);

#if defined(_DEBUG)
	GLint logLength;
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = new GLchar[logLength];
		glGetProgramInfoLog(m_programID, logLength, &logLength, log);
		OutputDebugString((LPCWSTR)log);
		delete[] log;
	}
#endif

	glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}

bool GEShader::validateProgram()
{
	GLint logLength, status;

	glValidateProgram(m_programID);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = new GLchar[logLength];
		glGetProgramInfoLog(m_programID, logLength, &logLength, log);
		OutputDebugString((LPCWSTR)log);
		delete[] log;
	}

	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &status);
	if (status == 0)
		return false;

	return true;
}

char* GEShader::loadShaderSourceFile(wstring filename)
{
	ifstream fin;
	int fileSize;
	char input;
	char* buffer;

	// Open the shader source file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return 0;
	}

	// Initialize the size of the file.
	fileSize = 0;

	// Read the first element of the file.
	fin.get(input);

	// Count the number of elements in the text file.
	while (!fin.eof())
	{
		fileSize++;
		fin.get(input);
	}

	// Close the file for now.
	fin.close();

	// Initialize the buffer to read the shader source file into.
	buffer = new char[fileSize + 1];
	if (!buffer)
	{
		return 0;
	}

	// Open the shader source file again.
	fin.open(filename);

	// Read the shader text file into the buffer as a block.
	fin.read(buffer, fileSize);

	// Close the file.
	fin.close();

	// Null terminate the buffer.
	buffer[fileSize] = '\0';

	return buffer;
}
