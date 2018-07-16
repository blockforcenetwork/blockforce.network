package com.example.matveich.mushroomsclassifier;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.matveich.mushroomsclassifier.models.Classifier;
import com.example.matveich.mushroomsclassifier.models.TensorFlowClassifier;


public class MainActivity extends AppCompatActivity {

    private Classifier c;

    static final int READ_REQ = 24;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button button_choose = findViewById(R.id.button_choose);
        button_choose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                loadModel();
                Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
                intent.addCategory(Intent.CATEGORY_OPENABLE);
                intent.setType("image/*");

                startActivityForResult(intent, READ_REQ);
            }
        });
    }

    private void loadModel() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    c = TensorFlowClassifier.create(getAssets(), "model",
                                    "weights_improvement_12_0.69.hdf5.pb",
                            "labels.txt", 150,
                                    "input",
                            "output", false);
                } catch (final Exception e) {
                    throw new RuntimeException("Error initializing classifiers!", e);
                }
            }
        }).start();
    }
}
