#!/bin/sh

# my_build_native.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ANDROID_ROOT="$DIR"
TELECOM_ROOT="$APP_ROOT"/telecom

rm -rf "$APP_ANDROID_ROOT"/assets
rm -rf "$APP_ANDROID_ROOT"/libs/armeabi
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
echo ""
else
mkdir "$APP_ANDROID_ROOT"/assets
fi

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/assets        "$APP_ANDROID_ROOT"

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/libs/armeabi        "$APP_ANDROID_ROOT"/libs


file="$APP_ANDROID_ROOT"/../armeabilibs/egame/egame_sdk_egame_logo.png
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/feeInfo.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/mmpay.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/data.bin
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/armeabi/libegamepay_dr2.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/armeabi/libentryexstd.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/egame/armeabi/libypiap.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi


cp -rf "$APP_ANDROID_ROOT"/../armeabilibs/egame/egame        "$APP_ANDROID_ROOT"/assets


rm -rf "$APP_ANDROID_ROOT"/assets/icon  # 移除图标素材素材
rm -rf "$APP_ANDROID_ROOT"/assets/csb/longbao
rm -rf "$APP_ANDROID_ROOT"/assets/pic/longbao