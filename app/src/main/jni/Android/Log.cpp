#include "Log.h"

#include "../JNI/JClass.h"
#include "../JNI/JObject.h"


namespace {
    JClass GetClass(JNIEnv* env) {
        return JClass(env, env->FindClass("android/util/Log"));
    }

    void invoke(JNIEnv* env, const char* methodName, const char* tag, const char* message)
    {
        // TODO: Consider optimizing by caching method ids.
        JClass logClass = GetClass(env);
        jmethodID methodID = env->GetStaticMethodID(logClass, methodName, "(Ljava/lang/String;Ljava/lang/String;)I");

        // We must track and delete the local refs so that we don't exceed the maximum.
        env->CallStaticIntMethod(
            logClass,
            methodID,
            JObject(env, env->NewStringUTF(tag)).get(),
            JObject(env, env->NewStringUTF(message)).get()
        );
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
