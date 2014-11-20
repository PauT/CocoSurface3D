#ifndef __CSDEVICE_H__
#define __CSDEVICE_H__

#include "../platform/CSPlatformMacros.h"
#include "cocos2d.h"

NS_CS_BEGIN
class CS_DLL CSDevice
{
public:
	static std::string openFileDialog();
};
NS_CS_END
#endif