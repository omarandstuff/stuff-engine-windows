#pragma once

#include "GEcommon.h"
#include "GEopengl.h"

class GEShader
{
	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	GLuint m_programID;

	// -------------------------------------------- //
	// ------------------- Load ------------------- //
	// -------------------------------------------- //
protected:
	void loadShaderWithFileName(wstring filename, GE_BUFFER_MODE buffermode);

	// -------------------------------------------- //
	// ------------- private members -------------- //
	// -------------------------------------------- //
private:
	GLuint compileShader(GLenum type, wstring filename);
	bool linkProgram();
	bool validateProgram();
	char* loadShaderSourceFile(wstring filename);

};