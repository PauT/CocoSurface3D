/****************************************************************************
Copyright (c) 2014 PauT

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

#ifndef __CSSCENE_H__
#define __CSSCENE_H__

#include <string>
#include "../platform/CSPlatformMacros.h"
#include "cocos2d.h"
USING_NS_CC;

NS_CS_BEGIN

class Camera;
class BaseLight;
class Renderer;
class EventListenerCustom;
class EventCustom;
#if CC_USE_PHYSICS
class PhysicsWorld;
#endif
/**
 * @addtogroup scene
 * @{
 */

/** @brief Scene is a subclass of Node that is used only as an abstract concept.

Scene and Node are almost identical with the difference that Scene has its
anchor point (by default) at the center of the screen.

For the moment Scene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use a Scene as the parent of all your nodes.
*/
class CSLayer;
class CS_DLL CSScene : public Scene
{
public:
    /** creates a new Scene object */
    static CSScene *create();

    /** creates a new Scene object with a predefined Size */
    static CSScene *createWithSize(const Size& size);

	/** init scene */
	virtual bool init();
	/** init scene */
	bool initWithSize(const Size& size);
    
CC_CONSTRUCTOR_ACCESS:
    CSScene();
    virtual ~CSScene();

protected:
	/** cslayer list */
	CC_SYNTHESIZE(CSLayer*, _layer3D, Layer3D);
	/** edit mode switch */
	CC_SYNTHESIZE(bool, _isEditMode, EditMode);
	/** look at point */
	CC_SYNTHESIZE(Vec3, _lookAtCenter, LookAt);

	/** rotate camera mode */
	enum CAMERA_MODE{
		CAMERA_NONE = 0,
		CAMERA_MOVE_MODE,
	};
	CC_SYNTHESIZE(CAMERA_MODE, _cameraRotateMode, CameraRotateMode);
	/** init camera */
	void resetCamera();

	CC_SYNTHESIZE(Ref*, _curSelect, CurSelect);

	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, Event* event);
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

	#define KEY_CTRL_DOWN		0x01
	#define KEY_ALT_DOWN		0x10
	int	 _keyboardState;
	/** windows event */
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyUp(EventKeyboard::KeyCode keyCode, Event* event);

	/** is mouse right button down */
	bool _isMouseRightButtonDown;
	Vec2 _previousMBRLoaction;

	void onMouseDown(Event* event);
	void onMouseUp(Event* event);
	void onMouseMove(Event* event);
	void onMouseScroll(Event* event);
#endif
public:
	CC_SYNTHESIZE(cocos2d::Camera*, m_camera3d, Camera);
private:
    CC_DISALLOW_COPY_AND_ASSIGN(CSScene);

};

// end of scene group
/// @}

NS_CS_END

#endif // __CCSCENE_H__
