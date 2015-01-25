#include <jni.h>

namespace Log {
    void v(JNIEnv* env, const char* tag, const char* message);

    void d(JNIEnv* env, const char* tag, const char* message);

    void w(JNIEnv* env, const char* tag, const char* message);

    void e(JNIEnv* env, const char* tag, const char* message);

    void wtf(JNIEnv* env, const char* tag, const char* message);
}
