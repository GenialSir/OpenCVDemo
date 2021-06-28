package com.genialsir.opencvdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;


import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;

import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    private TextView tv;
    private ImageView ivOpenCV;
    private OpenCVAssistant openCVAssistant;

//    private double max_size = 1024;
//    private int PICK_IMAGE_REQUEST = 1;
//    private Bitmap selectbp;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        openCVAssistant = new OpenCVAssistant();
        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        tv.setText(openCVAssistant.setDetectionAdapter(""));

        ivOpenCV = findViewById(R.id.iv_open_cv);


    }

    public void toGray(View view) {

        convertGray2();
//        convertGray1();

//        convertGray();
    }

    //变灰通过JNI配合SO库代码实现
    private void convertGray2() {
        Bitmap srcBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.genial_sir);
        Bitmap grayBitmap = Bitmap.createBitmap(srcBitmap.getWidth(), srcBitmap.getHeight(),
                Bitmap.Config.RGB_565);
        openCVAssistant.ctvColorFromJni(srcBitmap, grayBitmap);
        ivOpenCV.setImageBitmap(grayBitmap);
    }

    //变灰通过OpenCV的Java库和SO库实现
    private void convertGray1() {
        Mat rgbMat = new Mat();
        Mat grayMat = new Mat();
        Bitmap srcBitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.genial_sir);
        Bitmap grayBitmap = Bitmap.createBitmap(srcBitmap.getWidth(), srcBitmap.getHeight(),
                Bitmap.Config.RGB_565);
        Utils.bitmapToMat(srcBitmap, rgbMat);
        Imgproc.cvtColor(rgbMat, grayMat, Imgproc.COLOR_RGB2GRAY);
        Utils.matToBitmap(grayMat, grayBitmap);
        ivOpenCV.setImageBitmap(grayBitmap);

    }

//    private void convertGray() {
//        Mat src = new Mat();
//        Mat temp = new Mat();
//        Mat dst = new Mat();
//        Utils.bitmapToMat(selectbp, src);
//        Imgproc.cvtColor(src, temp, Imgproc.COLOR_BGRA2BGR);
//        Imgproc.cvtColor(temp, dst, Imgproc.COLOR_BGR2GRAY);
//        Utils.matToBitmap(dst, selectbp);
//        ivOpenCV.setImageBitmap(selectbp);
//    }


    public void toRecognition(View view) {
//        selectImage();

//        tv.setText(new OpenCVAssistant().setDetectionAdapter(""));
//        startActivity(new Intent(this, FaceRecognitionActivity.class));
    }


//
//    @Override
//    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//        super.onActivityResult(requestCode, resultCode, data);
//        if(requestCode == PICK_IMAGE_REQUEST && resultCode == RESULT_OK && data != null && data.getData() != null) {
//            Uri uri = data.getData();
//            try {
//                InputStream input = getContentResolver().openInputStream(uri);
//                BitmapFactory.Options options = new BitmapFactory.Options();
//                options.inJustDecodeBounds = true;
//                BitmapFactory.decodeStream(input, null, options);
//                int raw_width = options.outWidth;
//                int raw_height = options.outHeight;
//                int max = Math.max(raw_width, raw_height);
//                int newWidth = raw_width;
//                int newHeight = raw_height;
//                int inSampleSize = 1;
//                if(max > max_size) {
//                    newWidth = raw_width / 2;
//                    newHeight = raw_height / 2;
//                    while((newWidth/inSampleSize) > max_size || (newHeight/inSampleSize) > max_size) {
//                        inSampleSize *=2;
//                    }
//                }
//
//                options.inSampleSize = inSampleSize;
//                options.inJustDecodeBounds = false;
//                options.inPreferredConfig = Bitmap.Config.ARGB_8888;
//                selectbp = BitmapFactory.decodeStream(getContentResolver().openInputStream(uri), null, options);
//
//                ivOpenCV.setImageBitmap(selectbp);
//
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//    }
//
//    private void selectImage() {
//        Intent intent = new Intent();
//        intent.setType("image/*");
//        intent.setAction(Intent.ACTION_GET_CONTENT);
//        startActivityForResult(Intent.createChooser(intent,"选择图像..."), PICK_IMAGE_REQUEST);
//    }


}