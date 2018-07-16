package com.example.matveich.mushroomsclassifier.models;

public interface Classifier {
    String name();

    Classification recognize(final float[] pixels);
}
