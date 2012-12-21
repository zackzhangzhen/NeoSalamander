#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__


#include "layer/ScriptLayer.h"
#include "cocos2d.h"
#include "CCEGLView.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "layer/BgLayer.h";
#include "utility/Utility.h"
#include "sprite/ZSprite.h"
#include "layer/ObjectLayer.h"
#include "synchronization\GlobalFlag.h"
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif  // __APP_DELEGATE_H__

