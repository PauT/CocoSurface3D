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
:_isEditMode(false),
_cameraRotateMode(CAMERA_ROTATE_NONE),
m_camera3d(nullptr)
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
	auto layer3D = CSLayer::create(cocos2d::ccc4(0,255,0,255));
	_layer3D = layer3D;
	addChild(_layer3D, 0);
	_layer3D->setPosition3D(Vec3(50,0,-20));
	resetCamera();

	auto layer3DChild1 = CSLayer::create(cocos2d::ccc4(255,0,0,255));
	_layer3D->addChild(layer3DChild1, 0);
	layer3DChild1->setPosition3D(Vec3(0,0,0));

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(CSScene::onKeyDown, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(CSScene::onKeyUp, this);

	auto touchListener = cocos2d::EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesMoved = CC_CALLBACK_2(CSScene::onTouchesMoved, this);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(CSScene::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	return true;
}

/** init camera */
void CSScene::resetCamera()
{
	if(_isEditMode)
	{
		if(m_camera3d)
			m_camera3d->removeFromParent();
		auto s = Director::getInstance()->getWinSize();
		float zeye = Director::getInstance()->getZEye() + 100;
		auto camera = cocos2d::Camera::createPerspective(60, (GLfloat)s.width / s.height, 10, zeye + s.height/* / 2.0f*/);
		Vec3 eye(s.width/2, s.height/2.0f, zeye), center(s.width/2, s.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
		camera->setPosition3D(eye);
		camera->lookAt(center, up);
		m_camera3d = camera;
		_layer3D->addChild(m_camera3d);
	} else 
	{
		if(m_camera3d)
			m_camera3d->removeFromParent();
		auto camera = cocos2d::Camera::create();
		m_camera3d = camera;
		_layer3D->addChild(m_camera3d);
	}
}
/** touch move*/
void CSScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event)
{
	if(touches.size()==1 && _isEditMode)
	{
		auto touch = touches[0];
		auto location = touch->getLocation();
		auto PreviousLocation = touch->getPreviousLocation();
		Point newPos = PreviousLocation - location;

		if(_cameraRotateMode == CAMERA_ROTATE_XY)
		{
			Vec3  rotation3D= m_camera3d->getRotation3D();
			rotation3D.x+= newPos.y*0.1;
			rotation3D.y+= newPos.x*0.1;
			m_camera3d->setRotation3D(rotation3D);
		} else if(_cameraRotateMode == CAMERA_TRANSLATE_XY)
		{
			Vec3 cameraPos=  m_camera3d->getPosition3D();
			cameraPos.x+=newPos.x*0.5;
			cameraPos.y+=newPos.y*0.5;
			m_camera3d->setPosition3D(cameraPos);   
		}
		   
	}
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
/** windows event */
void CSScene::onKeyDown (EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_E:
		// edit mode switch 
		_isEditMode = !_isEditMode;
		resetCamera();
		break;
	case EventKeyboard::KeyCode::KEY_R:
		// reset camera
		if(_cameraRotateMode != CAMERA_ROTATE_NONE)
			resetCamera();
		break;
	case EventKeyboard::KeyCode::KEY_CTRL:
		// switch camera to rotate mode
		_cameraRotateMode = CAMERA_ROTATE_XY;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		// switch camera to rotate mode
		_cameraRotateMode = CAMERA_TRANSLATE_XY;
		break;
	}
}
void CSScene::onKeyUp(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_CTRL:
		_cameraRotateMode = CAMERA_ROTATE_NONE;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		_cameraRotateMode = CAMERA_ROTATE_NONE;
		break;
	}
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
	if(_isEditMode)
	{
		EventMouse* e = (EventMouse*)event;
		float ey = e->getScrollY();
		Vec3 cameraPos=  m_camera3d->getPosition3D();
		cameraPos.z+=ey * 10;
		m_camera3d->setPosition3D(cameraPos);
	}
	
}
#endif

NS_CS_END
