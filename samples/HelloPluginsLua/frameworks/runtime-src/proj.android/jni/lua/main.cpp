#include <memory>

#include <android/log.h>
#include <jni.h>

#include "platform/android/PluginJniHelper.h"

#include "AppDelegate.h"
#include "ConfigParser.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

namespace {
std::unique_ptr<AppDelegate> appDelegate;
}

void cocos_android_app_init(JNIEnv* env) {
    LOGD("cocos_android_app_init");
    appDelegate.reset(new AppDelegate());
    JavaVM* vm;
    env->GetJavaVM(&vm);
    PluginJniHelper::setJavaVM(vm);
}


extern "C"
{
    bool Java_org_cocos2dx_HelloPluginsLua_AppActivity_nativeIsLandScape(JNIEnv *env, jobject thisz)
    {
        if (!ConfigParser::getInstance()->isInit())
        {
            ConfigParser::getInstance()->readConfig();
        }
        return ConfigParser::getInstance()->isLanscape();
    }

    bool Java_org_cocos2dx_HelloPluginsLua_AppActivity_nativeIsDebug(JNIEnv *env, jobject thisz)
    {
        #ifdef NDEBUG
            return false;
        #else
            return true;
        #endif
    }
}
