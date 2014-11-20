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

#ifndef __CSLAYER_H__
#define __CSLAYER_H__

#include "cocos2d.h"
#include "../platform/CSPlatformMacros.h"
#include "DrawNode3D.h"

USING_NS_CC;

NS_CS_BEGIN

/**
 * @addtogroup layer
 * @{
 */

class __Set;
class TouchScriptHandlerEntry;

class EventListenerTouch;
class EventListenerKeyboard;
class EventListenerAcceleration;

class Touch;

//
// Layer
//
/** @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CS_DLL CSLayer : public cocos2d::LayerColor
{
public:    
    /** creates a fullscreen black layer */
    static CSLayer *create();
	/** creates a Layer with color. Width and height are the window size. */
	static CSLayer * create(const Color4B& color);
	/** creates a Layer with color, width and height in Points */
	static CSLayer * create(const Color4B& color, GLfloat width, GLfloat height);
    
    CSLayer();
    virtual ~CSLayer();

    virtual bool init() override;

	// show axis
	CC_SYNTHESIZE(bool, _showAxis, ShowAxis);

	// add tile map with image
	void addCSTileMapWithImage(std::string filename);

	
	
protected:
	// draw coordinate axis
	DrawNode3D *_drawAxis;

	CustomCommand _customCommand;

	void update(float dt);
};

// end of layer group
/// @}

NS_CS_END

#endif // __CSLAYER_H__

