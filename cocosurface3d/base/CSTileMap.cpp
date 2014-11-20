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
#include "CSUndoManager.h"
#include "CSSpriteBatchNode.h"

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
	_tileBatchNode = CSSpriteBatchNode::create(filename);
	auto sprite = Sprite::create(filename);
	auto tags = _tileBatchNode->getChildrenCount();
	_tileBatchNode->addChild(sprite, tags, tags);
	addChild(_tileBatchNode);


	CSUndoInfo *info = new CSUndoInfo();
	info->actionType = actionType_addMapImage;
	info->_target = this;
	info->objectList.push_back(sprite);
	CSUndoManager::getInstance()->Execute(info);

	return true;
}



void CSTileMap::Undo(CSUndoInfo *info)
{
	switch (info->actionType)
	{
	case actionType_addMapImage:
		{
			auto sprite = dynamic_cast<Sprite *>(*info->objectList.begin());
			sprite->retain();
			if(sprite)
				sprite->removeFromParent();
		}
		break;
	default:
		break;
	}
}
void CSTileMap::Redo(CSUndoInfo *info)
{
	switch (info->actionType)
	{
	case actionType_addMapImage:
		{
			auto sprite = dynamic_cast<Sprite *>(*info->objectList.begin());
			if(sprite)
				_tileBatchNode->addChild(sprite);
		}
		break;
	default:
		break;
	}
}
void CSTileMap::clearRedoItem(CSUndoInfo *info)
{
	switch (info->actionType)
	{
	case actionType_addMapImage:
		{
			//release object;
			auto sprite = dynamic_cast<Sprite *>(*info->objectList.begin());
			if(sprite)
				sprite->release();
		}
		break;
	default:
		break;
	}
}

NS_CS_END
