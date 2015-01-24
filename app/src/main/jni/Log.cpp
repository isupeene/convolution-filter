#include "Log.h"


namespace {
    void invoke(JNIEnv* env, const char* methodName, const char* tag, const char* message)
    {
        jclass logClass = env->FindClass("android/util/Log");
        jmethodID methodID = env->GetStaticMethodID(logClass, methodName, "(Ljava/lang/String;Ljava/lang/String;)I");
        env->CallStaticIntMethod(logClass, methodID, env->NewStringUTF(tag), env->NewStringUTF(message));
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
