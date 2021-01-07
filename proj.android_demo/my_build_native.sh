#!/bin/sh

# my_build_native.sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ANDROID_ROOT="$DIR"


if [ -d "$APP_ANDROID_ROOT"/assets ]; then
echo ""
else
mkdir "$APP_ANDROID_ROOT"/assets
fi

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/assets        "$APP_ANDROID_ROOT"

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/libs/armeabi        "$APP_ANDROID_ROOT"/libs

if [ -d "$APP_ANDROID_ROOT"/libs/x86 ]; then
echo ""
else
mkdir "$APP_ANDROID_ROOT"/libs/x86
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/armeabi/libmegjb.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/x86/libmegjb.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/x86
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/AndGame.Sdk.Lib_20130_4E4DB8F73D48429B0A74BED2D59DC7A8.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/c_data_store.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/Charge.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/Config.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/ConsumeCodeInfo.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/d_data_store.dat.x86
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/d_data_store.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/libmegbpp_02.02.13_00.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/libmegjb.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/andGame/assets/libmegbpp_02.02.13_00.so.x86
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/armeabilibs/andGame/assets/CMGC        "$APP_ANDROID_ROOT"/assets




rm -rf "$APP_ANDROID_ROOT"/assets/icon  # 移除图标素材素材
rm -rf "$APP_ANDROID_ROOT"/assets/csb/longbao
rm -rf "$APP_ANDROID_ROOT"/assets/pic/longbao