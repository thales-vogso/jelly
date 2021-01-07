#!/bin/sh

# my_build_native.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ANDROID_ROOT="$DIR"


#if [ -d "$APP_ANDROID_ROOT"/libs/armeabi-v7a ]; then
#echo ""
#else
#mkdir "$APP_ANDROID_ROOT"/libs/armeabi-v7a
#fi

#file="$APP_ANDROID_ROOT"/libs/armeabi/libcocos2dcpp.so
#if [ -f "$file" ]; then
#cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi-v7a
#fi


rm -rf "$APP_ANDROID_ROOT"/assets/icon  # 移除图标素材素材
rm -rf "$APP_ANDROID_ROOT"/assets/csb/longbao
rm -rf "$APP_ANDROID_ROOT"/assets/pic/longbao