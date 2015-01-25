#ifndef ASYNC_TASK_H
#define ASYNC_TASK_H

#include <jni.h>

namespace AsyncTask {
    void publishProgress(JNIEnv* env, jobject task, int progress);
}

#endif
