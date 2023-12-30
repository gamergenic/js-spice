// Copyright Gamergenic, LLC.  See full copyright notice and license in index.js.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com

#include "utility/unpack.h"
#include <utility>
#include <iomanip>
#include <sstream>

extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}

Unpacker::Unpacker(std::string _name, const Napi::CallbackInfo& _info) 
    : info(_info), name(_name)
{
}


Unpacker& Unpacker::_rec(SpiceDouble (&rec)[3], std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        std::stringstream stream;
        stream << "expected array [x, y, z], object {\"x\":x, \"y\":y, \"z\":z}, or 3 numeric args (x, y, z) ";
        if (!name.empty()) {
            stream << "'" << name << "' ";
        }
        stream << "at arg " << nextIndex + 1;
        return typeError(stream.str());
    };

    if (remaining() > 0) {
        if (next().IsArray()) {
            auto inArray = next().As<Napi::Array>();
            if (inArray.Length() == 3) {
                for (int i = 0; i < 3; ++i) {
                    if (!inArray.Get((uint32_t)i).IsNumber()) return errorOut();
                    rec[i] = inArray.Get((uint32_t)i).As<Napi::Number>().DoubleValue();
                }
                return advance();
            }
        } else if (next().IsObject()) {
            auto inObject = next().As<Napi::Object>();
            const char* keys[3] = {"x", "y", "z"};
            for (int i = 0; i < 3; ++i) {
                if (!inObject.HasOwnProperty(keys[i]) || !inObject.Get(keys[i]).IsNumber()) return errorOut();
                rec[i] = inObject.Get(keys[i]).As<Napi::Number>().DoubleValue();
            }
            return advance();
        } else if (remaining() >= 3) {
            for (int i = 0; i < 3; ++i) {
                if (!next((uint32_t)i).IsNumber()) return errorOut();
                rec[i] = next((uint32_t)i).As<Napi::Number>().DoubleValue();
            }
            return advance(3);
        }
    }
    return errorOut();
}


Unpacker& Unpacker::_unpackdouble3(const char* name1, const char* name2, const char* name3, SpiceDouble& v1, SpiceDouble& v2, SpiceDouble& v3) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        std::stringstream stream;
        stream << "expected object {\"" << name1 << "\":" << name1 << ", \"";
        stream << name2 << "\":" << name2 << ", \"";
        stream << name3 << "\":" << name3  << "} at arg " << nextIndex + 1;
        return typeError(stream.str());
    };

    if (remaining() <= 0 || !next().IsObject()) return errorOut();

    auto inObject = next().As<Napi::Object>();

    // Array of property names and references to the corresponding variables
    std::vector<std::pair<const char*, SpiceDouble&>> properties = {
        {name1, v1}, {name2, v2}, {name3, v3}
    };

    for (const auto& prop : properties) {
        if (!inObject.HasOwnProperty(prop.first) || !inObject.Get(prop.first).IsNumber()) {
            return errorOut();
        }
        prop.second = inObject.Get(prop.first).As<Napi::Number>().DoubleValue();
    }

    return advance();
}



Unpacker& Unpacker::_unpackquat(SpiceDouble (&quat)[4], std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        return typeError("object {\"w\":w, \"x\":x, \"y\":y, \"z\":z}", name);
    };

    if (remaining() <= 0 || !next().IsObject()) return errorOut();

    auto inObject = next().As<Napi::Object>();

    // Check for all required properties
    std::vector<std::string> properties = {"w", "x", "y", "z"};
    for (size_t i = 0; i < properties.size(); ++i) {
        if (!inObject.HasOwnProperty(properties[i]) || !inObject.Get(properties[i]).IsNumber()) {
            return errorOut();
        }
        quat[i] = inObject.Get(properties[i]).As<Napi::Number>().DoubleValue();
    }

    return advance();
}


Unpacker& Unpacker::_unpackdouble3x3(SpiceDouble (&mat)[3][3], std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        return typeError("3x3 double-precision numeric array ([[a,b,c],[d,e,f],[g,h,i]])", name);
    };

    if (remaining() <= 0 || !next().IsArray()) return errorOut();

    const uint32_t m = 3, n = 3;
    auto inArray = next().As<Napi::Array>();

    if (inArray.Length() != m) return errorOut();

    SpiceDouble temp[3][3];
    bool isValid = true;

    for (uint32_t i = 0; i < m; ++i) {
        auto arrayValue = inArray.Get(i);
        if (!arrayValue.IsArray()) {
            isValid = false;
            break;
        }
        auto array = arrayValue.As<Napi::Array>();

        if (array.Length() != n) {
            isValid = false;
            break;
        }

        for (uint32_t j = 0; j < n; ++j) {
            auto rowValue = array.Get(j);
            if (!rowValue.IsNumber()) {
                isValid = false;
                break;
            }
            temp[i][j] = rowValue.As<Napi::Number>().DoubleValue();
        }
        if (!isValid) break;
    }

    if (isValid) {
        std::memcpy(mat, temp, sizeof(mat));
        return advance();
    } else {
        return errorOut();
    }
}


