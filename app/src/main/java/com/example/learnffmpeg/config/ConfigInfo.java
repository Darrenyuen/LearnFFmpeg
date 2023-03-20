package com.example.learnffmpeg.config;

public class ConfigInfo {

    static {
        System.loadLibrary("medianative");
    }
    
    public static native String getConfigInfo();
}
