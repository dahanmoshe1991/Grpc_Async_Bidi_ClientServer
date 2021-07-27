# GRpc_Async_Client_Server
## C++ client - C# server implementation over grpc connection with async unary and Bidiractional stream messages


This solution is include async Unary & Bidirectional messages implematation for C++ client & C# server.
During my research, I found the grpc documentation is lacking. Therefore, I'm releasing my working version.

 ✨ ✨

## Features

- C++ client
- C# server
- Unary messages
- Async Unary Messages (using completion queue)
- Bidirectional Stream Messages.

##### *Please refer to the Class diagram for a better understanding of the working interface*


## Grpc

### - Documentation

- [Website](https://grpc.io/) - Official documentation, libraries, resources, samples and FAQ
- [Technical documentation](https://github.com/grpc/grpc/tree/master/doc) - Collection of useful technical documentation
- [gRPC status codes](https://github.com/grpc/grpc/blob/master/doc/statuscodes.md) - Status codes and their use in gRPC
- [gRPC status code mapping](https://github.com/grpc/grpc/blob/master/doc/http-grpc-status-mapping.md) - HTTP to gRPC Status Code Mapping
- [grpc-errors](https://github.com/avinassh/grpc-errors) - Code examples in each language on how to return and handle error statuses.
- [API Design Guide](https://cloud.google.com/apis/design/) - Google Cloud API Design Guide useful for gRPC API design insights

### - Community

- [Community links](https://grpc.io/community/) - Mailing list, Gitter, Twitter, Reddit

# Installation
##### If you want to create a grpc c++ project follow this:
First, install vcpkg package manager on your system using the official instructions:
in powerShell:
```sh
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
```
Depanding on your OS:
1. Bootstrap on Linux:
```sh
./bootstrap-vcpkg.sh
```
2. Bootstrap on Windows instead:
```sh
 ./bootstrap-vcpkg.bat
```

Next, install gRPC using vcpkg package manager:
```sh
./vcpkg install grpc
```
for user wide integration use:
```sh
 vcpkg integrate install
 ```
for specific project integration use:
```sh
vcpkg integrate project
 ```
follow instructions output in Powershell 
With a project open, go to Tools->NuGet Package Manager->Package Manager Console and paste:
Install-Package ****** -Source "****\vcpkg\scripts\buildsystems"
(replace ** with powershell output)

After grpc installed -> update googlePath macro to vcpckg installation location + "installed\x64-windows\include" (choose your relavant os folder)

##### If you want to create a grpc c# project follow this:
- [microsoft C# grpc tutorial](https://docs.microsoft.com/en-us/aspnet/core/tutorials/grpc/grpc-start?view=aspnetcore-5.0&tabs=visual-studio)

## Generate grpc stub files

In order to use grpc communication(Google's Protocol Buffers) we need to define a service, specifying the 
methods that can be called remotely with their parameters and return types.

we do this inside our .proto  files. To learn more about protocol buffers see the [protocol buffers documentation](https://developers.google.com/protocol-buffers/docs/overview)

gRPC uses *protoc* with a special gRPC plugin to generate code from your proto file.

use these commands to generate c++ code:
```sh
$(protobufPath)protoc -I=$(protosPath) -I $(googlePath) --cpp_out=$(ProjectDir)Generated $(protosPath)*.proto
$(protobufPath)protoc -I $(protosPath) -I $(googlePath) --grpc_out=$(ProjectDir)Generated --plugin=protoc-gen-grpc=$(grpcPath)grpc_cpp_plugin.exe $(protosPath)*.proto 
 ```
 
 where :
 - protobufPath -> protoc.exe location inside installed grpc
 - protosPath -> location of \*.proto files to generate from.
 - googlePath -> vcpckg installation location + "installed\x64-windows\include"
 - --cpp_out/--grpc_out -> output location
 - grpcPath -> googlePath + \grpc\x64-windows\tools\grpc\
### recommendation 
 Insert the above lines as a preBuild event to always keep your source code up to date.
 
## License

MIT

