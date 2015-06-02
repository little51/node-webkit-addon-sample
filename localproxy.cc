#include <node.h>
#include <string>
#include <Windows.h>

using namespace v8;

void Proxy(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  v8::String::Utf8Value param1(args[0]->ToString());
  std::string from = std::string(*param1);
  //  
  MessageBoxW(NULL,L"message!",L"ok", MB_OK);
  //
  from += "返回return" ;
  HandleScope scope(isolate);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, from.c_str()));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "proxy", Proxy);
}

NODE_MODULE(addon, init)