LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Game/GameManager.cpp \
                   ../../Classes/Game/GameScene.cpp \
                   ../../Classes/Game/Entity/Edge.cpp \
                   ../../Classes/Game/Entity/Entity.cpp \
                   ../../Classes/Game/Entity/EntityManager.cpp \
                   ../../Classes/Game/Entity/Packet.cpp \
                   ../../Classes/Game/Entity/Tower.cpp \
                   ../../Classes/Game/Layer/BackgroundLayer.cpp \
                   ../../Classes/Game/Layer/GameLayer.cpp \
                   ../../Classes/Game/Layer/GUILayer.cpp \
                   ../../Classes/Game/Level/Level.cpp \
                   ../../Classes/Game/Level/LevelManager.cpp \
                   ../../Classes/Game/Level/RandomTreeLevel.cpp \
                   ../../Classes/Util/Util.cpp \



LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
