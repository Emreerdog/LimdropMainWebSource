#include "my.h"
#include <Python.h>
void my::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	for(int i = 0; i < 10000; i++){
	
	wchar_t *program = Py_DecodeLocale("coolprogram", NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("import json\n""print('Today is' + 'nice')\n");
    Py_FinalizeEx();
       
    PyMem_RawFree(program);
	}
    std::cout << "Hello world" << std::endl;

    auto resp = HttpResponse::newNotFoundResponse();
    callback(resp);
}