Unpacker& Unpacker::_unpackdouble(SpiceDouble& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsNumber()){
        value = next().As<Napi::Number>().DoubleValue();
        return advance();
    }

    return typeError("double-precision numeric", name);    
}

Unpacker& Unpacker::_unpackint(SpiceInt& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsNumber()){
        value = next().As<Napi::Number>().Int32Value();
        return advance();
    }

    std::stringstream argType;
    argType << "int (" << ((sizeof(int)) * 8) << "-bit)";
    return typeError(argType.str(), name);
}

Unpacker& Unpacker::_unpackplane(SpicePlane& spiceplane, std::string){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Locally scoped lambda 'earlyOut' for error handling
    auto earlyOut = [&]() -> Unpacker& {
        return typeError("plane", name);
    };

    // Validate there's an unpacked argument that that it's an object
    if(remaining() <= 0 || !next().IsObject()) return earlyOut();

    auto inObject = next().As<Napi::Object>();

    // Validate he object has "normal" and "constant" properties
    if(!inObject.HasOwnProperty("normal") || !inObject.HasOwnProperty("constant")){
        return earlyOut();
    }

    auto normalValue =  inObject.Get("normal");  
    auto constantValue =  inObject.Get("constant");

    // Validate the normal is an array and the constant is a number
    if(!normalValue.IsArray() || !constantValue.IsNumber()) return earlyOut();

    auto normalArray =  normalValue.As<Napi::Array>();  
    auto constantNumber =  constantValue.As<Napi::Number>();

    // Validate the normal array has 3 members
    if(normalArray.Length() != 3) return earlyOut();

    for(uint32_t i = 0; i < 3; ++i){
        if(!normalArray.Get(i).IsNumber()){
            return earlyOut();
        }
    }

    SpiceDouble normal[3];
    for(uint32_t i = 0; i < 3; ++i){
        normal[i] = normalArray.Get(i).As<Napi::Number>().DoubleValue();
    }
    
    SpiceDouble constant = constantNumber.DoubleValue();
    nvc2pl_c(normal, constant, &spiceplane);
    return advance();
}


Unpacker& Unpacker::_unpackbool(SpiceBoolean& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsBoolean()){
        value = next().As<Napi::Boolean>().Value() ? SPICETRUE : SPICEFALSE;
        return advance();
    }

    return typeError("bool", name);    
}

Unpacker& Unpacker::_unpackstring(std::string& value, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsString()){
        value = next().As<Napi::String>().Utf8Value();
        return advance();
    }

    return typeError("string", name);    
}

template<int size>
Unpacker& Unpacker::_unpackelts(SpiceDouble (&elts)[size], std::string (&members)[size], std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Locally scoped lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        std::stringstream argName;
        argName << "object {";
        for (int i = 0; i < size; ++i) {
            if (i > 0) {
                argName << ", ";
            }
            argName << "\"" << members[i] << "\":" << members[i];
        }
        argName << "}";
        return typeError(argName.str(), name);
    };

    // Early exit if no remaining elements or the next element is not an object
    if (remaining() <= 0 || !next().IsObject()) return errorOut();

    auto inObject = next().As<Napi::Object>();
    SpiceDouble temp[size];
    bool isValid = true;

    for (int i = 0; i < size; ++i) {
        if (!inObject.HasOwnProperty(members[i])) {
            isValid = false;
            break;
        }
        Napi::Value memberValue = inObject.Get(members[i]);
        if (!memberValue.IsNumber()) {
            isValid = false;
            break;
        }
        temp[i] = memberValue.As<Napi::Number>().DoubleValue();
    }

    if (isValid) {
        std::memcpy(elts, temp, sizeof elts);
        return advance();
    } else {
        return errorOut();
    }
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

Unpacker& Unpacker::_unpackeulers(SpiceDouble& angle3, SpiceDouble& angle2, SpiceDouble& angle1, SpiceInt& axis3, SpiceInt& axis2, SpiceInt& axis1){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    auto errorOut = [&]() -> Unpacker& {
        std::stringstream argName;
        argName << "object {\"angle3\":a, \"angle2\":b, \"angle1\":c, \"axis3\":e, \"axis2\":e, \"axis1\":f }";
        return typeError(argName.str(), name);
    };

    if (remaining() <= 0 || !next().IsObject()) return errorOut();
    
    Napi::Object inObject = next().As<Napi::Object>();

    std::vector<std::string> properties = {"angle3", "angle2", "angle1", "axis3", "axis2", "axis1"};
    Napi::Number values[6];
    for (size_t i = 0; i < properties.size(); ++i) {
        if (!inObject.HasOwnProperty(properties[i]) || !inObject.Get(properties[i]).IsNumber()) {
            return errorOut();
        }
        values[i] = inObject.Get(properties[i]).As<Napi::Number>();
    }

    angle3 = values[0].DoubleValue();
    angle2 = values[1].DoubleValue();
    angle1 = values[2].DoubleValue();
    axis3  = values[3].Int32Value();
    axis2  = values[4].Int32Value();
    axis1  = values[5].Int32Value();

    return advance();
}


