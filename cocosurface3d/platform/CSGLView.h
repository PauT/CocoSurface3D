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

#ifndef __CSGLVIEW_H__
#define __CSGLVIEW_H__

#include "CSPlatformMacros.h"
#include "base/ccTypes.h"
//#include "base/CCEventTouch.h"
#include "platform/CCGLView.h"
#include "cocos2d.h"

#include <vector>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
typedef void* id;
#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) */





NS_CS_BEGIN

/**
 * @addtogroup platform
 * @{
 */
class CS_DLL CSGLView : public cocos2d::GLView
{
public:
    /**
     * @js ctor
     */
	CSGLView() {};
    
};

// end of platform group
/// @}

NS_CS_END

#endif /* __CCGLVIEW_H__ */
