
// C++ includes
#include <map>
#include <functional>
#include <string>
#include <chrono>
#include <thread>
// test inclues
#include "CS3DTestScene.h"

CS3DTestScene::CS3DTestScene()
{

}

CS3DTestScene::~CS3DTestScene()
{

}

void CS3DTestScene::runThisTest()
{
	this->init();
	Director::getInstance()->replaceScene(this);
}
