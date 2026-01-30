Set up for CLion

## 1. Clone the repository (including submodules)

```powershell
git clone --recurse-submodules https://github.com/adamdeere/MooseEngine.git
cd MooseEngine

git submodule update --init --recursive

cd external/vcpkg
.\bootstrap-vcpkg.bat

vcpkg.exe install

vcpkg will automatically download and build:

GLFW3 (window/input library)

GLAD (OpenGL loader)

Any required build tools (CMake, 7zip, PowerShell core, etc.)

Set toolchain

-DCMAKE_TOOLCHAIN_FILE=external/vcpkg/scripts/buildsystems/vcpkg.cmake
