#include "PyDLLInject.hpp"

#include <structmember.h>

namespace ACLIB
{
    PyObject* dll_inject_new_(PyTypeObject* type, PyObject* args, PyObject* kwds)
    {
        PyDLLInject* self;
        self = reinterpret_cast<PyDLLInject*>(type->tp_alloc(type, 0));

        if(self != nullptr)
        {
            self->m_dll_inject = new DLLInject();
        }
        return reinterpret_cast<PyObject*>(self);
    }

    int dll_inject_init_(PyDLLInject* self, PyObject* args, PyObject* kwds)
    {
        static char* kwlist[] = {"process", "dll", "interval", nullptr};
        char *       process, *dll;

        if(!PyArg_ParseTupleAndKeywords(
               args,
               kwds,
               "|ssi",
               kwlist,
               &process,
               &dll,
               &self->m_dll_inject->m_poll_interval))
            return -1;

        self->m_dll_inject->m_process_name = process;
        self->m_dll_inject->m_dll_name     = dll;

        return 0;
    }

    void dll_inject_del_(PyTypeObject* self)
    {
        delete reinterpret_cast<PyDLLInject*>(self)->m_dll_inject;
        Py_TYPE(self)->tp_free(self);
    }

    PyMemberDef DLLInjectType_members[] = {{nullptr}};

    PyObject* run(PyDLLInject* type, PyObject* args, PyObject* kwds)
    {
        type->m_dll_inject->run();
        return Py_None;
    }

    PyMethodDef DLLInjectType_methods[] = {
        // {"func_name", (PyCFunction)func, METH_NOARGS, "doc"},
        {"run", (PyCFunction)run, METH_NOARGS, "doc"},
        {nullptr}};

    static PyObject* get_process(PyDLLInject* self, void* closure)
    {
        return PyUnicode_FromString(self->m_dll_inject->m_process_name.data());
    }

    static PyObject* get_dll(PyDLLInject* self, void* closure)
    {
        return PyUnicode_FromString(self->m_dll_inject->m_dll_name.data());
    }

    static PyObject* get_interval(PyDLLInject* self, void* closure)
    {
        return PyLong_FromLong(self->m_dll_inject->m_poll_interval);
    }

    static PyGetSetDef DLLInjectType_getset[] = {
        {"process", (getter)get_process, nullptr, "", nullptr},
        {"dll", (getter)get_dll, nullptr, "", nullptr},
        {"interval", (getter)get_interval, nullptr, "", nullptr},
        {nullptr}};

    PyTypeObject DLLInjectType = {
        PyObject_HEAD_INIT(&PyType_Type) "aclib_injector.DLLInject", /* tp_name */
        sizeof(PyDLLInject),                                         /* tp_basicsize */
        0,                                                           /* tp_itemsize */
        (destructor)dll_inject_del_,                                 /* tp_dealloc */
        0,                                                           /* tp_print */
        nullptr,                                                     /* tp_getattr */
        nullptr,                                                     /* tp_setattr */
        nullptr,                                                     /* tp_reserved */
        nullptr,                                                     /* tp_repr */
        nullptr,                                                     /* tp_as_number */
        nullptr,                                                     /* tp_as_sequence */
        nullptr,                                                     /* tp_as_mapping */
        nullptr,                                                     /* tp_hash */
        nullptr,                                                     /* tp_call */
        nullptr,                                                     /* tp_str */
        nullptr,                                                     /* tp_getattro */
        nullptr,                                                     /* tp_setattro */
        nullptr,                                                     /* tp_as_buffer */
        Py_TPFLAGS_DEFAULT,                                          /* tp_flags */
        nullptr,                                                     /* tp_doc */
        nullptr,                                                     /* tp_traverse */
        nullptr,                                                     /* tp_clear */
        nullptr,                                                     /* tp_richcompare */
        0,                                                           /* tp_weaklistoffset */
        nullptr,                                                     /* tp_iter */
        nullptr,                                                     /* tp_iternext */
        DLLInjectType_methods,                                       /* tp_methods */
        DLLInjectType_members,                                       /* tp_members */
        DLLInjectType_getset,                                        /* tp_getset */
        nullptr,                                                     /* tp_base */
        nullptr,                                                     /* tp_dict */
        nullptr,                                                     /* tp_descr_get */
        nullptr,                                                     /* tp_descr_set */
        0,                                                           /* tp_dictoffset */
        (initproc)dll_inject_init_,                                  /* tp_init */
        nullptr,                                                     /* tp_alloc */
        (newfunc)dll_inject_new_,                                    /* tp_new */
    };
}  // namespace ACLIB
