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
#include "CSTileMap.h"

NS_CS_BEGIN

// Layer
CSTileMap::CSTileMap()
{
    _ignoreAnchorPointForPosition = true;
    setAnchorPoint(Vec2(0.5f, 0.5f));
}

CSTileMap::~CSTileMap()
{

}

bool CSTileMap::init()
{
	CCLayer::init();
    Director * director = Director::getInstance();
    setContentSize(director->getWinSize());
    return true;
}

CSTileMap *CSTileMap::create()
{
    CSTileMap *ret = new (std::nothrow) CSTileMap();
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

CSTileMap *CSTileMap::create(std::string filename)
{
	CSTileMap * layer = new (std::nothrow) CSTileMap();
	if(layer && layer->initWithImage(filename))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

CSTileMap *CSTileMap::create(std::string filename, GLfloat width, GLfloat height)
{
	CSTileMap * layer = new (std::nothrow) CSTileMap();
	if(layer && layer->initWithImage(filename, width, height))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool CSTileMap::initWithImage(std::string filename)
{
	Size s = Director::getInstance()->getWinSize();
	return initWithImage(filename, s.width, s.height);
}
bool CSTileMap::initWithImage(std::string filename, GLfloat width, GLfloat height)
{
	_tileBatchNode = SpriteBatchNode::create(filename, 50);
	addChild(_tileBatchNode);
	return true;
}

NS_CS_END