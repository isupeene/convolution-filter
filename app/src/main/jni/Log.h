#include <jni.h>

class Logger {
public:
    virtual void v(JNIEnv* env, const char* tag, const char* message) {}
    virtual void d(JNIEnv* env, const char* tag, const char* message) {}
    virtual void w(JNIEnv* env, const char* tag, const char* message) {}
    virtual void e(JNIEnv* env, const char* tag, const char*message) {}
    virtual void wtf(JNIEnv* env, const char* tag, const char* message) {}
};

class JavaLogger : public Logger {
public:
    // Resource leak here.  I don't know how to deal with it, because if access env on a different
    // thread from the one on which this thread was created, the app will crash.
    // Fortunately, it's not an issue in practice, since we currently only create one of these,
    // and never destroy it.
    JavaLogger(JNIEnv* env, jobject logWrapper) :
        _logWrapper(env->NewGlobalRef(logWrapper))
    {}

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

private:
    jobject _logWrapper;

    void invoke(JNIEnv* env, const char* methodName, const char* tag, const char* message)
    {
        jclass wrapperClass = env->FindClass("ece493/assignment1/LogWrapper");
        jmethodID methodID = env->GetMethodID(wrapperClass, methodName, "(Ljava/lang/String;Ljava/lang/String;)V");
        env->CallVoidMethod(_logWrapper, methodID, env->NewStringUTF(tag), env->NewStringUTF(message));
    }
};

extern Logger* Log;
