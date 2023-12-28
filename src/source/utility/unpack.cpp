// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "utility/unpack.h"
#include <utility>
#include <iomanip>
#include <sstream>

Unpacker::Unpacker(std::string _name, const Napi::CallbackInfo& _info) 
    : info(_info), name(_name)
{
}


Unpacker& Unpacker::_rec(SpiceDouble (&rec)[3], std::string name){
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
    stream << "expected array [x, y, z], object {\"x\":x, \"y\":y, \"z\":z}, or 3 numeric args (x, y, z) ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }    
    stream << "at arg ";
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


Unpacker& Unpacker::_unpackquat(SpiceDouble (&quat)[4], std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(remaining() > 0 && next().IsObject()){
        const Napi::Object inObject = next().As<Napi::Object>();

        bool bIsQuat = true;
        bIsQuat &= inObject.HasOwnProperty("w");
        bIsQuat &= inObject.HasOwnProperty("x");
        bIsQuat &= inObject.HasOwnProperty("y");
        bIsQuat &= inObject.HasOwnProperty("z");
        if(bIsQuat){
            const Napi::Value wValue = inObject.Get("w");       
            const Napi::Value xValue = inObject.Get("x");       
            const Napi::Value yValue = inObject.Get("y");
            const Napi::Value zValue = inObject.Get("z");
            bIsQuat &= wValue.IsNumber();       
            bIsQuat &= xValue.IsNumber();       
            bIsQuat &= yValue.IsNumber();       
            bIsQuat &= zValue.IsNumber();       
            if(bIsQuat){
                quat[0] = wValue.As<Napi::Number>().DoubleValue();
                quat[1] = xValue.As<Napi::Number>().DoubleValue();
                quat[2] = yValue.As<Napi::Number>().DoubleValue();
                quat[3] = zValue.As<Napi::Number>().DoubleValue();
                return advance();
            }
        }
    }

    std::stringstream stream;
    stream << "expected object {\"w\":w, \"x\":x, \"y\":y, \"z\":z} ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
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

    std::stringstream stream;
    stream << "expected string ";
    if(!name.empty()){
        stream << "'" << name  << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}

template<int size>
Unpacker& Unpacker::_unpackelts(SpiceDouble (&elts)[size], std::string (&members)[size], std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    SpiceDouble temp[size];
    if(remaining() > 0 && next().IsObject()){

        const Napi::Object inObject = next().As<Napi::Object>();

        bool bIsEltsObject = true;
        for(int i = 0; i < size; ++i){
            bIsEltsObject &= inObject.HasOwnProperty(members[i]);
            if(bIsEltsObject){
                const Napi::Value memberValue = inObject.Get(members[i]);
                bIsEltsObject &= memberValue.IsNumber();
                if(bIsEltsObject){
                    temp[i] = memberValue.As<Napi::Number>().DoubleValue();
                }
            }
            if(!bIsEltsObject) break;
        }

        if(bIsEltsObject){
            memcpy(elts, temp, sizeof elts);
            return advance();
        }
    }

    std::stringstream stream;
    stream << "expected object {";

    for(int i = 0; i < size; ++i){
        if(i > 0){
            stream << ", ";
        }
        stream << "\"" << members[i] << "\":" << members[i];
    }

    stream << "} ";

    if(!name.empty()){
        stream << "'" << name  << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());
}

Unpacker& Unpacker::_unpackconics(SpiceDouble (&elts)[8]){
    std::string members[] {"rp", "ecc", "inc", "lnode", "argp", "m0", "t0", "mu"};
    return _unpackelts(elts, members, "elts");
}


Unpacker& Unpacker::_unpackgeophs(SpiceDouble (&elts)[8]){
    std::string members[] {"j2", "j3", "j4", "ke", "qo", "so", "er", "ae"};
    return _unpackelts(elts, members, "geophs");
}

Unpacker& Unpacker::_unpackelems(SpiceDouble (&elems)[10]){
    std::string members[] {"ndt20", "ndd60", "bstar", "incl", "node0", "ecc", "omega", "m0", "n0", "epoch"};
    return _unpackelts(elems, members, "elems");
}


Unpacker& Unpacker::_unpackstate(SpiceDouble (&state)[6], std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    
    if(remaining() > 0 && next().IsObject()){
        const Napi::Object inObject = next().As<Napi::Object>();
        if(inObject.HasOwnProperty("r") && inObject.HasOwnProperty("v")){
            const Napi::Value rValue = inObject.Get("r");
            const Napi::Value vValue = inObject.Get("v");
            if(rValue.IsArray() && vValue.IsArray()){
                const Napi::Array rArray = rValue.As<Napi::Array>();
                const Napi::Array vArray = vValue.As<Napi::Array>();
                if(rArray.Length() == 3 && vArray.Length() == 3){
                    bool bIsState = true;
                    SpiceDouble temp[6];
                    for(uint32_t i = 0; i < 3; ++i){
                        const Napi::Value rMember = rArray.Get(i);
                        const Napi::Value vMember = vArray.Get(i);

                        bIsState &= rMember.IsNumber() && vMember.IsNumber();
                        if(bIsState){
                            temp[i] = rMember.As<Napi::Number>().DoubleValue();
                            temp[3 + i] = vMember.As<Napi::Number>().DoubleValue();
                        }
                        else {
                            break;
                        }
                    }

                    if(bIsState){
                        memcpy(state, temp, sizeof state);
                        return advance();
                    }
                }
            }
        }
    }

    std::stringstream stream;
    stream << "expected object {\"r\":[x, y, z], \"v\":[dx, dy, dz]} ";
    if(!name.empty()){
        stream << "'" << name << "' ";
    }
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());      
}

Unpacker& Unpacker::_getarray(Napi::Array& array, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsArray()){
        array = next().As<Napi::Array>();
        return advance();
    }

    std::stringstream stream;
    stream << "expected array ";
    if(!name.empty()){
        stream << "'" << name  << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());    
}


