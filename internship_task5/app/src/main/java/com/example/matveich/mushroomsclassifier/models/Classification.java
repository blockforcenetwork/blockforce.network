package com.example.matveich.mushroomsclassifier.models;

/**
 * Created by marianne-linhares on 20/04/17.
 */

public class Classification {

    private float conf;
    private String label;

    Classification() {
        this.conf = 0;
        this.label = null;
    }

    void update(float _conf, String _label) {
        conf = _conf;
        label = _label;
    }

    public String getLabel() {
        return label;
    }

    public float getConf() {
        return conf;
    }
}
