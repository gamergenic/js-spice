#include "utility/unpack.h"
#include <iomanip>
#include <sstream>
#include <iostream>

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

Unpacker& Unpacker::_unpackdouble3(const char* name1, const char* name2, const char* name3, SpiceDouble& v1, SpiceDouble& v2, SpiceDouble& v3){
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
    stream << "expected object {\"" << name1 << "\":" << name1 << ", \"";
    stream << name2 << "\":" << name2 << ", \"";
    stream << name3 << "\":" << name3  << "} at arg " << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackdouble3x3(SpiceDouble (&mat)[3][3], std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::stringstream dbg;

    if(remaining() > 0 && next().IsArray()){
        const uint32_t m = 3, n = 3;
        const Napi::Array inArray = next().As<Napi::Array>();

        dbg << inArray.Length() << " ";

        if(inArray.Length() == m){
            bool bSuccess = true;
            SpiceDouble temp[3][3];
            for(uint32_t i = 0; i < inArray.Length(); ++i){
                Napi::Value arrayValue = inArray.Get(i);
                bSuccess &= arrayValue.IsArray();
                if(bSuccess){
                    Napi::Array array = arrayValue.As<Napi::Array>();

                    dbg << array.Length() << std::endl;

                    bSuccess &= array.Length() == n;
                    if(bSuccess){
                        for(uint32_t j = 0; j < array.Length(); ++j){
                            Napi::Value rowValue = array.Get(j);
                            bSuccess &= rowValue.IsNumber();
                            if(bSuccess){
                                temp[i][j]= rowValue.As<Napi::Number>().DoubleValue();
                            }
                            if(!bSuccess) break;
                        }
                    }
                }
                if(!bSuccess) break;
            }
            if(bSuccess){
                memcpy(mat, temp, sizeof(mat));
                return advance();
            }
        }
    }

    std::cout << dbg.str();

    std::stringstream stream;
    stream << "expected 3x3 double-precision numeric array ([[a,b,c],[d,e,f],[g,h,i]]) ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());    
}

Unpacker& Unpacker::_unpackdouble(SpiceDouble& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsNumber()){
        value = next().As<Napi::Number>().DoubleValue();
        return advance();
    }

    std::cout << "_unpackdouble errored" << std::endl;

    std::stringstream stream;
    stream << "expected double-precision numeric ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackint(SpiceInt& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsNumber()){
        value = next().As<Napi::Number>().Int32Value();
        return advance();
    }

    std::cout << "_unpackint errored" << std::endl;

    std::stringstream stream;
    stream << "expected int (" << ((sizeof(int)) * 8) << "-bit) ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}


Unpacker& Unpacker::_unpackbool(SpiceBoolean& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsBoolean()){
        value = next().As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;
        return advance();
    }

    std::stringstream stream;
    stream << "expected bool ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackstring(std::string& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsString()){
        value = next().As<Napi::String>().Utf8Value();
        return advance();
    }

    std::cout << "__unpackstring errored" << std::endl;

    std::stringstream stream;
    stream << "expected string ";
    if(!name.empty()){
        stream << "'" << name  << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}

Unpacker Unpack(std::string _name, const Napi::CallbackInfo& _info){
    return Unpacker(_name, _info);
}
