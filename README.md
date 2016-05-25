Visualstuff Engine
===================

Visualstuff Engine it's  a small experimental 3D engine written in **C++** with an analog sister in Apple platforms written in **Objective-C**, it uses the graphics library **OpenGL** as its main render API.

I'm using VisualSudio 2015 community for easier development under windows platform, so be sure you have that version and the last video card drivers installed.

Installation
-------------
Ones you have the repository cloned you will need some dependencies to get the project running, all you need it's in this folder [Dependecies.zip](https://www.dropbox.com/s/5bah9tjomwc2gx8/Dependencies.rar?dl=0), this contains the next packages:
>- Bullet 2.83.6
>- DevIL-SDK-x86-1.7.8
>- freetype-2.6
>- glm-0.9.7.1

I recommend you unzip this packages in `C:\` since that's where the VisualStudio project is configured to look for them.

The next thing you have to add are the OpenGL extended functionality headers [glext.h](https://www.opengl.org/registry/api/GL/glext.h) and [wglext.h](https://www.opengl.org/registry/api/GL/wglext.h) normally they have to be placed in `C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl` or wherever the `GL.h` is located in your system. 

And that's it, that's all you need to get running the engine, as you can guess Visuastuff uses **Bullet Physics** a its main physics engine and **DevIL** is the library used to load image files from disk. **Freetype** is referenced to the project but its functionality isn't implemented yet. And the last one **GLM** provide the engine with all the 3D math and conventional math for all our matrix generation and space calculations.

----------
Getting started
-------------
The engine is composed of several feature, at first it can be a little scrambled but you can get used to them quickly. Next we will talk about how engine works and see how we can use its features. 

**Scenes and Objects**

A **Scene** Its he main repository of all the object you want to interact with each other and resulting in all of then drawn to the screen automatically

Create a new scene 
```c++
view = new GEScene();
view->BackgroundColor = color_banana;
view->Camera.Position = glm::vec3(0.0f, 30.0f, 30.0f);
view->Camera.Orientation = glm::vec3(-20.0f, 0.0f, 0.0f);
```
A scene has by default a camera object.

The base **3DObject** brings all the needed functionality to manipulate an entity in a **Scene** it can be **Renderable** to use a *vertex buffer* and start rendering it into the screen.

Create and add a new layer to the scene

```c++
GELayer* layer = view->addLayerWithName(L"Layer1");
```
An scene can contain a variety of **layers** and a 3D object can live there so you can control trough layers the **behavior** of a group of entities. 

----------
**Rendering**

Visualstuff uses the **forward rendering path** method with a **Blin Phong** generic shader.

> Included shaders:

> - **Color shader** for solid color objects.
> - **Depth shader** to get clean depth buffers.
> - **Full screen shader** for fast render a texture, covering the whole view.
> - **Texture shader** for sprites and not acclimated objects.

Internally objects will be rendered passing a render flag that will select which shader will be used. 

It also has a support for **off screen** rendering **FBO**, **cameras**, **lights** and **materials**.

```c++
// FBO
ShadowMapFBO = new GEFBO(ShadowMapSize, ShadowMapSize);
glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapFBO->FrameBufferID);
glViewport(0, 0, (ShadowMapFBO->Width, ShadowMapFBO->Height);

// Light
light = new GELight;
light->Intensity = 1.0f;
light->Ambient = 0.2f;
light->CastShadows = true;

// Camera
GECamera camera;
camera.Position = glm::vec3(0.0f, 30.0f, 30.0f);
camera.Orientation = glm::vec3(-20.0f, 0.0f, 0.0f);
```

----------
**Shadow mapping**

When a light has activated the shadow map it automatically  render a view from that light and pases the generated map shadow to the main render shader object for use to shade the covered areas. (This characteristic needs some improvements) and is also only contemplated **Directional Light**, will be added point and spot lights later.

----------
**Primitives**

There are included some dynamic primitive generators that can be used to use basic forms.

> Included dynamic primitives:

>- **Plane**
>- **Cube**
>- **Quad Sphere**

Set up a sphere:
```c++
GESphere* earth = new GESphere(20.0f, 12);
earth->Material.DiffuseColor = color_bisque_2;
earth->Material.Shininess = 128.0f;
earth->Wireframe = true;
earth->Material.DiffuseMap = GETexture::textureWithFileName(L"Resources/Images/earth.png");
earth->Material.SpecularMap = GETexture::textureWithFileName(L"Resources/Images/earth_specular.png");
earth->makeRigidBody(true);
layer->addObject(earth);
```
----------
**Meshes and Animations**

Visualstuff includes a MD5mesh and MD5anim file loader to include complex and animated entities in a scene.

```c++
GEAnimation* animation;
GEAnimatedModel* model;

animation = new GEAnimation(L"resources/models/bob lamp/bob_lamp.md5anim");

// This start the animation
animation->play();

model = new GEAnimatedModel(L"resources/models/bob lamp/bob_lamp.md5mesh");

// This will notify the model when the next animation frame is ready and will take effect on the model.
animation->addDelegate(model);

model->Position = glm::vec3(0.0f, 20.0f, 0.0f);
model->Scale = glm::vec3(0.1f, 0.1f, 0.1f);

layer->addObject(model);
```
----------
**Main Game File**

All the main logic can be placed in the `GEMain.cpp` file, you can setup everything up in the constructor and use the updating methods:

```c++
// Set logic here
void preUpdate();
void update(float time);
void posUpdate();
void render();
void layout(int width, int height);
```
----------
To Do
-------------

There is too much to improve, and add to this project but for now is a good place to start if you are looking for something where base your work or learn some graphics, maybe the next thing to do is try to implement the same functionality for DirectX and Vulkan.

Licence
-------------

Use it as you need.
