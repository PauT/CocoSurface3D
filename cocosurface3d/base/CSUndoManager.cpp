#include "CSUndoManager.h"

NS_CS_BEGIN
CSUndoManager::CSUndoManager()
{

}
CSUndoManager::~CSUndoManager()
{

}

void CSUndoManager::Undo()
{
	if( m_undoList.size() == 0 )
		return;

	auto info = m_undoList.end() - 1;

	auto target = dynamic_cast<CSUndoItem *>((*info)->_target);

	if(target != nullptr)
		target->Undo((*info));

	m_undoList.erase(info);
}
void CSUndoManager::Redo()
{
	if( m_redoList.size() == 0 )
		return;

	auto info = m_redoList.end() - 1;

	auto target = dynamic_cast<CSUndoItem *>((*info)->_target);

	if(target != nullptr)
		target->Redo((*info));

	m_redoList.erase(info);
}
void CSUndoManager::Execute(CSUndoInfo *info)
{
	m_undoList.push_back(info);
	clearRedoList();
}

void CSUndoManager::clearUndoList()
{

}
void CSUndoManager::clearRedoList()
{
	//没释放完全,隐患待处理

	m_redoList.clear();
}

// singleton stuff
static CSUndoManager *s_SharedCSUndoManager = nullptr;

CSUndoManager* CSUndoManager::getInstance()
{
	if (!s_SharedCSUndoManager)
	{
		s_SharedCSUndoManager = new (std::nothrow) CSUndoManager();
		CCASSERT(s_SharedCSUndoManager, "FATAL: Not enough memory");
		s_SharedCSUndoManager->init();
	}

	return s_SharedCSUndoManager;
}
NS_CS_END
