#include <jni.h>
#include <string.h>

JNIEXPORT jstring JNICALL
Java_com_example_micthebick_ndktest_MainActivity_testNdk(JNIEnv *env, jobject instance) {
    // TODO
    return (*env)->NewStringUTF(env, "hello ndk");
}