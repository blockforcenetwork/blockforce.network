package ustinov.artyom.deepmushrooms.models;

/**
 * Created by artyo on 7/16/2018.
 */
public class Classification {

    private float conf;

    Classification(float conf) {
        this.conf = conf;
    }

    Classification() {
        this.conf = 1;
    }

    public float getConf() {
        return conf;
    }
}
