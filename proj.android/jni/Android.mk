LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game2048_shared

LOCAL_MODULE_FILENAME := libgame2048

LOCAL_SRC_FILES := game2048/main.cpp \
                   ../../Classes/AppDelegate.cpp \
	           ../../Classes/Config.cpp \
	           ../../Classes/LayerBack.cpp \
		   ../../Classes/LayerGameOver.cpp \
		   ../../Classes/LayerOptions.cpp \
		   ../../Classes/LayerWin.cpp \
		   ../../Classes/ModelDialog.cpp \
		   ../../Classes/NumberCell.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)