Unpacker& Unpacker::_unpackstate(SpiceDouble (&state)[6], std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // Lambda for error handling
    auto errorOut = [&]() -> Unpacker& {
        std::stringstream argName;
        argName << "object {\"r\":[x, y, z], \"v\":[dx, dy, dz]}";
        return typeError(argName.str(), name);
    };

    if (remaining() > 0) {
        Napi::Array rArray, vArray;

        if (next().IsObject()) {
            auto inObject = next().As<Napi::Object>();
            if (inObject.HasOwnProperty("r") && inObject.Get("r").IsArray() &&
                inObject.HasOwnProperty("v") && inObject.Get("v").IsArray()) {
                rArray = inObject.Get("r").As<Napi::Array>();
                vArray = inObject.Get("v").As<Napi::Array>();
            } else {
                return errorOut();
            }
        } else if (next().IsArray()) {
            auto inArray = next().As<Napi::Array>();
            if (inArray.Length() == 2 && inArray.Get((uint32_t)0).IsArray() && inArray.Get((uint32_t)1).IsArray()) {
                rArray = inArray.Get((uint32_t)0).As<Napi::Array>();
                vArray = inArray.Get((uint32_t)1).As<Napi::Array>();
            } else {
                return errorOut();
            }
        } else {
            return errorOut();
        }

        if (rArray.Length() == 3 && vArray.Length() == 3) {
            for (uint32_t i = 0; i < 3; ++i) {
                if (!rArray.Get(i).IsNumber() || !vArray.Get(i).IsNumber()) return errorOut();
                state[i] = rArray.Get(i).As<Napi::Number>().DoubleValue();
                state[3 + i] = vArray.Get(i).As<Napi::Number>().DoubleValue();
            }
            return advance();
        }
    }

    return errorOut();
}


Unpacker& Unpacker::_getarray(Napi::Array& array, std::string name){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(remaining() > 0 && next().IsArray()){
        array = next().As<Napi::Array>();
        return advance();
    }

    return typeError("array", name);      
}


Unpacker& Unpacker::_windows(std::vector<std::pair<SpiceDouble, SpiceDouble>>& cnfine_vector, SpiceDouble& totalWindow, std::string name) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    auto errorOut = [&](const std::string& errorMessage) -> Unpacker& {
        return error(name + " " + errorMessage);
    };

    if (remaining() > 0 && next().IsArray()) {
        auto cnfine_array = next().As<Napi::Array>();

        totalWindow = 0;
        std::vector<std::pair<SpiceDouble, SpiceDouble>> cnfine_temp;

        for (uint32_t i = 0; i < cnfine_array.Length(); ++i) {
            auto val = cnfine_array.Get(i);
            double start, stop;

            if (val.IsArray()) {
                auto arr = val.As<Napi::Array>();
                if (arr.Length() != 2 || !arr.Get((uint32_t)0).IsNumber() || !arr.Get((uint32_t)1).IsNumber()) {
                    return errorOut("expected confinement window array child array [x, y]");
                }
                start = arr.Get((uint32_t)0).As<Napi::Number>().DoubleValue();
                stop = arr.Get((uint32_t)1).As<Napi::Number>().DoubleValue();
            } else if (val.IsObject()) {
                auto obj = val.As<Napi::Object>();
                if (!obj.HasOwnProperty("start") || !obj.Get("start").IsNumber() ||
                    !obj.HasOwnProperty("stop") || !obj.Get("stop").IsNumber()) {
                    return errorOut("expected confinement window array member object { start: x, stop: y }");
                }
                start = obj.Get("start").As<Napi::Number>().DoubleValue();
                stop = obj.Get("stop").As<Napi::Number>().DoubleValue();
            } else {
                return errorOut("expected confinement window array member as object { start: x, stop: y } or array [x, y]");
            }

            if (start >= stop) {
                return errorOut("expected confinement window start < stop");
            }
            cnfine_temp.emplace_back(start, stop);
            totalWindow += stop - start;
        }

        cnfine_vector = std::move(cnfine_temp);
        return advance();
    }

    return typeError("array in form of [[val1, val2], ...]", name);
}


Unpacker Unpack(std::string _name, const Napi::CallbackInfo& _info){
    return Unpacker(_name, _info);
}
