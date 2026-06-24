package nanoai

/*
#cgo LDFLAGS: -lnanoai
#include "nanoai/runtime.h"
#include <stdlib.h>
*/
import "C"
import (
	"unsafe"
)

type NanoRuntime struct {
	handle C.nanoai_runtime_t
}

func New() *NanoRuntime {
	return &NanoRuntime{handle: C.nanoai_create()}
}

func (r *NanoRuntime) Close() {
	C.nanoai_destroy(r.handle)
}

func (r *NanoRuntime) LoadModel(path, id string) bool {
	cPath := C.CString(path)
	cId := C.CString(id)
	defer C.free(unsafe.Pointer(cPath))
	defer C.free(unsafe.Pointer(cId))
	return bool(C.nanoai_load_model(r.handle, cPath, cId))
}

func (r *NanoRuntime) Generate(prompt, id string, priority int) string {
	cPrompt := C.CString(prompt)
	cId := C.CString(id)
	defer C.free(unsafe.Pointer(cPrompt))
	defer C.free(unsafe.Pointer(cId))
	res := C.nanoai_generate(r.handle, cPrompt, cId, C.int(priority))
	defer C.nanoai_string_free(res)
	return C.GoString(res)
}
