//
// Created by micth on 2016-06-26.
//

#include "Store.h"
#include <string.h>


int32_t isEntryValid(JNIEnv *pEnv, StoreEntry *pEntry, StoreType pType) {
    if ((pEntry != NULL) && (pEntry->mType == pType)) {
        return 1;
    }
    return 0;
}

StoreEntry *findEntry(JNIEnv *pEnv, Store *pStore, jstring pKey, int32_t *pError) {
    StoreEntry *lEntry = pStore->mEntries;
    StoreEntry *lEntryEnd = lEntry + pStore->mLength;

    const char *lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv, pKey, NULL);

    if (lKeyTmp == NULL) {
        if (pError != NULL) {
            *pError = 1;
        }
        return NULL;
    }

    while ((lEntry < lEntryEnd) && (strcmp(lEntry->mKey, lKeyTmp) != 0)) {
        ++lEntry;
    }

    (*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp);

    return (lEntry == lEntryEnd) ? NULL : lEntry;

}


StoreEntry *allocateEntry(JNIEnv *pEnv, Store *pStore, jstring pKey) {

    int32_t lError = 0;
    StoreEntry *lEntry = findEntry(pEnv, pStore, pKey, &lError);

    if (lEntry != NULL) {
        releaseEntryValue(pEnv, lEntry);
    } else if (!lError) {
        if (pStore->mLength >= STORE_MAX_CAPACITY) {
            return NULL;
        }
        lEntry = pStore->mEntries + pStore->mLength;

        const char *lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv, pKey, NULL);

        if (lKeyTmp == NULL) {
            return NULL;
        }
        lEntry->mKey = (char *) malloc(strlen(lKeyTmp));
        strcpy(lEntry->mKey, lKeyTmp);
        (*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp);

        ++pStore->mLength;
    }
    return lEntry;
}

void  releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry){
    int i;
    switch (pEntry->mType){
        case StoreType_String:
            free(pEntry->mValue.mString);
            break;
    }
}




