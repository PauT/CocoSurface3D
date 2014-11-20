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

#ifndef __CSSPRITEBATCHNODE_H__
#define __CSSPRITEBATCHNODE_H__

#include "cocos2d.h"
#include "../platform/CSPlatformMacros.h"

USING_NS_CC;

NS_CS_BEGIN

//
// Layer
//
/** @brief Layer is a subclass of Node that implements the TouchEventsDelegate protocol.

All features from Node are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CS_DLL CSSpriteBatchNode : public cocos2d::SpriteBatchNode
{
public:    
	/** creates a SpriteBatchNode with a file image (.png, .jpeg, .pvr, etc) and capacity of children.
     The capacity will be increased in 33% in runtime if it run out of space.
     The file will be loaded using the TextureMgr.
     */
    static CSSpriteBatchNode* create(const std::string& fileImage, ssize_t capacity = 29);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
protected:
	DepthBatchCommand _customCommand;
	void onDraw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
};

// end of layer group
/// @}

NS_CS_END

#endif // __CSLAYER_H__

