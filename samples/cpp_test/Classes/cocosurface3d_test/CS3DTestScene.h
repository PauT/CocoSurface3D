#ifndef _CS3D_TEST_SCENE_H_
#define _CS3D_TEST_SCENE_H_

#include "cocos2d.h"
#include "cocosurface3d.h"
#include "../testBasic.h"

USING_NS_CC;
USING_NS_CS;

class CS3DTestScene : public CSScene
{
public:
	CS3DTestScene();
	~CS3DTestScene();

	void runThisTest();
};

#endif
