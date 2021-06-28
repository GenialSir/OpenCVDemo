package com.genialsir.opencvdemo;

import android.graphics.Bitmap;

/**
 * @author genialsir@163.com (GenialSir) on 2021/6/22
 */
public class OpenCVAssistant {


    //open_cv_java Module会依赖open_jni中加载的opencv_java4的动态库。
    static {
        System.loadLibrary("opencv_jni");
    }


    public native String setDetectionAdapter(String path);

    public native void ctvColorFromJni(Bitmap srcBitmap, Bitmap grayBitmap);


}
