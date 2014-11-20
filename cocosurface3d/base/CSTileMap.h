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

#ifndef __CSTILEMAP_H__
#define __CSTILEMAP_H__

#include "cocos2d.h"
#include "../platform/CSPlatformMacros.h"
#include "CSUndoManager.h"

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
class CS_DLL CSTileMap : public cocos2d::CCLayer, public CSUndoItem
{
public:    
    /** creates a fullscreen black layer */
    static CSTileMap *create();
	/** creates a Layer with color. Width and height are the window size. */
	static CSTileMap * create(std::string filename);
	/** creates a Layer with color, width and height in Points */
	static CSTileMap * create(std::string filename, GLfloat width, GLfloat height);
    
    CSTileMap();
    virtual ~CSTileMap();

    virtual bool init() override;
	/** init with image */
	bool	initWithImage(std::string filename);
	/** init with image */
	bool	initWithImage(std::string filename, GLfloat width, GLfloat height);
	/** undo add map */
	void	undoAddWithImage();
protected:
	CC_SYNTHESIZE(SpriteBatchNode *, _tileBatchNode, TileBatchNode);

	virtual void Undo(CSUndoInfo *info);
	virtual void Redo(CSUndoInfo *info);
};

// end of layer group
/// @}

NS_CS_END

#endif // __CSLAYER_H__

