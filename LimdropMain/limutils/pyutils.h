#include <Python.h>

typedef PyObject* POBJECT;

#define LIM_PLONG(_long) (PyLong_FromLong(_long));
#define LIM_PDOUBLE(_double) (PyFloat_FromDouble(_double));
#define LIM_PDOUBLE_FROM_STR(_Dstring) (PyFloat_FromString(_Dstring));
#define LIM_PSTR(_string) (PyUnicode_FromString(_string));
#define LIM_PIMPORT(_import) (PyImport_ImportModule(_import));
#define LIM_PFUNC_NOARG(_funcname) (PyObject_CallNoArgs(_funcname));
#define LIM_PFUNC_ONEARG(_funcname, _arg1) (PyObject_CallOneArg(_funcname, _arg1));
#define LIM_PFUNC_ARGS(_funcname, _tuple) (PyObject_CallObject(_funcname, _tuple));
#define LIM_PCHECK_LONG(_PLONG) (PyLong_Check(_PLONG));
#define LIM_PCHECK_DOUBLE(_PDOUBLE) (PyFloat_Check(_PDOUBLE));
#define LIM_PCHECK_STR(_PSTR) (PyUnicode_Check(_PSTR));
#define LIM_PGET_ATTR(_attr, _attr_name) (PyObject_GetAttrString(_attr, _attr_name));
#define LIM_PSET_ATTR(_attr, _attr_name, _set_val) (PyObject_SetAttrString(_attr, _attr_name, _set_val));
#define LIM_POBJECT_STR(_obj) (PyObject_Str(_obj));
#define LIM_PCHECK_TUPLE(_obj) (PyTuple_Check(_obj));
#define LIM_PMAKE_TUPLE(_count) (PyTuple_New(_count));
#define LIM_PADD_TUPLE(_obj, _index, _type) (PyTuple_SetItem(_obj, _index, _type));
#define LIM_PGET_TUPLE_ITEM(_obj, _pos) (PyTuple_GetItem(_obj, _pos));
#define LIM_PSIZE_TUPLE(_obj) (PyTuple_Size(_obj));
#define LIM_PRESIZE_TUPLE(_obj, _newsize) (_PyTuple_Resize(_obj));

namespace PC_TILL {
    const char* toString(POBJECT o) {
        bool checkString = LIM_PCHECK_STR(o);
        if (!checkString) {
            std::cout << "Invalid type conversion" << std::endl;
            return "Error!";
        }
        else {
            POBJECT temp_bytes = PyUnicode_AsEncodedString(o, "UTF-8", "strict");
            const char* result = PyBytes_AS_STRING(temp_bytes);
            Py_CLEAR(temp_bytes);
            return result;
        }
    }
    long toLong(POBJECT o) {
        bool checkLong = LIM_PCHECK_LONG(o);
        if (checkLong) {
            std::cout << "Invalid type conversion returned -1";
            return -1;
        }
        else
        {
            long result = PyLong_AsLong(o);
            return result;
        }
    }

    double toDouble(POBJECT o) {
        bool checkDouble = LIM_PCHECK_DOUBLE(o);
        if (checkDouble) {
            std::cout << "Invalid type conversion returned -1";
        }
        else {
            double result = PyFloat_AsDouble(o);
            return result;
        }
    }
}

