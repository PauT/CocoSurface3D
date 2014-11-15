#ifndef __IACTION_H__
#define __IACTION_H__
#include "cocos2d.h"
#include "../platform/CSPlatformMacros.h"

USING_NS_CC;

NS_CS_BEGIN

enum UndoType {
	actionType_none = 0,
	actionType_addMapImage,
};

class CSUndoInfo
{
public:
	CSUndoInfo(){}
	~CSUndoInfo(){}

	//Action类型
	UndoType				actionType;
	//多个object所需
	std::vector<CCObject *> objectList;
	//
	int						objectId;


	virtual void  dosomething(){}
};

class CSUndoManager : public CCNode
{
public:
	CSUndoManager();
	~CSUndoManager();

	

protected:
	std::vector<CSUndoInfo *> m_undoList;
	std::vector<CSUndoInfo *> m_redoList;

	static CSUndoManager *sharedIAction();
};

NS_CS_END
#endif