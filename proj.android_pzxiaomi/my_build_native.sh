#!/bin/sh

# my_build_native.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ANDROID_ROOT="$DIR"

rm -rf "$APP_ANDROID_ROOT"/assets
rm -rf "$APP_ANDROID_ROOT"/libs/armeabi
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
echo ""
else
mkdir "$APP_ANDROID_ROOT"/assets
fi

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/assets        "$APP_ANDROID_ROOT"

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/libs/armeabi        "$APP_ANDROID_ROOT"/libs

#file="$APP_ANDROID_ROOT"/../armeabilibs/MM/assets/mmbilling.3.1.8.jar.protected.jar
#if [ -f "$file" ]; then
#cp "$file" "$APP_ANDROID_ROOT"/assets
#fi

rm -rf "$APP_ANDROID_ROOT"/assets/icon  # 移除图标素材素材
rm -rf "$APP_ANDROID_ROOT"/assets/csb/longbao
rm -rf "$APP_ANDROID_ROOT"/assets/pic/longbao