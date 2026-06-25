import { NativeModules } from 'react-native';
const { NanoAiModule } = NativeModules;

export class NanoRuntime {
  async loadModel(path: string, id: string): Promise<boolean> {
    return await NanoAiModule.loadModel(path, id);
  }
  async generate(prompt: string, id: string, priority: number): Promise<string> {
    return await NanoAiModule.generate(prompt, id, priority);
  }
}
