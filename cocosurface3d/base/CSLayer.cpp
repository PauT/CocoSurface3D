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
#include "CSTileMap.h"

USING_NS_CC;

NS_CS_BEGIN

// Layer
CSLayer::CSLayer()
:_showAxis(false)
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));

	

	_drawAxis = DrawNode3D::create();
	addChild(_drawAxis, 0);
	scheduleUpdate();
	
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

void CSLayer::update(float dt)
{
	if(_showAxis && _drawAxis != nullptr)
	{
		_drawAxis->clear();
		glLineWidth(5.0);
		_drawAxis->drawLine(Vec3(-getContentSize().width,0, 0), Vec3(getContentSize().width, 0, 0), Color4F(1,0,0,1) );
		_drawAxis->drawLine(Vec3(0,-getContentSize().height, 0), Vec3(0,getContentSize().height, 0), Color4F(0,1,0,1) );
		_drawAxis->drawLine(Vec3(0,0,-1000), Vec3(0,0,1000) , Color4F(0,0,1,1) );
	}
}




// add tile map with image
void CSLayer::addCSTileMapWithImage(std::string filename)
{
	auto tilemap = CSTileMap::create(filename);
	addChild(tilemap, 1);
}

NS_CS_END
