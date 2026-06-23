use std::ffi::{CStr, CString};
use std::os::raw::{c_char, c_void, c_int};

type NanoaiRuntimeT = *mut c_void;

extern "C" {
    fn nanoai_create() -> NanoaiRuntimeT;
    fn nanoai_destroy(handle: NanoaiRuntimeT);
    fn nanoai_load_model(handle: NanoaiRuntimeT, model_path: *const c_char) -> bool;
    fn nanoai_generate(handle: NanoaiRuntimeT, prompt: *const c_char) -> *const c_char;
    fn nanoai_run_ocr(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
    fn nanoai_run_segmentation(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
    fn nanoai_detect_objects(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
    fn nanoai_analyze_face(handle: NanoaiRuntimeT, buffer: *const u8, width: c_int, height: c_int) -> *const c_char;
    fn nanoai_recognize_speech(handle: NanoaiRuntimeT, samples: *const f32, count: c_int) -> *const c_char;
    fn nanoai_detect_wake_word(handle: NanoaiRuntimeT, samples: *const f32, count: c_int) -> *const c_char;
    fn nanoai_summarize_text(handle: NanoaiRuntimeT, text: *const c_char) -> *const c_char;
    fn nanoai_translate_text(handle: NanoaiRuntimeT, text: *const c_char) -> *const c_char;
    fn nanoai_classify_text(handle: NanoaiRuntimeT, text: *const c_char) -> *const c_char;
    fn nanoai_convert_model(input_path: *const c_char, output_path: *const c_char, quant: c_int) -> bool;
}

pub struct NanoRuntime {
    handle: NanoaiRuntimeT,
}

impl NanoRuntime {
    pub fn new() -> Self {
        unsafe { Self { handle: nanoai_create() } }
    }

    pub fn load_model(&self, model_path: &str) -> bool {
        let c_path = CString::new(model_path).unwrap();
        unsafe { nanoai_load_model(self.handle, c_path.as_ptr()) }
    }

    pub fn generate(&self, prompt: &str) -> String {
        let c_prompt = CString::new(prompt).unwrap();
        unsafe {
            let result_ptr = nanoai_generate(self.handle, c_prompt.as_ptr());
            if result_ptr.is_null() { return String::new(); }
            CStr::from_ptr(result_ptr).to_string_lossy().into_owned()
        }
    }

    pub fn translate_text(&self, text: &str) -> String {
        let c_text = CString::new(text).unwrap();
        unsafe {
            let result_ptr = nanoai_translate_text(self.handle, c_text.as_ptr());
            if result_ptr.is_null() { return String::new(); }
            CStr::from_ptr(result_ptr).to_string_lossy().into_owned()
        }
    }

    pub fn classify_text(&self, text: &str) -> String {
        let c_text = CString::new(text).unwrap();
        unsafe {
            let result_ptr = nanoai_classify_text(self.handle, c_text.as_ptr());
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
