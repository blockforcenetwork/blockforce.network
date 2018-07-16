package ustinov.artyom.deepmushrooms.models;



import android.content.res.AssetManager;
import android.graphics.Bitmap;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.tensorflow.contrib.android.TensorFlowInferenceInterface;

public class TensorFlowClassifier implements Classifier {
    private String inputName;
    private String outputName;
    private int[] imageBitmapPixels;
    private float[] imageNormalizedPixels;
    private float[] results;
    private TensorFlowInferenceInterface tensorFlowInference;

    @Override
    public Classification recognize(Bitmap bitmap) {
        preprocessImageToNormalizedFloats(bitmap);
        classifyImageToOutputs();
        Classification output = getResults();
        return output;
    }

    private void preprocessImageToNormalizedFloats(Bitmap bitmap) {
        // Preprocess the image data from 0-255 int to normalized float based
        // on the provided parameters.
        float imageStd = 256.0f;
        imageBitmapPixels = new int[bitmap.getWidth() * bitmap.getHeight()];
        imageNormalizedPixels = new float[bitmap.getWidth() * bitmap.getHeight() * 3];
        bitmap.getPixels(imageBitmapPixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight());

        for (int i = 0; i < imageBitmapPixels.length; i++) {
            try {
                int pixel = imageBitmapPixels[i];
                imageNormalizedPixels[i * 3] = (((pixel >> 16) & 0xFF)) / imageStd;
                imageNormalizedPixels[i * 3 + 1] = (((pixel >> 8) & 0xFF)) / imageStd;
                imageNormalizedPixels[i * 3 + 2] = ((pixel & 0xFF)) / imageStd;
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }

    private void classifyImageToOutputs() {
        tensorFlowInference.feed(inputName, imageNormalizedPixels, 1L, 3,150, 150);
        tensorFlowInference.run(new String[]{outputName}, true);
        tensorFlowInference.fetch(outputName, results);
    }

    public TensorFlowClassifier(AssetManager assetManager,
                                String modelPath, String labelFile, String inputName, String outputName,
                                boolean feedKeepProb) throws IOException {

        this.inputName = inputName;
        this.outputName = outputName;

        this.tensorFlowInference = new TensorFlowInferenceInterface(assetManager, modelPath);

        this.results = new float[1];
    }

    private Classification getResults() {
        Classification classification = new Classification(results[0]);
        return classification;
    }
}
