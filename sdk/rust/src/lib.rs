use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_void, c_int};

extern "C" {
    fn nanoai_create() -> *mut c_void;
    fn nanoai_destroy(handle: *mut c_void);
    fn nanoai_load_model(handle: *mut c_void, model_path: *const c_char, model_id: *const c_char) -> bool;
    fn nanoai_generate(handle: *mut c_void, prompt: *const c_char, model_id: *const c_char, priority: c_int) -> *const c_char;
    fn nanoai_get_runtime_telemetry(handle: *mut c_void) -> *const c_char;
    fn nanoai_get_hardware_profile(handle: *mut c_void) -> *const c_char;
    fn nanoai_get_cluster_nodes(handle: *mut c_void) -> *const c_char;
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
            nanoai_load_model(self.handle, path.as_ptr(), id.as_ptr())
        }
    }

    pub fn generate(&self, prompt: &str, model_id: &str, priority: i32) -> String {
        let input = CString::new(prompt).unwrap();
        let id = CString::new(id).unwrap();
        unsafe {
            let res = nanoai_generate(self.handle, input.as_ptr(), id.as_ptr(), priority);
            CStr::from_ptr(res).to_string_lossy().into_owned()
        }
    }

    pub fn get_telemetry(&self) -> String {
        unsafe {
            let res = nanoai_get_runtime_telemetry(self.handle);
            CStr::from_ptr(res).to_string_lossy().into_owned()
        }
    }

    pub fn get_hardware_profile(&self) -> String {
        unsafe {
            let res = nanoai_get_hardware_profile(self.handle);
            CStr::from_ptr(res).to_string_lossy().into_owned()
        }
    }

    pub fn get_cluster_nodes(&self) -> String {
        unsafe {
            let res = nanoai_get_cluster_nodes(self.handle);
            CStr::from_ptr(res).to_string_lossy().into_owned()
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
