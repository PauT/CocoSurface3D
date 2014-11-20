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

class CSUndoItem;
struct CSUndoInfo {
	//actor type
	UndoType				actionType;
	//object info
	std::vector<Ref *>		objectList;
	/** undo list */
	CSUndoItem				*_target;
};

class CSUndoItem
{
public:
	virtual void Undo(CSUndoInfo *info) = 0;
	virtual void Redo(CSUndoInfo *info) = 0;
};

class CS_DLL CSUndoManager : public Node
{
public:
	CSUndoManager();
	~CSUndoManager();

	/** undo */
	void Undo();
	/** redo */
	void Redo();
	/** execute */
	void Execute(CSUndoInfo *info);

	/** singleton */
	static CSUndoManager *getInstance();
protected:
	/** undo redo list */
	std::vector<CSUndoInfo *> m_undoList;
	std::vector<CSUndoInfo *> m_redoList;
	void clearUndoList();
	void clearRedoList();


	
};

NS_CS_END
#endif