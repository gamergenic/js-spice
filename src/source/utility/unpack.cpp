#include "utility/unpack.h"
#include <iomanip>
#include <sstream>

Unpacker::Unpacker(std::string _name, const Napi::CallbackInfo& _info) 
    : info(_info), name(_name)
{
}


Unpacker& Unpacker::_rec(SpiceDouble (&rec)[3]){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsArray()){
        const Napi::Array inArray = next().As<Napi::Array>();

        bool bIsVectorArray = inArray.Length() == 3;
        if(bIsVectorArray){
            const Napi::Value xValue = inArray.Get((uint32_t)0);       
            const Napi::Value yValue = inArray.Get((uint32_t)1);       
            const Napi::Value zValue = inArray.Get((uint32_t)2);
            bIsVectorArray &= xValue.IsNumber();       
            bIsVectorArray &= yValue.IsNumber();       
            bIsVectorArray &= zValue.IsNumber();       
            if(bIsVectorArray){
                rec[0] = xValue.As<Napi::Number>().DoubleValue();
                rec[1] = yValue.As<Napi::Number>().DoubleValue();
                rec[2] = zValue.As<Napi::Number>().DoubleValue();
                return advance();
            }
        }
    }
    else if(remaining() > 0 && next().IsObject()) {
        const Napi::Object inObject = next().As<Napi::Object>();

        bool bIsVectorObject = true;
        bIsVectorObject &= inObject.HasOwnProperty("x");
        bIsVectorObject &= inObject.HasOwnProperty("y");
        bIsVectorObject &= inObject.HasOwnProperty("z");
        if(bIsVectorObject){
            const Napi::Value xValue = inObject.Get("x");       
            const Napi::Value yValue = inObject.Get("y");       
            const Napi::Value zValue = inObject.Get("z");
            bIsVectorObject &= xValue.IsNumber();       
            bIsVectorObject &= yValue.IsNumber();       
            bIsVectorObject &= zValue.IsNumber();       
            if(bIsVectorObject){
                rec[0] = xValue.As<Napi::Number>().DoubleValue();
                rec[1] = yValue.As<Napi::Number>().DoubleValue();
                rec[2] = zValue.As<Napi::Number>().DoubleValue();
                return advance();
            }
        }
    }
    else if (remaining() >= 3){
        if(next(0).IsNumber() && next(1).IsNumber() && next(2).IsNumber()){
            rec[0] = next(0).As<Napi::Number>().DoubleValue();
            rec[1] = next(1).As<Napi::Number>().DoubleValue();
            rec[2] = next(2).As<Napi::Number>().DoubleValue();
            return advance(3);
        }
    }

    std::stringstream stream;
    stream << "expected array [x, y, z], object {\"x\":x, \"y\":y, \"z\":z}, or 3 numeric args (x, y, z) at arg ";
    stream << nextIndex + 1;
    return error(stream.str());    
}

Unpacker& Unpacker::_unpackdouble3(const char* name1, const char* name2, const char* name3, double& v1, double& v2, double& v3){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(remaining() > 0 && next().IsObject()){
        const Napi::Object inObject = next().As<Napi::Object>();

        bool bIsVectorObject = true;
        bIsVectorObject &= inObject.HasOwnProperty(name1);
        bIsVectorObject &= inObject.HasOwnProperty(name2);
        bIsVectorObject &= inObject.HasOwnProperty(name3);
        if(bIsVectorObject){
            const Napi::Value v1Value = inObject.Get(name1);       
            const Napi::Value v2Value = inObject.Get(name2);       
            const Napi::Value v3Value = inObject.Get(name3);
            bIsVectorObject &= v1Value.IsNumber();       
            bIsVectorObject &= v2Value.IsNumber();       
            bIsVectorObject &= v3Value.IsNumber();       
            if(bIsVectorObject){
                v1 = v1Value.As<Napi::Number>().DoubleValue();
                v2 = v2Value.As<Napi::Number>().DoubleValue();
                v3 = v3Value.As<Napi::Number>().DoubleValue();
                return advance();
            }
        }
    }

    std::stringstream stream;
    stream << "expected object {\"";
    stream << name1;
    stream << "\":";
    stream << name1;
    stream << ", \"";
    stream << name2;
    stream << "\":";
    stream << name2;
    stream << ", \"";
    stream << name3;
    stream << "\":";
    stream << name3;
    stream << "} at arg ";
    stream << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackdouble(double& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsNumber()){
        value = next().As<Napi::Number>().DoubleValue();
        return advance();
    }

    std::stringstream stream;
    stream << "expected double-precision numeric ";
    if(!name.empty()){
        stream << "'";
        stream << name;
        stream << "' ";
    }
    stream << "at arg ";
    stream << nextIndex + 1;
    return error(stream.str());
}


Unpacker& Unpacker::_unpackbool(bool& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsBoolean()){
        value = next().As<Napi::Boolean>().Value();
        return advance();
    }

    std::stringstream stream;
    stream << "expected bool ";
    if(!name.empty()){
        stream << "'";
        stream << name;
        stream << "' ";
    }    
    stream << "at arg ";
    stream << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackstring(std::string& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsString()){
        value = next().As<Napi::String>().Utf8Value();
        return advance();
    }

    std::stringstream stream;
    stream << "expected string ";
    if(!name.empty()){
        stream << "'";
        stream << name;
        stream << "' ";
    }    
    stream << "at arg ";
    stream << nextIndex + 1;
    return error(stream.str());
}

Unpacker Unpack(std::string _name, const Napi::CallbackInfo& _info){
    return Unpacker(_name, _info);
}
