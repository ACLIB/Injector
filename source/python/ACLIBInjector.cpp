#include "PyDLLInject.hpp"

namespace ACLIB
{
    static PyMethodDef module_methods[] = {
        // {"func name", func, METH_NOARGS, "doc"},
        {nullptr, nullptr, 0, nullptr}};

    struct PyModuleDef aclib_module = {
        PyModuleDef_HEAD_INIT,
        "aclib_injector",
        "Injects a dll into an executable",
        -1,
        module_methods};

    PyMODINIT_FUNC PyInit_aclib_injector()
    {
        PyObject* module = PyModule_Create(&aclib_module);

        if(PyType_Ready(&DLLInjectType) < 0)
        {
            // err
            printf("Could not init DLLInject type");
        }

        PyModule_AddObject(module, "DLLInject", reinterpret_cast<PyObject*>(&DLLInjectType));

        return module;
    }

}  // namespace ACLIB
