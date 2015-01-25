#include <jni.h>

// Resource management class for jclasses.  Deletes the local ref to the jclass in the destructor.
class JClass {
public:
    JClass(JNIEnv* env, jclass inner);
    JClass(JClass&& other);
    ~JClass();
    operator jclass();
private:
    JNIEnv* _env;
    jclass _inner;
};