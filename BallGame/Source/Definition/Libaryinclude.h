#pragma once

#include <comutil.h>
#include <ShellAPI.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <TurboircXml/XML.h>
#include <TurboircXml/mime.h>

#include <Bullet/Include/btBulletCollisionCommon.h>
#include <Bullet/Include/btBulletDynamicsCommon.h>
#include <Bullet/Include/BulletCollision/CollisionDispatch/btGhostObject.h>

#pragma comment(lib, "d3d9.lib")

#include <Audiere/include/audiere.h>
#pragma comment(lib, "Lib/Audiere/audiere.lib")

#ifdef _DEBUG
#pragma comment(lib, "comsuppd.lib")
#pragma comment(lib, "comsuppwd.lib")
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "Lib/Bullet/Debug/BulletCollision.lib")
#pragma comment(lib, "Lib/Bullet/Debug/BulletDynamics.lib")
#pragma comment(lib, "Lib/Bullet/Debug/LinearMath.lib")
#pragma comment(lib, "Lib/Bullet/Debug/BulletMultiThreaded.lib")
#else
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Lib/Bullet/Release/BulletCollision.lib")
#pragma comment(lib, "Lib/Bullet/Release/BulletDynamics.lib")
#pragma comment(lib, "Lib/Bullet/Release/LinearMath.lib")
#pragma comment(lib, "Lib/Bullet/Release/BulletMultiThreaded.lib")
#endif


