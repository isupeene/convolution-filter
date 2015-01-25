#ifndef JOBJECT_H
#define JOBJECT_H

#include <jni.h>

class JObject {
public:
    JObject(JNIEnv* env, jobject inner);
    JObject(JObject&& other);
    ~JObject();
    operator jobject();
    jobject get(); // Implicit conversion won't work for ... args.
private:
    JNIEnv* _env;
    jobject _inner;
};

#endif
