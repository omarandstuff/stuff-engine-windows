#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\compatibility.hpp>
#include <gtx\quaternion.hpp>
using namespace std;

// -------------------------------------------- //
// ---------------- RENDER MODE --------------- //
// -------------------------------------------- //
enum GE_RENDER_MODE
{
	GE_RENDER_MODE_NORMAL,
	GE_RENDER_MODE_DEPTH
};

// -------------------------------------------- //
// ---------------- BUFFER MODE --------------- //
// -------------------------------------------- //

enum GE_BUFFER_MODE
{
	GE_BUFFER_MODE_POSITION,
	GE_BUFFER_MODE_POSITION_TEXTURE,
	GE_BUFFER_MODE_POSITION_NORMAL,
	GE_BUFFER_MODE_ALL
};

// -------------------------------------------- //
// ---------------- UNIFORM IDs --------------- //
// -------------------------------------------- //
enum
{
	GE_UNIFORM_MODELVIEWPROJECTION_MATRIX,
	GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION,
	GE_UNIFORM_MATERIAL_DIFFUSE_MAP,
	GE_UNIFORM_MATERIAL_DIFFUSE_MAP_ENABLED,
	GE_UNIFORM_MATERIAL_SPECULAR_MAP,
	GE_UNIFORM_MATERIAL_SPECULAR_MAP_ENABLED,
	GE_UNIFORM_MATERIAL_DIFFUSE_COLOR,
	GE_UNIFORM_MATERIAL_AMBIENT_COLOR,
	GE_UNIFORM_MATERIAL_SPECULAR_COLOR,
	GE_UNIFORM_MATERIAL_SHININESS,
	GE_UNIFORM_MATERIAL_OPASITY,
	GE_UNIFORM_NUMBER_OF_VERTEX_LIGHTS,
	GE_UNIFORM_NUMBER_OF_FRAGMENT_LIGHTS,
	GE_NUM_UNIFORMS
};

enum
{
	GE_UNIFORM_LIGHT_TYPE,
	GE_UNIFORM_LIGHT_POSITION,
	GE_UNIFORM_LIGHT_DIRECTION,
	GE_UNIFORM_LIGHT_CUTOFF,
	GE_UNIFORM_LIGHT_DIFFUSE_COLOR,
	GE_UNIFORM_LIGHT_AMBIENT_COLOR,
	GE_UNIFORM_LIGHT_SPECULAR_COLOR,
	GE_UNIFORM_LIGHT_MODELVIEWPROJECTION_MATRIX,
	GE_UNIFORM_LIGHT_SHADOW_MAP,
	GE_UNIFORM_LIGHT_SHADOW_MAP_TEXTEL_SIZE,
	GE_UNIFORM_LIGHT_SHADOWS_ENABLED,
	GE_NUM_LIGHT_UNIFORMS
};
