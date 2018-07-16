package ustinov.artyom.deepmushrooms.models;

import android.graphics.Bitmap;

/**
 * Created by artyo on 7/16/2018.
 */

public interface Classifier {
    Classification recognize(Bitmap bitmap);
}
