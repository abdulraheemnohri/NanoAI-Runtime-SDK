use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_void, c_int};

#[link(name = "nanoai")]
extern "C" {
    fn nanoai_create() -> *mut c_void;
    fn nanoai_destroy(handle: *mut c_void);
    fn nanoai_string_free(str: *mut c_char);
    fn nanoai_load_model(handle: *mut c_void, model_path: *const c_char, model_id: *const c_char) -> bool;
    fn nanoai_generate(handle: *mut c_void, prompt: *const c_char, model_id: *const c_char, priority: c_int) -> *mut c_char;
    fn nanoai_run_swarm(handle: *mut c_void, task_name: *const c_char, agents: *const *const c_char, agent_count: c_int, input: *const c_char) -> *mut c_char;
    fn nanoai_run_workflow(handle: *mut c_void, workflow_json: *const c_char, input: *const c_char) -> *mut c_char;
    fn nanoai_os_boot(handle: *mut c_void) -> bool;
    fn nanoai_os_dispatch(handle: *mut c_void, task: *const c_char) -> *mut c_char;
    fn nanoai_get_runtime_telemetry(handle: *mut c_void) -> *mut c_char;
    fn nanoai_get_hardware_profile(handle: *mut c_void) -> *mut c_char;
    fn nanoai_get_cluster_nodes(handle: *mut c_void) -> *mut c_char;
}

unsafe fn decode_and_free(ptr: *mut c_char) -> String {
    if ptr.is_null() {
        return String::new();
    }
    let s = CStr::from_ptr(ptr).to_string_lossy().into_owned();
    nanoai_string_free(ptr);
    s
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

    pub fn close(&mut self) {
        if !self.handle.is_null() {
            unsafe {
                nanoai_destroy(self.handle);
            }
            self.handle = std::ptr::null_mut();
        }
    }

    pub fn generate(&self, prompt: &str, model_id: &str, priority: i32) -> String {
        let input = CString::new(prompt).unwrap();
        let id = CString::new(model_id).unwrap();
        unsafe {
            let res = nanoai_generate(self.handle, input.as_ptr(), id.as_ptr(), priority);
            decode_and_free(res)
        }
    }

    pub fn run_swarm(&self, task_name: &str, agents: &[&str], input: &str) -> String {
        let task = CString::new(task_name).unwrap();
        let input = CString::new(input).unwrap();
        let agent_strings: Vec<CString> = agents
            .iter()
            .map(|agent| CString::new(*agent).unwrap())
            .collect();
        let agent_ptrs: Vec<*const c_char> = agent_strings
            .iter()
            .map(|agent| agent.as_ptr())
            .collect();

        unsafe {
            let res = nanoai_run_swarm(
                self.handle,
                task.as_ptr(),
                agent_ptrs.as_ptr(),
                agent_ptrs.len() as c_int,
                input.as_ptr(),
            );
            decode_and_free(res)
        }
    }

    pub fn run_workflow(&self, workflow_json: &str, input: &str) -> String {
        let workflow = CString::new(workflow_json).unwrap();
        let input = CString::new(input).unwrap();
        unsafe {
            let res = nanoai_run_workflow(self.handle, workflow.as_ptr(), input.as_ptr());
            decode_and_free(res)
        }
    }

    pub fn boot_os(&self) -> bool {
        unsafe { nanoai_os_boot(self.handle) }
    }

    pub fn os_dispatch(&self, task: &str) -> String {
        let task = CString::new(task).unwrap();
        unsafe {
            let res = nanoai_os_dispatch(self.handle, task.as_ptr());
            decode_and_free(res)
        }
    }

    pub fn get_runtime_telemetry(&self) -> String {
        unsafe {
            let res = nanoai_get_runtime_telemetry(self.handle);
            decode_and_free(res)
        }
    }

    pub fn get_telemetry(&self) -> String {
        self.get_runtime_telemetry()
    }

    pub fn get_hardware_profile(&self) -> String {
        unsafe {
            let res = nanoai_get_hardware_profile(self.handle);
            decode_and_free(res)
        }
    }

    pub fn get_cluster_nodes(&self) -> String {
        unsafe {
            let res = nanoai_get_cluster_nodes(self.handle);
            decode_and_free(res)
        }
    }
}

impl Drop for NanoRuntime {
    fn drop(&mut self) {
        self.close();
    }
}
