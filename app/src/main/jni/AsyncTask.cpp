#include "AsyncTask.h"

#include <cstdio>

#include "Log.h"
#include "JClass.h"
#include "JObject.h"

#define TAG "AsyncTask"

namespace {
    JClass GetClass(JNIEnv* env) {
        return JClass(env, env->FindClass("android/os/AsyncTask"));
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
        JClass intClass(env, env->FindClass("java/lang/Integer"));
        static jmethodID initID = env->GetMethodID(intClass, "<init>", "(I)V");
        JObject progressObject(env, env->NewObject(intClass, initID, progress));

        JObject array(env, env->NewObjectArray(1, intClass, progressObject.get()));

        env->CallVoidMethod(
            task,
            GetMethodID_publishProgress(env),
            array.get()
        );
    }
}