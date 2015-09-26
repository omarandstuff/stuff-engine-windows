#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <sstream>

#pragma managed(push, off)
#include <glm.hpp>
#include <gtc\constants.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>
#include <gtx\compatibility.hpp>
#include <gtx\quaternion.hpp>
#pragma managed(pop)

#include "property.h"
#include <btBulletDynamicsCommon.h>

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
	GE_UNIFORM_MODEL_MATRIX,
	GE_UNIFORM_VIEWPROJECTION_MATRIX,
	GE_UNIFORM_NORMAL_MATRIX,
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
	GE_UNIFORM_NUMBER_OF_LIGHTS,
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
	GE_UNIFORM_LIGHT_VIEWPROJECTION_MATRIX,
	GE_UNIFORM_LIGHT_SHADOW_MAP,
	GE_UNIFORM_LIGHT_SHADOW_MAP_TEXTEL_SIZE,
	GE_UNIFORM_LIGHT_SHADOWS_ENABLED,
	GE_NUM_LIGHT_UNIFORMS
};

// -------------------------------------------- //
// ---------------- Light Types --------------- //
// -------------------------------------------- //

enum GE_LIGHT_TYPE
{
	GE_LIGHT_DIRECTIONAL,
	GE_LIGHT_POINT,
	GE_LIGHT_SPOT
};

// -------------------------------------------- //
// ---------------- Camera Types -------------- //
// -------------------------------------------- //

enum GE_CAMERA_TYPE
{
	GE_CAMERA_ORTHOGONAL,
	GE_CAMERA_PERSPECTIVE
};


// -------------------------------------------- //
// --------------- MODELS_STYLES -------------- //
// -------------------------------------------- //

enum GE_DIRECTION
{
	GE_DIRECTION_POSITIVE_X,
	GE_DIRECTION_NEGATIVE_X,
	GE_DIRECTION_POSITIVE_Y,
	GE_DIRECTION_NEGATIVE_Y,
	GE_DIRECTION_POSITIVE_Z,
	GE_DIRECTION_NEGATIVE_Z
};

// -------------------------------------------- //
// ------------------- INPUT ------------------ //
// -------------------------------------------- //

enum GE_INPUT_XBOX
{
	GE_INPUT_XBOX_BUTTON_A,
	GE_INPUT_XBOX_BUTTON_B,
	GE_INPUT_XBOX_BUTTON_Y,
	GE_INPUT_XBOX_BUTTON_X,
	GE_INPUT_XBOX_BUTTON_BACK,
	GE_INPUT_XBOX_BUTTON_START,
	GE_INPUT_XBOX_LBUMPER,
	GE_INPUT_XBOX_RBUMPER,
	GE_INPUT_XBOX_DPAD_RIGHT,
	GE_INPUT_XBOX_DPAD_LEFT,
	GE_INPUT_XBOX_DPAD_UP,
	GE_INPUT_XBOX_DPAD_DOWN,
	GE_INPUT_XBOX_THUMB_LEFT,
	GE_INPUT_XBOX_THUMB_RIGHT,
	GE_INPUT_XBOX_PRESIONALBLE_NUMBER,
	GE_INPUT_XBOX_LEFT_TRIGGER,
	GE_INPUT_XBOX_RIGHT_TRIGGER,
	GE_INPUT_XBOX_LEFT_STICK,
	GE_INPUT_XBOX_RIGHT_STICK
};

enum GE_BODY_TYPE
{
	GE_BODY_TYPE_CUBE,
	GE_BODY_TYPE_SPHERE,
	GE_BODY_TYPE_CAPSULE,
	GE_BODY_TYPE_PLANE,
	GE_BODY_TYPE_CYLINDRE,
	GE_BODY_TYPE_MESH
};

// -------------------------------------------- //
// ------------------- COLORS ----------------- //
// -------------------------------------------- //

