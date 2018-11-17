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
