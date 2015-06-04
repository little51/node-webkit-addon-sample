#include <node.h>
#include <string>
#include <Windows.h>
#include <sstream>
#include <json.h>

using namespace v8;

std::string IntToStr(const int i) {
    std::string result;
    std::stringstream s;
    s << i;
    s >> result;
    return result;
}

std::string& trim(std::string &s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

void Proxy(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    v8::String::Utf8Value paramx(args[0]->ToString());
    std::string param1 = std::string(*paramx);
    //
    Json::Reader reader;
    Json::Value value;
    std::string functionname = "";
    if(reader.parse(param1, value)) {
        functionname= value["functionname"].asString();
    }
    std::string returnValue = "" ;
    if(functionname =="getDeviceID") {
        HINSTANCE hDLL;
        typedef char*(*pHDSerialNumRead)();
        hDLL = LoadLibrary("des.dll");
        pHDSerialNumRead ph=(pHDSerialNumRead)GetProcAddress(hDLL,"HDSerialNumRead");
		/*nw-gyp与node-gyp的行为不一样，nw-gyp里char*必须先copy到一个数组中，不然返回是乱码*/
        char* p = ph() ;
        char p1[30];
        strcpy(p1,p) ;
        std::string sno = p1 ;
        FreeLibrary(hDLL) ;
        returnValue = "{\"data\":[{\"ret_code\":\"1\",\"ret_desc\":\"" + trim(sno)+ "\"}],\"err\":\"\"}" ;
    } 
	else if(functionname == "getHospitalCode"){
		 returnValue = "{\"data\":[{\"ret_code\":\"1\",\"ret_desc\":\"00000011\"}],\"err\":\"\"}" ;
	}
	else {
        returnValue = "{\"data\":[{\"ret_code\":\"1\",\"ret_desc\":\"\"}],\"err\":\"\"}" ;
    }
    HandleScope scope(isolate);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, returnValue.c_str()));
}

void init(Handle<Object> exports) {
    NODE_SET_METHOD(exports, "proxy", Proxy);
}

NODE_MODULE(addon, init)