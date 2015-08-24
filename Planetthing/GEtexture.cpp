#include "GEtexture.h"

// ------------------------------------------------------------------------------ //
// ---------------------------- Unique Testure Sytem ---------------------------- //
// ------------------------------------------------------------------------------ //

map<wstring, pair<int, GETexture*>> GETexture::m_texturesHolder;

GETexture* GETexture::textureWithFileName(wstring filename)
{
	// The texture is already loaded?
	pair<int, GETexture*> t_i = m_texturesHolder[filename];
	if (t_i.first == 0)
	{
		t_i.second = new GETexture();
		t_i.second->loadTextureWithFileName(filename);
		t_i.first = 1;
		m_texturesHolder[filename] = t_i;
	}

	return t_i.second;
}

void GETexture::releaseTexture()
{
	pair<int, GETexture*> t_i = m_texturesHolder[FileName];
	t_i.first--;
	// Remove reference if the texture is not used.
	if (t_i.first == 0)
	{
		delete t_i.second;
		m_texturesHolder.erase(FileName);
	}
}

GETexture::~GETexture()
{

}

// ------------------------------------------------------------------------------ //
// ---------------------------- Load Image - Texture ---------------------------- //
// ------------------------------------------------------------------------------ //
void GETexture::loadTextureWithFileName(wstring filename)
{
	FileName = filename;

	// Load the image form file.
	unsigned char* rawPixels = loadImageWithFileName(filename);

	if (!rawPixels) return;

	// Generate the openGL reference in the video card.
	generateTextureFromPixels(rawPixels);

	// Don't keep the pixels in RAM.
	delete[] rawPixels;
}

unsigned char* GETexture::loadImageWithFileName(wstring filename)
{
	// Initialize IL if is not already.
	static bool initialized = false;
	if (!initialized)
	{
		ilInit();
		initialized = true;
	}

	// Generate an image name to use.
	ILuint ImgId = 0;
	ilGenImages(1, &ImgId);

	// Bind this image name.
	ilBindImage(ImgId);

	if (!ilLoadImage(filename.data()))
		return 0;

	Width = ilGetInteger(IL_IMAGE_WIDTH);
	Height = ilGetInteger(IL_IMAGE_HEIGHT);

	ILenum imageFormat = ilGetInteger(IL_IMAGE_FORMAT);
	ILint imageBBP = ilGetInteger(IL_IMAGE_BPP);

	// Allocate a buffer to store the bitmap data.
	unsigned char* rawPixels = new unsigned char[Width * Height * imageBBP];
	if (!rawPixels)
	{
		return 0;
	}

	// Copy data from DevIL to our pixmap.
	ilCopyPixels(0, 0, 0, Width, Height, 1, imageFormat, IL_UNSIGNED_BYTE, rawPixels);

	// Unbound image name and frees DevIL image memory.
	ilBindImage(0);
	ilDeleteImage(ImgId);

	return rawPixels;
}

void GETexture::generateTextureFromPixels(unsigned char* rawPixels)
{
	// Generate an ID for the texture.
	glGenTextures(1, &TextureID);

	// Bind the texture as a 2D texture.
	glBindTexture(GL_TEXTURE_2D, TextureID);

	// Load the image data into the texture unit.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawPixels);

	// Use linear filetring
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Generate mipmaps for the texture.
	glGenerateMipmap(GL_TEXTURE_2D);
}