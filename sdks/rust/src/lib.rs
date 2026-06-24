use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_void, c_int};

extern "C" {
    fn nanoai_create() -> *mut c_void;
    fn nanoai_destroy(handle: *mut c_void);
    fn nanoai_load_model_id(handle: *mut c_void, model_path: *const c_char, model_id: *const c_char) -> bool;
    fn nanoai_generate_id(handle: *mut c_void, prompt: *const c_char, model_id: *const c_char) -> *const c_char;
    fn nanoai_get_detected_hardware(handle: *mut c_void, model_id: *const c_char) -> *const c_char;
    fn nanoai_convert_model(input_path: *const c_char, output_path: *const c_char, quantization_type: c_int) -> bool;
}

pub struct NanoRuntime {
    handle: *mut c_void,
}

impl NanoRuntime {
    pub fn new() -> Self {
        unsafe {
            NanoRuntime {
                handle: nanoai_create(),
            }
        }
    }

    pub fn load_model(&self, model_path: &str, model_id: &str) -> bool {
        let path = CString::new(model_path).unwrap();
        let id = CString::new(model_id).unwrap();
        unsafe {
            nanoai_load_model_id(self.handle, path.as_ptr(), id.as_ptr())
        }
    }

    pub fn generate(&self, prompt: &str, model_id: &str) -> String {
        let input = CString::new(prompt).unwrap();
        let id = CString::new(model_id).unwrap();
        unsafe {
            let res = nanoai_generate_id(self.handle, input.as_ptr(), id.as_ptr());
            CStr::from_ptr(res).to_string_lossy().into_owned()
        }
    }

    pub fn get_detected_hardware(&self, model_id: &str) -> String {
        let id = CString::new(model_id).unwrap();
        unsafe {
            let res = nanoai_get_detected_hardware(self.handle, id.as_ptr());
            CStr::from_ptr(res).to_string_lossy().into_owned()
        }
    }

    pub fn convert_model(input_path: &str, output_path: &str, quantization_type: i32) -> bool {
        let input = CString::new(input_path).unwrap();
        let output = CString::new(output_path).unwrap();
        unsafe {
            nanoai_convert_model(input.as_ptr(), output.as_ptr(), quantization_type)
        }
    }
}

impl Drop for NanoRuntime {
    fn drop(&mut self) {
        unsafe {
            nanoai_destroy(self.handle);
        }
    }
}
