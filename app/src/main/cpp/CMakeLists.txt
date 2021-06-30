cmake_minimum_required(VERSION 3.10.2)

include_directories(libopencv/include)

add_library(
        opencv_jni
        SHARED
        opencv_jni.cpp
        face_detector.cpp
)

#配置静态库
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/lib3rdparty/${CMAKE_ANDROID_ARCH_ABI}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libopencv/libs/${CMAKE_ANDROID_ARCH_ABI}")


#声明动态库
add_library(
        opencv_java4
        SHARED
        IMPORTED
)
#定义项目的动态库路径
#set(PROJECT_ROOT_DIR D:/AndroidProject/DemoProject/OpenCVDemo)
#动态库的所在路径
set_target_properties(
        opencv_java4
        PROPERTIES
        IMPORTED_LOCATION

        ${CMAKE_SOURCE_DIR}/../libs/${CMAKE_ANDROID_ARCH_ABI}/libopencv_java4.so
)

target_link_libraries( # Specifies the target library.
        opencv_jni

        opencv_java4

        #opencv_core因依赖到opencv_imgproc库所以需要放在其后面
#        -Wl,--start-group
#        opencv_calib3d
#        opencv_dnn
#        opencv_features2d
#        opencv_flann
#        opencv_gapi
#        opencv_highgui
#        opencv_imgcodecs
#        opencv_imgproc
#        opencv_core
#        opencv_ml
#        opencv_photo
#        opencv_objdetect
#        opencv_stitching
#        opencv_video
#        opencv_videoio
#        -Wl,--end-group

        #3rdparty静态库需要放在opencv静态库之后
#        -Wl,--start-group
#        ade
#        cpufeatures
#        IlmImf
#        ittnotify
#        libjpeg-turbo
#        libopenjp2
#        libpng
#        libprotobuf
#        libtiff
#        libwebp
#        quirc
#        tbb
#        tegra_hal
#        -Wl,--end-group

        jnigraphics
#        z
        log)

