#include "JClass.h"

#include <cstddef>

JClass::JClass(JNIEnv* env, jclass inner) :
    _env(env),
    _inner(inner)
{}

JClass::JClass(JClass&& other) :
    _env(other._env),
    _inner(other._inner)
{
    other._inner = nullptr;
}

JClass::~JClass() {
    if (_inner) _env->DeleteLocalRef(_inner);
}

JClass::operator jclass() {
    return _inner;
}
