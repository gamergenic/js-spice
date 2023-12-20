#include <napi.h>
extern "C" {
  #include <SpiceUsr.h>  // Include the CSPICE header
}
#include <iostream>
#include <string>

Napi::Object HelloWorld(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::cout << "HelloWorld" << std::endl;

  // Load a kernel.
  // You need a kernel file that contains the necessary data.
  // You can download kernel files from the NAIF website.
  furnsh_c("D:\\gameassets\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
  furnsh_c("D:\\gameassets\\naif\\kernels\\Generic\\SPK\\planets\\de430.bsp");
  furnsh_c("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\gm_de431.tpc");
  furnsh_c("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\pck00010.tpc");

  // Specify the time for which you want to perform the calculation.
  // Use a string representing the time in UTC.
  std::string timeString = "2023-12-01T12:00:00";
  SpiceDouble et;
  str2et_c(timeString.c_str(), &et);

  // Compute the position of Mars relative to Earth.
  SpiceDouble position[3];
  SpiceDouble lightTime;
  spkpos_c("MARS BARYCENTER", et, "J2000", "NONE", "Earth", position, &lightTime);

  // Output the position.
  std::cout << "Position of Mars relative to Earth:" << std::endl;
  std::cout << "X: " << position[0] << " km" << std::endl;
  std::cout << "Y: " << position[1] << " km" << std::endl;
  std::cout << "Z: " << position[2] << " km" << std::endl;

  // Unload the kernel.
  unload_c("D:\\gameassets\\naif\\kernels\\Generic\\LSK\\latest_leapseconds.tls");
  unload_c("D:\\gameassets\\naif\\kernels\\Generic\\SPK\\de432s.bsp");
  unload_c("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\gm_de431.tpc");
  unload_c("D:\\gameassets\\naif\\kernels\\Generic\\PCK\\pck00010.tpc");

  Napi::Object obj = Napi::Object::New(env);

  // Assign values to properties
  obj.Set("x", position[0]);
  obj.Set("y", position[1]);
  obj.Set("z", position[2]);

  return obj;

//  return Napi::String::New(env, "Hello, world!");
}

