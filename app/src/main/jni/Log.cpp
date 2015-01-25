#include "Log.h"


namespace {
    void invoke(JNIEnv* env, const char* methodName, const char* tag, const char* message)
    {
        jclass logClass = env->FindClass("android/util/Log");
        jmethodID methodID = env->GetStaticMethodID(logClass, methodName, "(Ljava/lang/String;Ljava/lang/String;)I");

        // We must track and delete the local refs so that we don't exceed the maximum.
        jobject tagObject = env->NewStringUTF(tag);
        jobject messageObject = env->NewStringUTF(message);
        env->CallStaticIntMethod(logClass, methodID, tagObject, messageObject);
        env->DeleteLocalRef(tagObject);
        env->DeleteLocalRef(messageObject);
        env->DeleteLocalRef(logClass);
    }
}

namespace Log {
    void v(JNIEnv* env, const char* tag, const char* message) {
        invoke(env, "v", tag, message);
    }

    void d(JNIEnv* env, const char* tag, const char* message) {
        invoke(env, "d", tag, message);
    }

    void w(JNIEnv* env, const char* tag, const char* message) {
        invoke(env, "w", tag, message);
    }

    void e(JNIEnv* env, const char* tag, const char* message) {
        invoke(env, "e", tag, message);
    }

    void wtf(JNIEnv* env, const char* tag, const char* message) {
        invoke(env, "wtf", tag, message);
    }
}
