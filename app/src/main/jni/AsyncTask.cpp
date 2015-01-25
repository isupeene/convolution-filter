#include "AsyncTask.h"

#include <cstdio>

#include "Log.h"

#define TAG "AsyncTask"

namespace {
    jclass GetClass(JNIEnv* env) {
        static jclass result = env->FindClass("android/os/AsyncTask");
        return result;
    }

    jmethodID GetMethodID_publishProgress(JNIEnv* env) {
        static jmethodID result = env->GetMethodID(
            GetClass(env),
            "publishProgress",
            "([Ljava/lang/Object;)V"
        );
        return result;
    }
}

namespace AsyncTask {
    void publishProgress(JNIEnv* env, jobject task, int progress) {
        // TODO: seperate Integer Array stuff from AsyncTask stuff.
        static jclass intClass = env->FindClass("java/lang/Integer");
        static jmethodID initID = env->GetMethodID(intClass, "<init>", "(I)V");
        jobject progressObject = env->NewObject(intClass, initID, progress);

        jobject array = env->NewObjectArray(1, intClass, progressObject);

        env->CallVoidMethod(
            task,
            GetMethodID_publishProgress(env),
            array
        );

        env->DeleteLocalRef(progressObject);
        env->DeleteLocalRef(array);
    }
}