#define     color_indian_red              { 0.690196078f,  0.090196078f,   0.121568627 }
#define     color_crimson                 { 0.862745098f,  0.078431373f,   0.235294118 }
#define     color_lightpink               { 1.0f,          0.71372549f,    0.756862745 }
#define     color_lightpink_1             { 1.0f,          0.682352941f,   0.725490196 }
#define     color_lightpink_2             { 0.933333333f,  0.635294118f,   0.678431373 }
#define     color_lightpink_3             { 0.803921569f,  0.549019608f,   0.584313725 }
#define     color_lightpink_4             { 0.545098039f,  0.37254902f,    0.396078431 }
#define     color_pink                    { 1.0f,          0.752941176f,   0.796078431 }
#define     color_pink_1                  { 1.0f,          0.709803922f,   0.77254902 }
#define     color_pink_2                  { 0.933333333f,  0.662745098f,   0.721568627 }
#define     color_pink_3                  { 0.803921569f,  0.568627451f,   0.619607843 }
#define     color_pink_4                  { 0.545098039f,  0.388235294f,   0.423529412 }
#define     color_palevioletred           { 0.858823529f,  0.439215686f,   0.576470588 }
#define     color_palevioletred_1         { 1.0f,          0.509803922f,   0.670588235 }
#define     color_palevioletred_2         { 0.933333333f,  0.474509804f,   0.623529412 }
#define     color_palevioletred_3         { 0.803921569f,  0.407843137f,   0.537254902 }
#define     color_palevioletred_4         { 0.545098039f,  0.278431373f,   0.364705882 }
#define     color_lavenderblush           { 1.0f,          0.941176471f,   0.960784314 }
#define     color_lavenderblush_2         { 0.933333333f,  0.878431373f,   0.898039216 }
#define     color_lavenderblush_3         { 0.803921569f,  0.756862745f,   0.77254902 }
#define     color_lavenderblush_4         { 0.545098039f,  0.51372549f,    0.525490196 }
#define     color_violetred_1             { 1.0f,          0.243137255f,   0.588235294 }
#define     color_violetred_2             { 0.933333333f,  0.22745098f,    0.549019608 }
#define     color_violetred_3             { 0.803921569f,  0.196078431f,   0.470588235 }
#define     color_violetred_4             { 0.545098039f,  0.133333333f,   0.321568627 }
#define     color_hotpink                 { 1.0f,          0.411764706f,   0.705882353 }
#define     color_hotpink_1               { 1.0f,          0.431372549f,   0.705882353 }
#define     color_hotpink_2               { 0.933333333f,  0.415686275f,   0.654901961 }
#define     color_hotpink_3               { 0.803921569f,  0.376470588f,   0.564705882 }
#define     color_hotpink_4               { 0.545098039f,  0.22745098f,    0.384313725 }
#define     color_raspberry               { 0.529411765f,  0.149019608f,   0.341176471 }
#define     color_deeppink_1              { 1.0f,          0.078431373f,   0.576470588 }
#define     color_deeppink_2              { 0.933333333f,  0.070588235f,   0.537254902 }
#define     color_deeppink_3              { 0.803921569f,  0.062745098f,   0.462745098 }
#define     color_deeppink_4              { 0.545098039f,  0.039215686f,   0.31372549 }
#define     color_maroon_1                { 1.0f,          0.203921569f,   0.701960784 }
#define     color_maroon_2                { 0.933333333f,  0.188235294f,   0.654901961 }
#define     color_maroon_3                { 0.803921569f,  0.160784314f,   0.564705882 }
#define     color_maroon_4                { 0.545098039f,  0.109803922f,   0.384313725 }
#define     color_mediumvioletred         { 0.780392157f,  0.082352941f,   0.521568627 }
#define     color_violetred               { 0.815686275f,  0.125490196f,   0.564705882 }
#define     color_orchid                  { 0.854901961f,  0.439215686f,   0.839215686 }
#define     color_orchid_1                { 1.0f,          0.51372549f,    0.980392157 }
#define     color_orchid_2                { 0.933333333f,  0.478431373f,   0.91372549 }
#define     color_orchid_3                { 0.803921569f,  0.411764706f,   0.788235294 }
#define     color_orchid_4                { 0.545098039f,  0.278431373f,   0.537254902 }
#define     color_thistle                 { 0.847058824f,  0.749019608f,   0.847058824 }
#define     color_thistle_1               { 1.0f,          0.882352941f,   1.0 }
#define     color_thistle_2               { 0.933333333f,  0.823529412f,   0.933333333 }
#define     color_thistle_3               { 0.803921569f, 0.709803922f, 0.803921569 }
#define     color_thistle_4               { 0.545098039f, 0.482352941f, 0.545098039 }
#define     color_plum_1                  { 1.0f, 0.733333333f, 1.0 }
#define     color_plum_2                  { 0.933333333f, 0.682352941f, 0.933333333 }
#define     color_plum_3                  { 0.803921569f, 0.588235294f, 0.803921569 }
#define     color_plum_4                  { 0.545098039f, 0.4f, 0.545098039 }
#define     color_plum                    { 0.866666667f, 0.62745098f, 0.866666667 }
#define     color_violet                  { 0.933333333f, 0.509803922f, 0.933333333 }
#define     color_magenta                 { 1.0f, 0.0f, 1.0 }
#define     color_magenta_2               { 0.933333333f, 0.0f, 0.933333333 }
#define     color_magenta_3               { 0.803921569f, 0.0f, 0.803921569 }
#define     color_magenta_4               { 0.545098039f, 0.0f, 0.545098039 }
#define     color_purple                  { 0.501960784f, 0.0f, 0.501960784 }
#define     color_mediumorchid            { 0.729411765f, 0.333333333f, 0.82745098 }
#define     color_mediumorchid_1          { 0.878431373f, 0.4f, 1.0 }
#define     color_mediumorchid_2          { 0.819607843f, 0.37254902f, 0.933333333 }
#define     color_mediumorchid_3          { 0.705882353f, 0.321568627f, 0.803921569 }
#define     color_mediumorchid_4          { 0.478431373f, 0.215686275f, 0.545098039 }
#define     color_darkviolet              { 0.580392157f, 0.0f, 0.82745098 }
#define     color_darkorchid              { 0.6f, 0.196078431f, 0.8 }
#define     color_darkorchid_1            { 0.749019608f, 0.243137255f, 1.0 }
#define     color_darkorchid_2            { 0.698039216f, 0.22745098f, 0.933333333 }
#define     color_darkorchid_3            { 0.603921569f, 0.196078431f, 0.803921569 }
#define     color_darkorchid_4            { 0.407843137f, 0.133333333f, 0.545098039 }
#define     color_indigo                  { 0.294117647f, 0.0f, 0.509803922 }
#define     color_blueviolet              { 0.541176471f, 0.168627451f, 0.88627451 }
#define     color_purple_1                { 0.607843137f, 0.188235294f, 1.0 }
#define     color_purple_2                { 0.568627451f, 0.17254902f, 0.933333333 }
#define     color_purple_3                { 0.490196078f, 0.149019608f, 0.803921569 }
#define     color_purple_4                { 0.333333333f, 0.101960784f, 0.545098039 }
#define     color_mediumpurple            { 0.576470588f, 0.439215686f, 0.858823529 }
#define     color_mediumpurple_1          { 0.670588235f, 0.509803922f, 1.0 }
#define     color_mediumpurple_2          { 0.623529412f, 0.474509804f, 0.933333333 }
#define     color_mediumpurple_3          { 0.537254902f, 0.407843137f, 0.803921569 }
#define     color_mediumpurple_4          { 0.364705882f, 0.278431373f, 0.545098039 }
#define     color_darkslateblue           { 0.282352941f, 0.239215686f, 0.545098039 }
#define     color_lightslateblue          { 0.517647059f, 0.439215686f, 1.0 }
#define     color_mediumslateblue         { 0.482352941f, 0.407843137f, 0.933333333 }
#define     color_slateblue               { 0.415686275f, 0.352941176f, 0.803921569 }
#define     color_slateblue_1             { 0.51372549f, 0.435294118f, 1.0 }
#define     color_slateblue_2             { 0.478431373f, 0.403921569f, 0.933333333 }
#define     color_slateblue_3             { 0.411764706f, 0.349019608f, 0.803921569 }
#define     color_slateblue_4             { 0.278431373f, 0.235294118f, 0.545098039 }
#define     color_ghostwhite              { 0.97254902f, 0.97254902f, 1.0 }
#define     color_lavender                { 0.901960784f, 0.901960784f, 0.980392157 }
#define     color_blue                    { 0.0f, 0.0f, 1.0 }
#define     color_blue_2                  { 0.0f, 0.0f, 0.933333333 }
#define     color_blue_3                  { 0.0f, 0.0f, 0.803921569 }
#define     color_blue_4                  { 0.0f, 0.0f, 0.545098039 }
#define     color_navy                    { 0.0f, 0.0f, 0.501960784 }
#define     color_midnightblue            { 0.098039216f, 0.098039216f, 0.439215686 }
#define     color_cobalt                  { 0.239215686f, 0.349019608f, 0.670588235 }
#define     color_royalblue               { 0.254901961f, 0.411764706f, 0.882352941 }
#define     color_royalblue_1             { 0.282352941f, 0.462745098f, 1.0 }
#define     color_royalblue_2             { 0.262745098f, 0.431372549f, 0.933333333 }
#define     color_royalblue_3             { 0.22745098f, 0.37254902f, 0.803921569 }
#define     color_royalblue_4             { 0.152941176f, 0.250980392f, 0.545098039 }
#define     color_cornflowerblue          { 0.392156863f, 0.584313725f, 0.929411765 }
#define     color_lightsteelblue          { 0.690196078f, 0.768627451f, 0.870588235 }
#define     color_lightsteelblue_1        { 0.792156863f, 0.882352941f, 1.0 }
#define     color_lightsteelblue_2        { 0.737254902f, 0.823529412f, 0.933333333 }
#define     color_lightsteelblue_3        { 0.635294118f, 0.709803922f, 0.803921569 }
#define     color_lightsteelblue_4        { 0.431372549f, 0.482352941f, 0.545098039 }
#define     color_lightslategray          { 0.466666667f, 0.533333333f, 0.6 }
#define     color_slategray               { 0.439215686f, 0.501960784f, 0.564705882 }
#define     color_slategray_1             { 0.776470588f, 0.88627451f, 1.0 }
#define     color_slategray_2             { 0.725490196f, 0.82745098f, 0.933333333 }
#define     color_slategray_3             { 0.623529412f, 0.71372549f, 0.803921569 }
#define     color_slategray_4             { 0.423529412f, 0.482352941f, 0.545098039 }
#define     color_dodgerblue              { 0.117647059f, 0.564705882f, 1.0 }
#define     color_dodgerblue_2            { 0.109803922f, 0.525490196f, 0.933333333 }
#define     color_dodgerblue_3            { 0.094117647f, 0.454901961f, 0.803921569 }
#define     color_dodgerblue_4            { 0.062745098f, 0.305882353f, 0.545098039 }
#define     color_aliceblue               { 0.941176471f, 0.97254902f, 1.0 }
#define     color_steelblue               { 0.274509804f, 0.509803922f, 0.705882353 }
#define     color_steelblue_1             { 0.388235294f, 0.721568627f, 1.0 }
#define     color_steelblue_2             { 0.360784314f, 0.674509804f, 0.933333333 }
#define     color_steelblue_3             { 0.309803922f, 0.580392157f, 0.803921569 }
#define     color_steelblue_4             { 0.211764706f, 0.392156863f, 0.545098039 }
#define     color_lightskyblue            { 0.529411765f, 0.807843137f, 0.980392157 }
#define     color_lightskyblue_1          { 0.690196078f, 0.88627451f, 1.0 }
#define     color_lightskyblue_2          { 0.643137255f, 0.82745098f, 0.933333333 }
#define     color_lightskyblue_3          { 0.552941176f, 0.71372549f, 0.803921569 }
#define     color_lightskyblue_4          { 0.376470588f, 0.482352941f, 0.545098039 }
#define     color_skyblue_1               { 0.529411765f, 0.807843137f, 1.0 }
#define     color_skyblue_2               { 0.494117647f, 0.752941176f, 0.933333333 }
#define     color_skyblue_3               { 0.423529412f, 0.650980392f, 0.803921569 }
#define     color_skyblue_4               { 0.290196078f, 0.439215686f, 0.545098039 }
#define     color_skyblue                 { 0.529411765f, 0.807843137f, 0.921568627 }
#define     color_deepskyblue             { 0.0f, 0.749019608f, 1.0 }
#define     color_deepskyblue_2           { 0.0f, 0.698039216f, 0.933333333 }
#define     color_deepskyblue_3           { 0.0f, 0.603921569f, 0.803921569 }
#define     color_deepskyblue_4           { 0.0f, 0.407843137f, 0.545098039 }
#define     color_peacock                 { 0.2f, 0.631372549f, 0.788235294 }
#define     color_lightblue               { 0.678431373f, 0.847058824f, 0.901960784 }
#define     color_lightblue_1             { 0.749019608f, 0.937254902f, 1.0 }
#define     color_lightblue_2             { 0.698039216f, 0.874509804f, 0.933333333 }
#define     color_lightblue_3             { 0.603921569f, 0.752941176f, 0.803921569 }
#define     color_lightblue_4             { 0.407843137f, 0.51372549f, 0.545098039 }
#define     color_powderblue              { 0.690196078f, 0.878431373f, 0.901960784 }
#define     color_cadetblue_1             { 0.596078431f, 0.960784314f, 1.0 }
#define     color_cadetblue_2             { 0.556862745f, 0.898039216f, 0.933333333 }
#define     color_cadetblue_3             { 0.478431373f, 0.77254902f, 0.803921569 }
#define     color_cadetblue_4             { 0.325490196f, 0.525490196f, 0.545098039 }
#define     color_turquoise_1             { 0.0f, 0.960784314f, 1.0 }
#define     color_turquoise_2             { 0.0f, 0.898039216f, 0.933333333 }
#define     color_turquoise_3             { 0.0f, 0.77254902f, 0.803921569 }
#define     color_turquoise_4             { 0.0f, 0.525490196f, 0.545098039 }
#define     color_cadetblue               { 0.37254902f, 0.619607843f, 0.62745098 }
#define     color_darkturquoise           { 0.0f, 0.807843137f, 0.819607843 }
#define     color_azure                   { 0.941176471f, 1.0f, 1.0 }
#define     color_azure_2                 { 0.878431373f, 0.933333333f, 0.933333333 }
#define     color_azure_3                 { 0.756862745f, 0.803921569f, 0.803921569 }
#define     color_azure_4                 { 0.51372549f, 0.545098039f, 0.545098039 }
#define     color_lightcyan               { 0.878431373f, 1.0f, 1.0 }
#define     color_lightcyan_2             { 0.819607843f, 0.933333333f, 0.933333333 }
#define     color_lightcyan_3             { 0.705882353f, 0.803921569f, 0.803921569 }
#define     color_lightcyan_4             { 0.478431373f, 0.545098039f, 0.545098039 }
#define     color_paleturquoise           { 0.733333333f, 1.0f, 1.0 }
#define     color_paleturquoise_2         { 0.682352941f, 0.933333333f, 0.933333333 }
#define     color_paleturquoise_3         { 0.588235294f, 0.803921569f, 0.803921569 }
#define     color_paleturquoise_4         { 0.4f, 0.545098039f, 0.545098039 }
#define     color_darkslategray           { 0.184313725f, 0.309803922f, 0.309803922 }
#define     color_darkslategray_1         { 0.592156863f, 1.0f, 1.0 }
#define     color_darkslategray_2         { 0.552941176f, 0.933333333f, 0.933333333 }
#define     color_darkslategray_3         { 0.474509804f, 0.803921569f, 0.803921569 }
#define     color_darkslategray_4         { 0.321568627f, 0.545098039f, 0.545098039 }
#define     color_cyan                    { 0.0f, 1.0f, 1.0 }
#define     color_cyan_2                  { 0.0f, 0.933333333f, 0.933333333 }
#define     color_cyan_3                  { 0.0f, 0.803921569f, 0.803921569 }
#define     color_cyan_4                  { 0.0f, 0.545098039f, 0.545098039 }
#define     color_teal                    { 0.0f, 0.501960784f, 0.501960784 }
#define     color_mediumturquoise         { 0.282352941f, 0.819607843f, 0.8 }
#define     color_lightseagreen           { 0.125490196f, 0.698039216f, 0.666666667 }
#define     color_manganeseblue           { 0.011764706f, 0.658823529f, 0.619607843 }
#define     color_turquoise               { 0.250980392f, 0.878431373f, 0.815686275 }
#define     color_coldgrey                { 0.501960784f, 0.541176471f, 0.529411765 }
#define     color_turquoiseblue           { 0.0f, 0.780392157f, 0.549019608 }
#define     color_aquamarine              { 0.498039216f, 1.0f, 0.831372549 }
#define     color_aquamarine_2            { 0.462745098f, 0.933333333f, 0.776470588 }
#define     color_aquamarine_3            { 0.4f, 0.803921569f, 0.666666667 }
#define     color_aquamarine_4            { 0.270588235f, 0.545098039f, 0.454901961 }
#define     color_mediumspringgreen       { 0.0f, 0.980392157f, 0.603921569 }
#define     color_mintcream               { 0.960784314f, 1.0f, 0.980392157 }
#define     color_springgreen             { 0.0f, 1.0f, 0.498039216 }
#define     color_springgreen_1           { 0.0f, 0.933333333f, 0.462745098 }
#define     color_springgreen_2           { 0.0f, 0.803921569f, 0.4 }
#define     color_springgreen_3           { 0.0f, 0.545098039f, 0.270588235 }
#define     color_mediumseagreen          { 0.235294118f, 0.701960784f, 0.443137255 }
#define     color_seagreen_1              { 0.329411765f, 1.0f, 0.623529412 }
#define     color_seagreen_2              { 0.305882353f, 0.933333333f, 0.580392157 }
#define     color_seagreen_3              { 0.262745098f, 0.803921569f, 0.501960784 }
#define     color_seagreen_4              { 0.180392157f, 0.545098039f, 0.341176471 }
#define     color_emeraldgreen            { 0.0f, 0.788235294f, 0.341176471 }
#define     color_mint                    { 0.741176471f, 0.988235294f, 0.788235294 }
#define     color_cobaltgreen             { 0.239215686f, 0.568627451f, 0.250980392 }
#define     color_honeydew                { 0.941176471f, 1.0f, 0.941176471 }
#define     color_honeydew_2              { 0.878431373f, 0.933333333f, 0.878431373 }
#define     color_honeydew_3              { 0.756862745f, 0.803921569f, 0.756862745 }
#define     color_honeydew_4              { 0.51372549f, 0.545098039f, 0.51372549 }
#define     color_darkseagreen            { 0.560784314f, 0.737254902f, 0.560784314 }
#define     color_darkseagreen_1          { 0.756862745f, 1.0f, 0.756862745 }
#define     color_darkseagreen_2          { 0.705882353f, 0.933333333f, 0.705882353 }
#define     color_darkseagreen_3          { 0.607843137f, 0.803921569f, 0.607843137 }
#define     color_darkseagreen_4          { 0.411764706f, 0.545098039f, 0.411764706 }
#define     color_palegreen               { 0.596078431f, 0.984313725f, 0.596078431 }
#define     color_palegreen_1             { 0.603921569f, 1.0f, 0.603921569 }
#define     color_palegreen_2             { 0.564705882f, 0.933333333f, 0.564705882 }
#define     color_palegreen_3             { 0.48627451f, 0.803921569f, 0.48627451 }
#define     color_palegreen_4             { 0.329411765f, 0.545098039f, 0.329411765 }
#define     color_limegreen               { 0.196078431f, 0.803921569f, 0.196078431 }
#define     color_forestgreen             { 0.133333333f, 0.545098039f, 0.133333333 }
#define     color_lime                    { 0.0f, 1.0f, 0.0 }
#define     color_green_2                 { 0.0f, 0.933333333f, 0.0 }
#define     color_green_3                 { 0.0f, 0.803921569f, 0.0 }
#define     color_green_4                 { 0.0f, 0.545098039f, 0.0 }
#define     color_green                   { 0.0f, 0.501960784f, 0.0 }
#define     color_darkgreen               { 0.0f, 0.392156863f, 0.0 }
#define     color_sapgreen                { 0.188235294f, 0.501960784f, 0.078431373 }
#define     color_lawngreen               { 0.48627451f, 0.988235294f, 0.0 }
#define     color_chartreuse              { 0.498039216f, 1.0f, 0.0 }
#define     color_chartreuse_2            { 0.462745098f, 0.933333333f, 0.0 }
#define     color_chartreuse_3            { 0.4f, 0.803921569f, 0.0 }
#define     color_chartreuse_4            { 0.270588235f, 0.545098039f, 0.0 }
#define     color_greenyellow             { 0.678431373f, 1.0f, 0.184313725 }
#define     color_darkolivegreen_1        { 0.792156863f, 1.0f, 0.439215686 }
#define     color_darkolivegreen_2        { 0.737254902f, 0.933333333f, 0.407843137 }
#define     color_darkolivegreen_3        { 0.635294118f, 0.803921569f, 0.352941176 }
#define     color_darkolivegreen_4        { 0.431372549f, 0.545098039f, 0.239215686 }
#define     color_darkolivegreen          { 0.333333333f, 0.419607843f, 0.184313725 }
#define     color_olivedrab               { 0.419607843f, 0.556862745f, 0.137254902 }
#define     color_olivedrab_1             { 0.752941176f, 1.0f, 0.243137255 }
#define     color_olivedrab_2             { 0.701960784f, 0.933333333f, 0.22745098 }
#define     color_olivedrab_3             { 0.603921569f, 0.803921569f, 0.196078431 }
#define     color_olivedrab_4             { 0.411764706f, 0.545098039f, 0.133333333 }
#define     color_ivory                   { 1.0f, 1.0f, 0.941176471 }
#define     color_ivory_2                 { 0.933333333f, 0.933333333f, 0.878431373 }
#define     color_ivory_3                 { 0.803921569f, 0.803921569f, 0.756862745 }
#define     color_ivory_4                 { 0.545098039f, 0.545098039f, 0.51372549 }
#define     color_beige                   { 0.960784314f, 0.960784314f, 0.862745098 }
#define     color_lightyellow             { 1.0f, 1.0f, 0.878431373 }
#define     color_lightyellow_2           { 0.933333333f, 0.933333333f, 0.819607843 }
#define     color_lightyellow_3           { 0.803921569f, 0.803921569f, 0.705882353 }
#define     color_lightyellow_4           { 0.545098039f, 0.545098039f, 0.478431373 }
#define     color_lightgoldenrodyellow    { 0.980392157f, 0.980392157f, 0.823529412 }
#define     color_yellow                  { 1.0f, 1.0f, 0.0 }
#define     color_yellow_2                { 0.933333333f, 0.933333333f, 0.0 }
#define     color_yellow_3                { 0.803921569f, 0.803921569f, 0.0 }
#define     color_yellow_4                { 0.545098039f, 0.545098039f, 0.0 }
#define     color_warmgrey                { 0.501960784f, 0.501960784f, 0.411764706 }
#define     color_olive                   { 0.501960784f, 0.501960784f, 0.0 }
#define     color_darkkhaki               { 0.741176471f, 0.717647059f, 0.419607843 }
#define     color_khaki_2                 { 1.0f, 0.964705882f, 0.560784314 }
#define     color_khaki_3                 { 0.933333333f, 0.901960784f, 0.521568627 }
#define     color_khaki_4                 { 0.803921569f, 0.776470588f, 0.450980392 }
#define     color_khaki_5                 { 0.545098039f, 0.525490196f, 0.305882353 }
#define     color_khaki                   { 0.941176471f, 0.901960784f, 0.549019608 }
#define     color_palegoldenrod           { 0.933333333f, 0.909803922f, 0.666666667 }
#define     color_lemonchiffon            { 1.0f, 0.980392157f, 0.803921569 }
#define     color_lemonchiffon_2          { 0.933333333f, 0.91372549f, 0.749019608 }
#define     color_lemonchiffon_3          { 0.803921569f, 0.788235294f, 0.647058824 }
#define     color_lemonchiffon_4          { 0.545098039f, 0.537254902f, 0.439215686 }
#define     color_lightgoldenrod_1        { 1.0f, 0.925490196f, 0.545098039 }
#define     color_lightgoldenrod_2        { 0.933333333f, 0.862745098f, 0.509803922 }
#define     color_lightgoldenrod_3        { 0.803921569f, 0.745098039f, 0.439215686 }
#define     color_lightgoldenrod_4        { 0.545098039f, 0.505882353f, 0.298039216 }
#define     color_banana                  { 0.890196078f, 0.811764706f, 0.341176471 }
#define     color_gold                    { 1.0f, 0.843137255f, 0.0 }
#define     color_gold_2                  { 0.933333333f, 0.788235294f, 0.0 }
#define     color_gold_3                  { 0.803921569f, 0.678431373f, 0.0 }
#define     color_gold_4                  { 0.545098039f, 0.458823529f, 0.0 }
#define     color_cornsilk                { 1.0f, 0.97254902f, 0.862745098 }
#define     color_cornsilk_2              { 0.933333333f, 0.909803922f, 0.803921569 }
#define     color_cornsilk_3              { 0.803921569f, 0.784313725f, 0.694117647 }
#define     color_cornsilk_4              { 0.545098039f, 0.533333333f, 0.470588235 }
#define     color_goldenrod               { 0.854901961f, 0.647058824f, 0.125490196 }
#define     color_goldenrod_1             { 1.0f, 0.756862745f, 0.145098039 }
#define     color_goldenrod_2             { 0.933333333f, 0.705882353f, 0.133333333 }
#define     color_goldenrod_3             { 0.803921569f, 0.607843137f, 0.11372549 }
#define     color_goldenrod_4             { 0.545098039f, 0.411764706f, 0.078431373 }
#define     color_darkgoldenrod           { 0.721568627f, 0.525490196f, 0.043137255 }
#define     color_darkgoldenrod_1         { 1.0f, 0.725490196f, 0.058823529 }
#define     color_darkgoldenrod_2         { 0.933333333f, 0.678431373f, 0.054901961 }
#define     color_darkgoldenrod_3         { 0.803921569f, 0.584313725f, 0.047058824 }
#define     color_darkgoldenrod_4         { 0.545098039f, 0.396078431f, 0.031372549 }
#define     color_orange                  { 1.0f, 0.647058824f, 0.0 }
#define     color_orange_2                { 0.933333333f, 0.603921569f, 0.0 }
#define     color_orange_3                { 0.803921569f, 0.521568627f, 0.0 }
#define     color_orange_4                { 0.545098039f, 0.352941176f, 0.0 }
#define     color_floralwhite             { 1.0f, 0.980392157f, 0.941176471 }
#define     color_oldlace                 { 0.992156863f, 0.960784314f, 0.901960784 }
#define     color_wheat                   { 0.960784314f, 0.870588235f, 0.701960784 }
#define     color_wheat_1                 { 1.0f, 0.905882353f, 0.729411765 }
#define     color_wheat_2                 { 0.933333333f, 0.847058824f, 0.682352941 }
#define     color_wheat_3                 { 0.803921569f, 0.729411765f, 0.588235294 }
#define     color_wheat_4                 { 0.545098039f, 0.494117647f, 0.4 }
#define     color_moccasin                { 1.0f, 0.894117647f, 0.709803922 }
#define     color_papayawhip              { 1.0f, 0.937254902f, 0.835294118 }
#define     color_blanchedalmond          { 1.0f, 0.921568627f, 0.803921569 }
#define     color_navajowhite             { 1.0f, 0.870588235f, 0.678431373 }
#define     color_navajowhite_2           { 0.933333333f, 0.811764706f, 0.631372549 }
#define     color_navajowhite_3           { 0.803921569f, 0.701960784f, 0.545098039 }
#define     color_navajowhite_4           { 0.545098039f, 0.474509804f, 0.368627451 }
#define     color_eggshell                { 0.988235294f, 0.901960784f, 0.788235294 }
#define     color_tan                     { 0.823529412f, 0.705882353f, 0.549019608 }
#define     color_brick                   { 0.611764706f, 0.4f, 0.121568627 }
#define     color_cadmiumyellow           { 1.0f, 0.6f, 0.070588235 }
#define     color_antiquewhite            { 0.980392157f, 0.921568627f, 0.843137255 }
#define     color_antiquewhite_1          { 1.0f, 0.937254902f, 0.858823529 }
#define     color_antiquewhite_2          { 0.933333333f, 0.874509804f, 0.8 }
#define     color_antiquewhite_3          { 0.803921569f, 0.752941176f, 0.690196078 }
#define     color_antiquewhite_4          { 0.545098039f, 0.51372549f, 0.470588235 }
#define     color_burlywood               { 0.870588235f, 0.721568627f, 0.529411765 }
#define     color_burlywood_1             { 1.0f, 0.82745098f, 0.607843137 }
#define     color_burlywood_2             { 0.933333333f, 0.77254902f, 0.568627451 }
#define     color_burlywood_3             { 0.803921569f, 0.666666667f, 0.490196078 }
#define     color_burlywood_4             { 0.545098039f, 0.450980392f, 0.333333333 }
#define     color_bisque                  { 1.0f, 0.894117647f, 0.768627451 }
#define     color_bisque_2                { 0.933333333f, 0.835294118f, 0.717647059 }
#define     color_bisque_3                { 0.803921569f, 0.717647059f, 0.619607843 }
#define     color_bisque_4                { 0.545098039f, 0.490196078f, 0.419607843 }
#define     color_melon                   { 0.890196078f, 0.658823529f, 0.411764706 }
#define     color_carrot                  { 0.929411765f, 0.568627451f, 0.129411765 }
#define     color_darkorange              { 1.0f, 0.549019608f, 0.0 }
#define     color_darkorange_1            { 1.0f, 0.498039216f, 0.0 }
#define     color_darkorange_2            { 0.933333333f, 0.462745098f, 0.0 }
#define     color_darkorange_3            { 0.803921569f, 0.4f, 0.0 }
#define     color_darkorange_4            { 0.545098039f, 0.270588235f, 0.0 }
#define     color_tan_1                   { 1.0f, 0.647058824f, 0.309803922 }
#define     color_tan_2                   { 0.933333333f, 0.603921569f, 0.28627451 }
#define     color_tan_3                   { 0.803921569f, 0.521568627f, 0.247058824 }
#define     color_tan_4                   { 0.545098039f, 0.352941176f, 0.168627451 }
#define     color_linen                   { 0.980392157f, 0.941176471f, 0.901960784 }
#define     color_peachpuff               { 1.0f, 0.854901961f, 0.725490196 }
#define     color_peachpuff_2             { 0.933333333f, 0.796078431f, 0.678431373 }
#define     color_peachpuff_3             { 0.803921569f, 0.68627451f, 0.584313725 }
#define     color_peachpuff_4             { 0.545098039f, 0.466666667f, 0.396078431 }
#define     color_seashell                { 1.0f, 0.960784314f, 0.933333333 }
#define     color_seashell_2              { 0.933333333f, 0.898039216f, 0.870588235 }
#define     color_seashell_3              { 0.803921569f, 0.77254902f, 0.749019608 }
#define     color_seashell_4              { 0.545098039f, 0.525490196f, 0.509803922 }
#define     color_sandybrown              { 0.956862745f, 0.643137255f, 0.376470588 }
#define     color_rawsienna               { 0.780392157f, 0.380392157f, 0.078431373 }
#define     color_chocolate               { 0.823529412f, 0.411764706f, 0.117647059 }
#define     color_chocolate_1             { 1.0f, 0.498039216f, 0.141176471 }
#define     color_chocolate_2             { 0.933333333f, 0.462745098f, 0.129411765 }
#define     color_chocolate_3             { 0.803921569f, 0.4f, 0.11372549 }
#define     color_chocolate_4             { 0.545098039f, 0.270588235f, 0.074509804 }
#define     color_ivoryblack              { 0.160784314f, 0.141176471f, 0.129411765 }
#define     color_flesh                   { 1.0f, 0.490196078f, 0.250980392 }
#define     color_cadmiumorange           { 1.0f, 0.380392157f, 0.011764706 }
#define     color_burntsienna             { 0.541176471f, 0.211764706f, 0.058823529 }
#define     color_sienna                  { 0.62745098f, 0.321568627f, 0.176470588 }
#define     color_sienna_1                { 1.0f, 0.509803922f, 0.278431373 }
#define     color_sienna_2                { 0.933333333f, 0.474509804f, 0.258823529 }
#define     color_sienna_3                { 0.803921569f, 0.407843137f, 0.223529412 }
#define     color_sienna_4                { 0.545098039f, 0.278431373f, 0.149019608 }
#define     color_lightsalmon             { 1.0f, 0.62745098f, 0.478431373 }
#define     color_lightsalmon_2           { 0.933333333f, 0.584313725f, 0.447058824 }
#define     color_lightsalmon_3           { 0.803921569f, 0.505882353f, 0.384313725 }
#define     color_lightsalmon_4           { 0.545098039f, 0.341176471f, 0.258823529 }
#define     color_coral                   { 1.0f, 0.498039216f, 0.31372549 }
#define     color_orangered               { 1.0f, 0.270588235f, 0.0 }
#define     color_orangered_2             { 0.933333333f, 0.250980392f, 0.0 }
#define     color_orangered_3             { 0.803921569f, 0.215686275f, 0.0 }
#define     color_orangered_4             { 0.545098039f, 0.145098039f, 0.0 }
#define     color_sepia                   { 0.368627451f, 0.149019608f, 0.070588235 }
#define     color_darksalmon              { 0.91372549f, 0.588235294f, 0.478431373 }
#define     color_salmon_1                { 1.0f, 0.549019608f, 0.411764706 }
#define     color_salmon_2                { 0.933333333f, 0.509803922f, 0.384313725 }
#define     color_salmon_3                { 0.803921569f, 0.439215686f, 0.329411765 }
#define     color_salmon_4                { 0.545098039f, 0.298039216f, 0.223529412 }
#define     color_coral_1                 { 1.0f, 0.447058824f, 0.337254902 }
#define     color_coral_2                 { 0.933333333f, 0.415686275f, 0.31372549 }
#define     color_coral_3                 { 0.803921569f, 0.356862745f, 0.270588235 }
#define     color_coral_4                 { 0.545098039f, 0.243137255f, 0.184313725 }
#define     color_burntumber              { 0.541176471f, 0.2f, 0.141176471 }
#define     color_tomato                  { 1.0f, 0.388235294f, 0.278431373 }
#define     color_tomato_2                { 0.933333333f, 0.360784314f, 0.258823529 }
#define     color_tomato_3                { 0.803921569f, 0.309803922f, 0.223529412 }
#define     color_tomato_4                { 0.545098039f, 0.211764706f, 0.149019608 }
#define     color_salmon                  { 0.980392157f, 0.501960784f, 0.447058824 }
#define     color_mistyrose               { 1.0f, 0.894117647f, 0.882352941 }
#define     color_mistyrose_2             { 0.933333333f, 0.835294118f, 0.823529412 }
#define     color_mistyrose_3             { 0.803921569f, 0.717647059f, 0.709803922 }
#define     color_mistyrose_4             { 0.545098039f, 0.490196078f, 0.482352941 }
#define     color_snow                    { 1.0f, 0.980392157f, 0.980392157 }
#define     color_snow_2                  { 0.933333333f, 0.91372549f, 0.91372549 }
#define     color_snow_3                  { 0.803921569f, 0.788235294f, 0.788235294 }
#define     color_snow_4                  { 0.545098039f, 0.537254902f, 0.537254902 }
#define     color_rosybrown               { 0.737254902f, 0.560784314f, 0.560784314 }
#define     color_rosybrown_1             { 1.0f, 0.756862745f, 0.756862745 }
#define     color_rosybrown_2             { 0.933333333f, 0.705882353f, 0.705882353 }
#define     color_rosybrown_3             { 0.803921569f, 0.607843137f, 0.607843137 }
#define     color_rosybrown_4             { 0.545098039f, 0.411764706f, 0.411764706 }
#define     color_lightcoral              { 0.941176471f, 0.501960784f, 0.501960784 }
#define     color_indianred               { 0.803921569f, 0.360784314f, 0.360784314 }
#define     color_indianred_1             { 1.0f, 0.415686275f, 0.415686275 }
#define     color_indianred_2             { 0.933333333f, 0.388235294f, 0.388235294 }
#define     color_indianred_4             { 0.545098039f, 0.22745098f, 0.22745098 }
#define     color_indianred_3             { 0.803921569f, 0.333333333f, 0.333333333 }
#define     color_brown                   { 0.647058824f, 0.164705882f, 0.164705882 }
#define     color_brown_1                 { 1.0f, 0.250980392f, 0.250980392 }
#define     color_brown_2                 { 0.933333333f, 0.231372549f, 0.231372549 }
#define     color_brown_3                 { 0.803921569f, 0.2f, 0.2 }
#define     color_brown_4                 { 0.545098039f, 0.137254902f, 0.137254902 }
#define     color_firebrick               { 0.698039216f, 0.133333333f, 0.133333333 }
#define     color_firebrick_1             { 1.0f, 0.188235294f, 0.188235294 }
#define     color_firebrick_2             { 0.933333333f, 0.17254902f, 0.17254902 }
#define     color_firebrick_3             { 0.803921569f, 0.149019608f, 0.149019608 }
#define     color_firebrick_4             { 0.545098039f, 0.101960784f, 0.101960784 }
#define     color_red                     { 1.0f, 0.0f, 0.0 }
#define     color_red_2                   { 0.933333333f, 0.0f, 0.0 }
#define     color_red_3                   { 0.803921569f, 0.0f, 0.0 }
#define     color_red_4                   { 0.545098039f, 0.0f, 0.0 }
#define     color_maroon                  { 0.501960784f, 0.0f, 0.0 }
#define     color_sgi_beet                { 0.556862745f, 0.219607843f, 0.556862745 }
#define     color_sgi_slateblue           { 0.443137255f, 0.443137255f, 0.776470588 }
#define     color_sgi_lightblue           { 0.490196078f, 0.619607843f, 0.752941176 }
#define     color_sgi_teal                { 0.219607843f, 0.556862745f, 0.556862745 }
#define     color_sgi_chartreuse          { 0.443137255f, 0.776470588f, 0.443137255 }
#define     color_sgi_olivedrab           { 0.556862745f, 0.556862745f, 0.219607843 }
#define     color_sgi_brightgray          { 0.77254902f, 0.756862745f, 0.666666667 }
#define     color_sgi_salmon              { 0.776470588f, 0.443137255f, 0.443137255 }
#define     color_sgi_darkgray            { 0.333333333f, 0.333333333f, 0.333333333 }
#define     color_sgi_gray_12             { 0.117647059f, 0.117647059f, 0.117647059 }
#define     color_sgi_gray_16             { 0.156862745f, 0.156862745f, 0.156862745 }
#define     color_sgi_gray_32             { 0.317647059f, 0.317647059f, 0.317647059 }
#define     color_sgi_gray_36             { 0.356862745f, 0.356862745f, 0.356862745 }
#define     color_sgi_gray_52             { 0.517647059f, 0.517647059f, 0.517647059 }
#define     color_sgi_gray_56             { 0.556862745f, 0.556862745f, 0.556862745 }
#define     color_sgi_lightgray           { 0.666666667f, 0.666666667f, 0.666666667 }
#define     color_sgi_gray_72             { 0.717647059f, 0.717647059f, 0.717647059 }
#define     color_sgi_gray_76             { 0.756862745f, 0.756862745f, 0.756862745 }
#define     color_sgi_gray_92             { 0.917647059f, 0.917647059f, 0.917647059 }
#define     color_sgi_gray_96             { 0.956862745f, 0.956862745f, 0.956862745 }
#define     color_white                   { 1.0f, 1.0f, 1.0 }
#define     color_white_smoke             { 0.960784314f, 0.960784314f, 0.960784314 }
#define     color_gainsboro               { 0.862745098f, 0.862745098f, 0.862745098 }
#define     color_lightgrey               { 0.82745098f, 0.82745098f, 0.82745098 }
#define     color_silver                  { 0.752941176f, 0.752941176f, 0.752941176 }
#define     color_darkgray                { 0.662745098f, 0.662745098f, 0.662745098 }
#define     color_gray                    { 0.501960784f, 0.501960784f, 0.501960784 }
#define     color_dimgray                 { 0.411764706f, 0.411764706f, 0.411764706 }
#define     color_black                   { 0.0f, 0.0f, 0.0 }
#define     color_gray_99                 { 0.988235294f, 0.988235294f, 0.988235294 }
#define     color_gray_98                 { 0.980392157f, 0.980392157f, 0.980392157 }
#define     color_gray_97                 { 0.968627451f, 0.968627451f, 0.968627451 }
#define     color_gray_95                 { 0.949019608f, 0.949019608f, 0.949019608 }
#define     color_gray_94                 { 0.941176471f, 0.941176471f, 0.941176471 }
#define     color_gray_93                 { 0.929411765f, 0.929411765f, 0.929411765 }
#define     color_gray_92                 { 0.921568627f, 0.921568627f, 0.921568627 }
#define     color_gray_91                 { 0.909803922f, 0.909803922f, 0.909803922 }
#define     color_gray_90                 { 0.898039216f, 0.898039216f, 0.898039216 }
#define     color_gray_89                 { 0.890196078f, 0.890196078f, 0.890196078 }
#define     color_gray_88                 { 0.878431373f, 0.878431373f, 0.878431373 }
#define     color_gray_87                 { 0.870588235f, 0.870588235f, 0.870588235 }
#define     color_gray_86                 { 0.858823529f, 0.858823529f, 0.858823529 }
#define     color_gray_85                 { 0.850980392f, 0.850980392f, 0.850980392 }
#define     color_gray_84                 { 0.839215686f, 0.839215686f, 0.839215686 }
#define     color_gray_83                 { 0.831372549f, 0.831372549f, 0.831372549 }
#define     color_gray_82                 { 0.819607843f, 0.819607843f, 0.819607843 }
#define     color_gray_81                 { 0.811764706f, 0.811764706f, 0.811764706 }
#define     color_gray_80                 { 0.8f, 0.8f, 0.8 }
#define     color_gray_79                 { 0.788235294f, 0.788235294f, 0.788235294 }
#define     color_gray_78                 { 0.780392157f, 0.780392157f, 0.780392157 }
#define     color_gray_77                 { 0.768627451f, 0.768627451f, 0.768627451 }
#define     color_gray_76                 { 0.760784314f, 0.760784314f, 0.760784314 }
#define     color_gray_75                 { 0.749019608f, 0.749019608f, 0.749019608 }
#define     color_gray_74                 { 0.741176471f, 0.741176471f, 0.741176471 }
#define     color_gray_73                 { 0.729411765f, 0.729411765f, 0.729411765 }
#define     color_gray_72                 { 0.721568627f, 0.721568627f, 0.721568627 }
#define     color_gray_71                 { 0.709803922f, 0.709803922f, 0.709803922 }
#define     color_gray_70                 { 0.701960784f, 0.701960784f, 0.701960784 }
#define     color_gray_69                 { 0.690196078f, 0.690196078f, 0.690196078 }
#define     color_gray_68                 { 0.678431373f, 0.678431373f, 0.678431373 }
#define     color_gray_67                 { 0.670588235f, 0.670588235f, 0.670588235 }
#define     color_gray_66                 { 0.658823529f, 0.658823529f, 0.658823529 }
#define     color_gray_65                 { 0.650980392f, 0.650980392f, 0.650980392 }
#define     color_gray_64                 { 0.639215686f, 0.639215686f, 0.639215686 }
#define     color_gray_63                 { 0.631372549f, 0.631372549f, 0.631372549 }
#define     color_gray_62                 { 0.619607843f, 0.619607843f, 0.619607843 }
#define     color_gray_61                 { 0.611764706f, 0.611764706f, 0.611764706 }
#define     color_gray_60                 { 0.6f, 0.6f, 0.6 }
#define     color_gray_59                 { 0.588235294f, 0.588235294f, 0.588235294 }
#define     color_gray_58                 { 0.580392157f, 0.580392157f, 0.580392157 }
#define     color_gray_57                 { 0.568627451f, 0.568627451f, 0.568627451 }
#define     color_gray_56                 { 0.560784314f, 0.560784314f, 0.560784314 }
#define     color_gray_55                 { 0.549019608f, 0.549019608f, 0.549019608 }
#define     color_gray_54                 { 0.541176471f, 0.541176471f, 0.541176471 }
#define     color_gray_53                 { 0.529411765f, 0.529411765f, 0.529411765 }
#define     color_gray_52                 { 0.521568627f, 0.521568627f, 0.521568627 }
#define     color_gray_51                 { 0.509803922f, 0.509803922f, 0.509803922 }
#define     color_gray_50                 { 0.498039216f, 0.498039216f, 0.498039216 }
#define     color_gray_49                 { 0.490196078f, 0.490196078f, 0.490196078 }
#define     color_gray_48                 { 0.478431373f, 0.478431373f, 0.478431373 }
#define     color_gray_47                 { 0.470588235f, 0.470588235f, 0.470588235 }
#define     color_gray_46                 { 0.458823529f, 0.458823529f, 0.458823529 }
#define     color_gray_45                 { 0.450980392f, 0.450980392f, 0.450980392 }
#define     color_gray_44                 { 0.439215686f, 0.439215686f, 0.439215686 }
#define     color_gray_43                 { 0.431372549f, 0.431372549f, 0.431372549 }
#define     color_gray_42                 { 0.419607843f, 0.419607843f, 0.419607843 }
#define     color_gray_40                 { 0.4f, 0.4f, 0.4 }
#define     color_gray_39                 { 0.388235294f, 0.388235294f, 0.388235294 }
#define     color_gray_38                 { 0.380392157f, 0.380392157f, 0.380392157 }
#define     color_gray_37                 { 0.368627451f, 0.368627451f, 0.368627451 }
#define     color_gray_36                 { 0.360784314f, 0.360784314f, 0.360784314 }
#define     color_gray_35                 { 0.349019608f, 0.349019608f, 0.349019608 }
#define     color_gray_34                 { 0.341176471f, 0.341176471f, 0.341176471 }
#define     color_gray_33                 { 0.329411765f, 0.329411765f, 0.329411765 }
#define     color_gray_32                 { 0.321568627f, 0.321568627f, 0.321568627 }
#define     color_gray_31                 { 0.309803922f, 0.309803922f, 0.309803922 }
#define     color_gray_30                 { 0.301960784f, 0.301960784f, 0.301960784 }
#define     color_gray_29                 { 0.290196078f, 0.290196078f, 0.290196078 }
#define     color_gray_28                 { 0.278431373f, 0.278431373f, 0.278431373 }
#define     color_gray_27                 { 0.270588235f, 0.270588235f, 0.270588235 }
#define     color_gray_26                 { 0.258823529f, 0.258823529f, 0.258823529 }
#define     color_gray_25                 { 0.250980392f, 0.250980392f, 0.250980392 }
#define     color_gray_24                 { 0.239215686f, 0.239215686f, 0.239215686 }
#define     color_gray_23                 { 0.231372549f, 0.231372549f, 0.231372549 }
#define     color_gray_22                 { 0.219607843f, 0.219607843f, 0.219607843 }
#define     color_gray_21                 { 0.211764706f, 0.211764706f, 0.211764706 }
#define     color_gray_20                 { 0.2f, 0.2f, 0.2 }
#define     color_gray_19                 { 0.188235294f, 0.188235294f, 0.188235294 }
#define     color_gray_18                 { 0.180392157f, 0.180392157f, 0.180392157 }
#define     color_gray_17                 { 0.168627451f, 0.168627451f, 0.168627451 }
#define     color_gray_16                 { 0.160784314f, 0.160784314f, 0.160784314 }
#define     color_gray_15                 { 0.149019608f, 0.149019608f, 0.149019608 }
#define     color_gray_14                 { 0.141176471f, 0.141176471f, 0.141176471 }
#define     color_gray_13                 { 0.129411765f, 0.129411765f, 0.129411765 }
#define     color_gray_12                 { 0.121568627f, 0.121568627f, 0.121568627 }
#define     color_gray_11                 { 0.109803922f, 0.109803922f, 0.109803922 }
#define     color_gray_10                 { 0.101960784f, 0.101960784f, 0.101960784 }
#define     color_gray_9                  { 0.090196078f, 0.090196078f, 0.090196078 }
#define     color_gray_8                  { 0.078431373f, 0.078431373f, 0.078431373 }
#define     color_gray_7                  { 0.070588235f, 0.070588235f, 0.070588235 }
#define     color_gray_6                  { 0.058823529f, 0.058823529f, 0.058823529 }
#define     color_gray_5                  { 0.050980392f, 0.050980392f, 0.050980392 }
#define     color_gray_4                  { 0.039215686f, 0.039215686f, 0.039215686 }
#define     color_gray_3                  { 0.031372549f, 0.031372549f, 0.031372549 }
#define     color_gray_2                  { 0.019607843f, 0.019607843f, 0.019607843 }
#define     color_gray_1                  { 0.011764706f, 0.011764706f, 0.011764706 }