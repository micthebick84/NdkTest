package com.example.micthebick.ndktest;

/**
 * Created by micth on 2016-06-25.
 */
public class Store {

    static {
        System.loadLibrary("store");
    }

    public native int getInteger(String pKey);
    public native void setInteger(String pKey, int pInt);
    public native String getString(String pKey);
    public native void setString(String pKey, String pString);

}