Unpacker& Unpacker::_windows(std::vector<std::pair<SpiceDouble, SpiceDouble>>& cnfine_vector, SpiceDouble& totalWindow, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsArray()){
        Napi::Array  cnfine_array = next().As<Napi::Array>();

        totalWindow = 0;
        std::vector<std::pair<SpiceDouble, SpiceDouble>> cnfine_temp;
        
        for(uint32_t i = 0; i < cnfine_array.Length(); ++i){
            Napi::Value val = cnfine_array.Get(i);
            double start, stop;
            if (val.IsArray()){
                Napi::Array arr = val.As<Napi::Array>();

                bool bArrayIsValid = true;
                bArrayIsValid &= arr.Length() == 2;
                if(bArrayIsValid){
                    Napi::Value startValue = arr.Get((uint32_t)0);
                    Napi::Value stopValue = arr.Get((uint32_t)1);
                    bArrayIsValid &= startValue.IsNumber();
                    bArrayIsValid &= stopValue.IsNumber();
                    if(bArrayIsValid){
                        start = startValue.As<Napi::Number>().DoubleValue();
                        stop = stopValue.As<Napi::Number>().DoubleValue();
                    }
                }
                if(!bArrayIsValid){
                    return error(name + " expected confinement window array child array [x, y]");
                }
            }
            else if(val.IsObject()){
                Napi::Object obj = val.As<Napi::Object>();
                bool bObjectIsValid = true;
                bObjectIsValid &= obj.HasOwnProperty("start");
                bObjectIsValid &= obj.HasOwnProperty("stop");
                if(bObjectIsValid){
                    Napi::Value startValue = obj.Get("start");
                    bObjectIsValid &= startValue.IsNumber();
                    if(bObjectIsValid){
                        start = startValue.As<Napi::Number>().DoubleValue();
                    }
                }
                if(bObjectIsValid){
                    Napi::Value stopValue = obj.Get("stop");
                    bObjectIsValid &= stopValue.IsNumber();
                    if(bObjectIsValid){
                        stop = stopValue.As<Napi::Number>().DoubleValue();
                    }
                }
                if(!bObjectIsValid){
                    return error(name + " expected confinement window array member object { start: x, stop: y }");
                }
            }
            else {
                return error(name + " expected confinement window array member as object { start: x, stop: y} or array [x, y]");
            }
            if(start >= stop){
                return error(name + " expected confinement window start < stop");
            }
            cnfine_temp.push_back(std::pair(start, stop));
            totalWindow += stop - start;
        }    

        cnfine_vector = cnfine_temp;
        return advance();
    }    
    
    std::stringstream stream;
    stream << "expected array ";
    if(!name.empty()){
        stream << "'" << name  << "' ";
    }    
    stream << "at arg " << nextIndex + 1;
    return error(stream.str());        
}

Unpacker Unpack(std::string _name, const Napi::CallbackInfo& _info){
    return Unpacker(_name, _info);
}
