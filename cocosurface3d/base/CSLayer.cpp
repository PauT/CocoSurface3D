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

#include <stdarg.h>
#include "CSLayer.h"

NS_CS_BEGIN

// Layer
CSLayer::CSLayer()
:_showAxis(false)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

CSLayer::~CSLayer()
{

}

bool CSLayer::init()
{
	CCLayerColor::init();
    Director * director = Director::getInstance();
    setContentSize(director->getWinSize());
    return true;
}

CSLayer *CSLayer::create()
{
    CSLayer *ret = new (std::nothrow) CSLayer();
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

CSLayer *CSLayer::create(const Color4B& color)
{
	CSLayer * layer = new (std::nothrow) CSLayer();
	if(layer && layer->initWithColor(color))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

CSLayer *CSLayer::create(const Color4B& color, GLfloat width, GLfloat height)
{
	CSLayer * layer = new (std::nothrow) CSLayer();
	if(layer && layer->initWithColor(color, width, height))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void CSLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	
	if(_showAxis)
	{
		// draw coordinate axis
		_customCommand.init(_globalZOrder);
		_customCommand.func = CC_CALLBACK_0(CSLayer::onDraw, this, transform, flags);
		renderer->addCommand(&_customCommand);
	}
	cocos2d::CCLayerColor::draw(renderer, transform, flags);
}
void CSLayer::onDraw(const Mat4 &transform, uint32_t flags)
{
	cocos2d::Director* director = cocos2d::Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	// draw coordinate axis
	glLineWidth( 5.0f );
	cocos2d::DrawPrimitives::setDrawColor4B(255,0,0,255);
	cocos2d::DrawPrimitives::drawLine3D( Vec3(-getContentSize().width,0, 0), Vec3(getContentSize().width, 0, 0) );

	glLineWidth( 5.0f );
	cocos2d::DrawPrimitives::setDrawColor4B(0,255,0,255);
	cocos2d::DrawPrimitives::drawLine3D( Vec3(0,-getContentSize().height, 0), Vec3(0,getContentSize().height, 0) );

	glLineWidth( 5.0f );
	cocos2d::DrawPrimitives::setDrawColor4B(0,0,255,255);
	cocos2d::DrawPrimitives::drawLine3D( Vec3(0,0,-1000), Vec3(0,0,1000) );

	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}


NS_CS_END
