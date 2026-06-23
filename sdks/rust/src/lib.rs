use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_void, c_int};

type NanoaiRuntimeT = *mut c_void;

extern "C" {
    fn nanoai_create() -> NanoaiRuntimeT;
    fn nanoai_destroy(handle: NanoaiRuntimeT);
    fn nanoai_load_model_id(handle: NanoaiRuntimeT, model_path: *const c_char, model_id: *const c_char) -> bool;
    fn nanoai_generate_id(handle: NanoaiRuntimeT, prompt: *const c_char, model_id: *const c_char) -> *const c_char;
    fn nanoai_analyze_document(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
    fn nanoai_understand_report(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
}

pub struct NanoRuntime {
    handle: NanoaiRuntimeT,
}

impl NanoRuntime {
    pub fn new() -> Self {
        unsafe { Self { handle: nanoai_create() } }
    }

    pub fn load_model(&self, model_path: &str, model_id: &str) -> bool {
        let c_path = CString::new(model_path).unwrap();
        let c_id = CString::new(model_id).unwrap();
        unsafe { nanoai_load_model_id(self.handle, c_path.as_ptr(), c_id.as_ptr()) }
    }

    pub fn generate(&self, prompt: &str, model_id: &str) -> String {
        let c_prompt = CString::new(prompt).unwrap();
        let c_id = CString::new(model_id).unwrap();
        unsafe {
            let result_ptr = nanoai_generate_id(self.handle, c_prompt.as_ptr(), c_id.as_ptr());
            if result_ptr.is_null() { return String::new(); }
            CStr::from_ptr(result_ptr).to_string_lossy().into_owned()
        }
    }

    pub fn analyze_document(&self, buffer: &[u8], width: i32, height: i32) -> String {
        unsafe {
            let result_ptr = nanoai_analyze_document(self.handle, buffer.as_ptr(), width, height);
            if result_ptr.is_null() { return String::new(); }
            CStr::from_ptr(result_ptr).to_string_lossy().into_owned()
        }
    }
}

impl Drop for NanoRuntime {
    fn drop(&mut self) {
        unsafe { nanoai_destroy(self.handle); }
    }
}

unsafe impl Send for NanoRuntime {}
