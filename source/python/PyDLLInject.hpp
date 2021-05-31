#ifndef ACLIB_SHARED_MEMORY_PYEVENTLOOP_HPP
#define ACLIB_SHARED_MEMORY_PYEVENTLOOP_HPP

#include "DLLInject.hpp"

#include <Python.h>

namespace ACLIB
{
    struct PyDLLInject
    {
        PyObject_HEAD
        DLLInject* m_dll_inject;
    };

    static PyObject* dll_inject_new_(PyTypeObject* type, PyObject* args, PyObject* kwds);
    static void      dll_inject_del_(PyTypeObject* self);

    static int      dll_inject_init_(PyDLLInject* self, PyObject* args, PyObject* kwds);

    extern PyMemberDef  DLLInjectType_members[];
    extern PyMethodDef  DLLInjectType_methods[];
    extern PyTypeObject DLLInjectType;
}  // namespace ACLIB

#endif  // ACLIB_SHARED_MEMORY_PYEVENTLOOP_HPP
