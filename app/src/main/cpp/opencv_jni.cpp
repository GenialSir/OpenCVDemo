#include <jni.h>
#include <string>

#include "face_detector.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <android/bitmap.h>


using namespace std;
using namespace cv;
CascadeClassifier face_cascade_classifier;


void BitmapToMat(JNIEnv *pEnv, jobject src, Mat &mat);

void MatToBitmap(JNIEnv *pEnv, Mat &mat, jobject gray);

extern "C"
JNIEXPORT jstring
JNICALL
Java_com_genialsir_opencvdemo_OpenCVAssistant_setDetectionAdapter(JNIEnv *env, jobject thiz,
                                                                  jstring path) {
    std::string msg = "检测文件未找到";
    const char *adapter_path = env->GetStringUTFChars(path, 0);
    Mat mat;
//    face_cascade_classifier异常
//    if(!face_cascade_classifier.load(adapter_path)){
//        return env->NewStringUTF(msg.c_str());
//    }
    msg = "检测文件配置完毕" CV_VERSION;
    return env->NewStringUTF(msg.c_str());
}




extern "C"
JNIEXPORT void JNICALL
Java_com_genialsir_opencvdemo_OpenCVAssistant_ctvColorFromJni(JNIEnv *env, jobject thiz,
                                                              jobject src_bitmap,
                                                              jobject gray_bitmap) {
    Mat src_image_mat;
    BitmapToMat(env, src_bitmap, src_image_mat);
    Mat gray_image_mat;
    cv::cvtColor(src_image_mat, gray_image_mat, COLOR_RGB2GRAY);
    MatToBitmap(env, gray_image_mat, gray_bitmap);
}

/**
 * Mat参数为什么传入的地址值，为什么不传入地址变灰操作会出错？
 * &和*的具体区别
 * */
void BitmapToMat(JNIEnv *env, jobject bitmap, Mat &dst) {
    AndroidBitmapInfo android_bitmap_info;
    void *pixels = nullptr;

    try {
        CV_Assert(AndroidBitmap_getInfo(env, bitmap, &android_bitmap_info) >= 0);
        CV_Assert(android_bitmap_info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
                  android_bitmap_info.format == ANDROID_BITMAP_FORMAT_RGB_565);
        CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
        CV_Assert(pixels);
        dst.create(android_bitmap_info.height, android_bitmap_info.width, CV_8UC4);
        if (android_bitmap_info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
            // LOGD("nBitmapToMat: RGBA_8888 -> CV_8UC4");
            Mat tmp(android_bitmap_info.height, android_bitmap_info.width, CV_8UC4, pixels);
            if (false) cvtColor(tmp, dst, COLOR_mRGBA2RGBA);
            else tmp.copyTo(dst);
        } else {
            // info.format == ANDROID_BITMAP_FORMAT_RGB_565
            // LOGD("nBitmapToMat: RGB_565 -> CV_8UC4");
            Mat tmp(android_bitmap_info.height, android_bitmap_info.width, CV_8UC2, pixels);
            cvtColor(tmp, dst, COLOR_BGR5652RGBA);
        }
        AndroidBitmap_unlockPixels(env, bitmap);
        return;
    } catch (const cv::Exception &e) {
        AndroidBitmap_unlockPixels(env, bitmap);
        // LOGE("nBitmapToMat catched cv::Exception: %s", e.what());
        jclass je = env->FindClass("org/opencv/core/CvException");
        if (!je) je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, e.what());
        return;
    } catch (...) {
        AndroidBitmap_unlockPixels(env, bitmap);
        //LOGE("nBitmapToMat catched unknown exception (...)");
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "Unknown exception in JNI code {nBitmapToMat}");
        return;
    }

}

void MatToBitmap(JNIEnv *env, Mat &src, jobject bitmap) {

    AndroidBitmapInfo info;
    void *pixels = nullptr;

    try {
        // LOGD("nMatToBitmap");
        CV_Assert(AndroidBitmap_getInfo(env, bitmap, &info) >= 0);
        CV_Assert(info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
                  info.format == ANDROID_BITMAP_FORMAT_RGB_565);
        CV_Assert(src.dims == 2 && info.height == (uint32_t) src.rows &&
                  info.width == (uint32_t) src.cols);
        CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3 || src.type() == CV_8UC4);
        CV_Assert(AndroidBitmap_lockPixels(env, bitmap, &pixels) >= 0);
        CV_Assert(pixels);
        if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
            Mat tmp(info.height, info.width, CV_8UC4, pixels);
            if (src.type() == CV_8UC1) {
                //  LOGD("nMatToBitmap: CV_8UC1 -> RGBA_8888");
                cvtColor(src, tmp, COLOR_GRAY2RGBA);
            } else if (src.type() == CV_8UC3) {
                // LOGD("nMatToBitmap: CV_8UC3 -> RGBA_8888");
                cvtColor(src, tmp, COLOR_RGB2RGBA);
            } else if (src.type() == CV_8UC4) {
                // LOGD("nMatToBitmap: CV_8UC4 -> RGBA_8888");
                if (false)
                    cvtColor(src, tmp, COLOR_RGBA2mRGBA);
                else
                    src.copyTo(tmp);
            }
        } else {
            // info.format == ANDROID_BITMAP_FORMAT_RGB_565
            Mat tmp(info.height, info.width, CV_8UC2, pixels);
            if (src.type() == CV_8UC1) {
                // LOGD("nMatToBitmap: CV_8UC1 -> RGB_565");
                cvtColor(src, tmp, COLOR_GRAY2BGR565);
            } else if (src.type() == CV_8UC3) {
                // LOGD("nMatToBitmap: CV_8UC3 -> RGB_565");
                cvtColor(src, tmp, COLOR_RGB2BGR565);
            } else if (src.type() == CV_8UC4) {
                //LOGD("nMatToBitmap: CV_8UC4 -> RGB_565");
                cvtColor(src, tmp, COLOR_RGBA2BGR565);
            }
        }
        AndroidBitmap_unlockPixels(env, bitmap);
        return;
    } catch (const cv::Exception &e) {
        AndroidBitmap_unlockPixels(env, bitmap);
        //LOGE("nMatToBitmap catched cv::Exception: %s", e.what());
        jclass je = env->FindClass("org/opencv/core/CvException");
        if (!je) je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, e.what());
        return;
    } catch (...) {
        AndroidBitmap_unlockPixels(env, bitmap);
        //LOGE("nMatToBitmap catched unknown exception (...)");
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "Unknown exception in JNI code {nMatToBitmap}");
        return;
    }

}
