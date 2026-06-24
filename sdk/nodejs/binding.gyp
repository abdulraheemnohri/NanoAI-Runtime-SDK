{
  "targets": [
    {
      "target_name": "nanoai",
      "sources": ["src/nanoai_node.cc"],
      "include_dirs": ["<(module_root_dir)/../../core/include"],
      "cflags_cc": ["-std=c++17"],
      "libraries": ["-L<(module_root_dir)/../../build", "-lnanoai"],
      "ldflags": ["-Wl,-rpath,<(module_root_dir)/../../build"]
    }
  ]
}
