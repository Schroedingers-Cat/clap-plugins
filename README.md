# Clap Plugin Examples

This repo contains some example CLAP plugins.

## Building on various platforms

### Windows

WARNING: Make sure that you've cloned this repository into a short path to avoid running into the 255 character path limit later on. The repository's default name `clap-plugins` placed into the root of a drive would already be too long! Clone or rename it to something like `C:\clappl` or `D:\clappl`.  

In case you haven't already, install the necessary tools:
```powershell
choco install cmake -y
```

Dependencies on Windows are managed by vcpkg through CMake. For that to work, you'll have to init and checkout all submodules, which includes vcpkg:
```powershell
git submodule init
git submodule update
```

You can now open the project with CMake, select the `Visual Studio + VCPKG` preset and configure & generate the solutions (tested with VS 2019). CMake should be able to automatically detect vcpkg, bootstrap and acquire the necessary packages. This will take some time because `qtdeclarative` will be downloaded and built from source on your machine. However, this is necessary only once after cloning.  
