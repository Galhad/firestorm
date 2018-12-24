# firestorm

## About
Firestorm is a 2D game engine that aims to be easy to use, cross platform
and efficient.

Features:
* Cross-platform:
  * Windows
  * Linux
  * Android
* Vulkan support

## Release notes

## Building
CMake is used as a building system.

### Cloning
External dependencies are stored as git submodules, so when doing a fresh clone you need to initialize submodules:

```
git clone --recursive https://gitlab.com/galhad/firestorm.git
```

Existing repositories can be updated manually:

```
git submodule init
git submodule update
```

### Dependencies
* Vulkan SDK
* External libraries dependencies

Install dependencies:

* Fedora:
```
sudo dnf install libXcursor-devel libXinerama-devel libXrandr-devel xorg-x11-server-devel
```

* Ubuntu
```
sudo apt update
sudo apt install build-essential xorg-dev
wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.1.92-bionic.list http://packages.lunarg.com/vulkan/1.1.92/lunarg-vulkan-1.1.92-bionic.list
sudo apt update
sudo apt install lunarg-vulkan-sdk
```

* Windows \
Install VulaknSDK from https://vulkan.lunarg.com/sdk/home#windows