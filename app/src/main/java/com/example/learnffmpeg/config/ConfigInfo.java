package com.example.learnffmpeg.config;

public class ConfigInfo {

    static {
        System.loadLibrary("ffmpeg");
    }

    public static native String getConfigInfo();
}
