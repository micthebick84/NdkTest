//
// Created by micth on 2016-06-25.
//

#include "com_example_micthebick_ndktest_Store.h"
#include "Store.h"
#include <stdint.h>
#include <string.h>

static Store mStore = {{}, 0};

JNIEXPORT jint JNICALL Java_com_example_micthebick_ndktest_Store_getInteger
        (JNIEnv *pEnv, jobject pThis, jstring pKey){
    StoreEntry* lEntry = findEntry(pEnv, &mStore, pKey, NULL);
    if (isEntryValid(pEnv, lEntry, StoreType_Integer)){
        return lEntry->mValue.mInteger;
    } else{
        return 0;
    }
}

JNIEXPORT void JNICALL Java_com_example_micthebick_ndktest_Store_setInteger
        (JNIEnv *pEnv, jobject pThis, jstring pKey, jint pInteger){

    StoreEntry* lEntry  =   allocateEntry(pEnv, &mStore, pKey);
    if (lEntry != NULL){
        lEntry->mType   =   StoreType_Integer;
        lEntry->mValue.mInteger =   pInteger;
    }
}

JNIEXPORT jstring JNICALL Java_com_example_micthebick_ndktest_Store_getString
        (JNIEnv *pEnv, jobject pThis, jstring pKey){
    StoreEntry* lEntry  =   findEntry(pEnv, &mStore, pKey, NULL);
    if (isEntryValid(pEnv, lEntry, StoreType_String)){
        return (*pEnv)->NewStringUTF(pEnv, lEntry->mValue.mString);
    } else{
        return NULL;
    }
}

JNIEXPORT void JNICALL Java_com_example_micthebick_ndktest_Store_setString
        (JNIEnv *pEnv, jobject pThis, jstring pKey, jstring pString){

    const char* lStringTmp  =   (*pEnv)->GetStringUTFChars(pEnv, pString, NULL);

    if (lStringTmp == NULL){
        return;
    }

    StoreEntry* lEntry  =   allocateEntry(pEnv, &mStore, pKey);

    if (lEntry != NULL){
        lEntry->mType   =   StoreType_String;
        jsize lStringLength =   (*pEnv)->GetStringUTFLength(pEnv, pString);
        lEntry->mValue.mString  =   (char*)malloc(sizeof(char) * (lStringLength + 1));
        strcpy(lEntry->mValue.mString, lStringTmp);
    }
    (*pEnv)->ReleaseStringUTFChars(pEnv, pString, lStringTmp);
}


