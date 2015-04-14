#include "AppDelegate.h"
#include "Game/GameScene.h"

USING_NS_CC;


//---------------------------------------------------------------------//
AppDelegate::AppDelegate() {

}
//---------------------------------------------------------------------//
AppDelegate::~AppDelegate() 
{
}
//---------------------------------------------------------------------//
void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs attr = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(attr);
}
//---------------------------------------------------------------------//
bool AppDelegate::applicationDidFinishLaunching() {

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Defence");

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		glview->setFrameSize(1280, 720);
		#endif


        director->setOpenGLView(glview);
    }


    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	auto scene = GameScene::create();

    // run
    director->runWithScene(scene);

    return true;
}
//---------------------------------------------------------------------//
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
//---------------------------------------------------------------------//
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
