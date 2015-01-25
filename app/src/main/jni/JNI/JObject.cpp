#include "JObject.h"

#include <cstddef>

JObject::JObject(JNIEnv* env, jobject inner) :
    _env(env),
    _inner(inner)
{}

JObject::JObject(JObject&& other) :
    _env(other._env),
    _inner(other._inner)
{
    other._inner = nullptr;
}

JObject::~JObject() {
    if (_inner) _env->DeleteLocalRef(_inner);
}

jobject JObject::get() {
    return _inner;
}

JObject::operator jobject() {
    return _inner;
}
