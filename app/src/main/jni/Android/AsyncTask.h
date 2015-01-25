#include <jni.h>

namespace AsyncTask {
    void publishProgress(JNIEnv* env, jobject task, int progress);
}