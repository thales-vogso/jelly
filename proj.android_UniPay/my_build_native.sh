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

#if [ -d "$APP_ANDROID_ROOT"/libs/armeabi-v7a ]; then
#echo ""
#else
#mkdir "$APP_ANDROID_ROOT"/libs/armeabi-v7a
#fi



cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/assets        "$APP_ANDROID_ROOT"

cp -rf /Volumes/old/Users/wushuang/Desktop/Jelly/project/jelly3.5/proj.android/libs/armeabi        "$APP_ANDROID_ROOT"/libs

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/libmegjb.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/libsmsprotocol.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/libs/armeabi
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/AndGame.Sdk.Lib_.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/c_data_store.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/Charge.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/Config.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/ConsumeCodeInfo.xml
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/d_data_store.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/feeInfo.dat
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/libmegbpp_02.02.09_00.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi

file="$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/libmegbpp_02.02.09_00.so
if [ -f "$file" ]; then
cp "$file" "$APP_ANDROID_ROOT"/assets
fi


cp -rf "$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/CMGC        "$APP_ANDROID_ROOT"/assets
cp -rf "$APP_ANDROID_ROOT"/../armeabilibs/unipay/assets/unicom_base        "$APP_ANDROID_ROOT"/assets

rm -rf "$APP_ANDROID_ROOT"/assets/icon  # 移除图标素材素材
rm -rf "$APP_ANDROID_ROOT"/assets/csb/longbao
rm -rf "$APP_ANDROID_ROOT"/assets/pic/longbao