#pragma once

#include "GEinput.h"
#include "GEanimatedmodel.h"
#include "GEplane.h"
#include "GEsphere.h"
#include "GEcube.h"
#include "GEscene.h"

class GMMain : public GEUpdateProtocol, public GERenderProtocol, public GEInputXBoxControllerProtocol, public GEInputMouseProtocol
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GMMain* sharedInstance();
private:
	GMMain();
	GMMain(GMMain const&) = delete;
	void operator=(GMMain const&) = delete;

	// -------------------------------------------- //
	// --------- Update - Render - Layout --------- //
	// -------------------------------------------- //
public:
	void preUpdate();
	void update(float time);
	void posUpdate();
	void render();
	void layout(int width, int height);


	// -------------------------------------------- //
	// ---------- Xbox Controller Events ---------- //
	// -------------------------------------------- //
public:
	void xBoxControllerButtonDown(GE_INPUT_XBOX button, int player);
	void xBoxControllerButtonUp(GE_INPUT_XBOX button, int player);
	void xBoxControllerTriguerChange(GE_INPUT_XBOX trigger, int player, float value);
	void xBoxControllerStickChange(GE_INPUT_XBOX stick, int player, float xAxis, float yAxis);

	// -------------------------------------------- //
	// ---------------- Mouse Events -------------- //
	// -------------------------------------------- //
public:
	void mouseMove(float coordX, float coordY);
	void mouseChange(float deltaX, float deltaY);

	// -------------------------------------------- //
	// -------------- Private Members ------------- //
	// -------------------------------------------- //
private:
	unsigned int m_screenWidth, m_screenHeight;

	GELight* light;
	GEAnimation* animation;
	GEAnimatedModel* player;
	GESphere* earth;
	GECube* cubes[200];

	GEScene* view;

	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;


	btCollisionShape* earthShape;
	btRigidBody* earthRigidBody;

	btCollisionShape* boxshape;
	btRigidBody* boxRigidBodies[200];

	btCollisionShape* playerShape;
	btRigidBody* playerRigidBody;
};
