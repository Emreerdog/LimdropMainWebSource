#include "checkpy.h"
#include <limutils/pyutils.h>
void checkpy::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	Py_Initialize();
	PyObject* ourArgs = PyTuple_New(2);
    PyTuple_SetItem(ourArgs, 0, PyLong_FromLong(5));
    PyTuple_SetItem(ourArgs, 1, PyLong_FromLong(2));
    PyObject* imports = PyImport_ImportModule("math");
    PyObject* function = PyObject_GetAttrString(imports, "pow");
    PyObject* callFunc = PyObject_CallObject(function, ourArgs);
    long result = PyLong_AsLong(callFunc);
    std::cout << result << std::endl;
    Py_CLEAR(ourArgs);
    Py_CLEAR(imports);
    Py_CLEAR(function);
    Py_CLEAR(callFunc);
	Py_FinalizeEx();
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}
