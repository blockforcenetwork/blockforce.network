package ustinov.artyom.deepmushrooms;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import java.util.Random;

import ustinov.artyom.deepmushrooms.models.Classification;
import ustinov.artyom.deepmushrooms.models.Classifier;
import ustinov.artyom.deepmushrooms.models.TensorFlowClassifier;

public class MainActivity extends AppCompatActivity {

    Classifier mClassifier;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        String drawabale = "ic_mushroom_" + (new Random().nextInt(5) + 1);
        setContentView(R.layout.activity_main);
        ImageView imageView = findViewById(R.id.imageView2);
        imageView.setImageDrawable(getResources().getDrawable(getResourceID(drawabale, "drawable", getApplicationContext())));
        loadModel();
    }

    protected final static int getResourceID(final String resName, final String resType, final Context ctx) {
        final int ResourceID = ctx.getResources().getIdentifier(resName, resType, ctx.getApplicationInfo().packageName);
        if (ResourceID == 0) {
            throw new IllegalArgumentException("No resource string found with name " + resName);
        } else {
            return ResourceID;
        }
    }

    static final int REQUEST_IMAGE_CAPTURE = 1;


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_IMAGE_CAPTURE && resultCode == RESULT_OK) {
            Bundle extras = data.getExtras();
            Bitmap imageBitmap = (Bitmap) extras.get("data");
            ImageView mImageView = findViewById(R.id.imageView2);
            mImageView.setImageBitmap(imageBitmap);
            Classification res = mClassifier.recognize(Bitmap.createScaledBitmap(imageBitmap,150,150,true));
            Button mButton = findViewById(R.id.button);
            String result = "("+Double.toString(res.getConf()) + (res.getConf()>=0.5?") Might be edible":") Might be inedible");
            mButton.setText(result);
        }
    }


    public void dispatchTakePictureIntent(View view) {
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null) {
            startActivityForResult(takePictureIntent, REQUEST_IMAGE_CAPTURE);
        }
    }

    private void loadModel() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    mClassifier = new TensorFlowClassifier(getAssets(),
                            "frozen_classification.pb", "opt_class",
                            "input_1", "output/Sigmoid", true);
                } catch (final Exception e) {
                    throw new RuntimeException("Error initializing classifier!", e);
                }
            }
        }).start();
    }


}
