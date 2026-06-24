import 'dart:async';
import 'package:flutter/services.dart';

class NanoRuntime {
  static const MethodChannel _channel = MethodChannel('nanoai');

  Future<bool> loadModel(String path, String id) async {
    return await _channel.invokeMethod('loadModel', {'path': path, 'id': id});
  }

  Future<String> generate(String prompt, String id, int priority) async {
    return await _channel.invokeMethod('generate', {'prompt': prompt, 'id': id, 'priority': priority});
  }
}
