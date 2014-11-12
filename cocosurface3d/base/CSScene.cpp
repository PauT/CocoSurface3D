/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CSScene.h"
#include "CSLayer.h"
USING_NS_CC;
NS_CS_BEGIN

CSScene::CSScene()
:_isEditMode(false)
{
}

CSScene::~CSScene()
{

}


CSScene* CSScene::create()
{
    CSScene *ret = new (std::nothrow) CSScene();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

CSScene* CSScene::createWithSize(const Size& size)
{
    CSScene *ret = new (std::nothrow) CSScene();
    if (ret && ret->initWithSize(size))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

/** init scene */
bool CSScene::init()
{
	Scene::init();

	/** test part need remove*/
	auto layer3D = CSLayer::create();
	addChild(layer3D, 0);
	layer3D->setPosition3D(Vec3(0,0, 0));

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(CSScene::onKeyDown, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(CSScene::onKeyUp, this);

	auto touchListener = cocos2d::EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesMoved = CC_CALLBACK_2(CSScene::onTouchesMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

/** init camera */
void CSScene::resetCamera()
{
	if(_isEditMode)
	{
		_defaultCamera->removeFromParent();
		auto s = Director::getInstance()->getWinSize();
		float zeye = Director::getInstance()->getZEye() + 100;
		auto camera = cocos2d::Camera::createPerspective(60, (GLfloat)s.width / s.height, 10, zeye + s.height / 2.0f);
		Vec3 eye(s.width/2, s.height/2.0f, zeye), center(s.width/2, s.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
		camera->setPosition3D(eye);
		camera->lookAt(center, up);
		_defaultCamera = camera;
		addChild(_defaultCamera);
	} else 
	{
		_defaultCamera->removeFromParent();
		auto camera = cocos2d::Camera::create();
		_defaultCamera = camera;
		addChild(_defaultCamera);
	}
}

void CSScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	if(touches.size()==1 && _isEditMode)
	{
		auto touch = touches[0];
		auto location = touch->getLocation();
		auto PreviousLocation = touch->getPreviousLocation();
		Point newPos = PreviousLocation - location;

		Vec3 cameraDir;
		Vec3 cameraRightDir;
		_defaultCamera->getNodeToWorldTransform().getForwardVector(&cameraDir);
		cameraDir.normalize();
		cameraDir.y=0;
		_defaultCamera->getNodeToWorldTransform().getRightVector(&cameraRightDir);
		cameraRightDir.normalize();
		cameraRightDir.y=0;
		Vec3 cameraPos=  _defaultCamera->getPosition3D();
		cameraPos+=cameraDir*newPos.y*0.5;
		cameraPos+=cameraRightDir*newPos.x*0.5;
		_defaultCamera->setPosition3D(cameraPos);      
	}
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
/** windows event */
void CSScene::onKeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_E:
		_isEditMode = !_isEditMode;
		resetCamera();
		break;
	}
}
void CSScene::onKeyUp(EventKeyboard::KeyCode keyCode, Event* event)
{

}

void CSScene::onMouseDown(Event* event)
{

}
void CSScene::onMouseUp(Event* event)
{

}
void CSScene::onMouseMove(Event* event)
{

}
void CSScene::onMouseScroll(Event* event)
{

}
#endif

NS_CS_END
