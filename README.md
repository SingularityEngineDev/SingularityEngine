# Singularity Engine

> [!IMPORTANT]
> This is WIP project I develop in my free time for mainly learning purposes, readme is also in progress

## Currently working on: Virutal filesystem and custom archive format with O(1) lookup complexity

## Backends I plan to implement ordered by priority
1. Direct3D 11 (in progress)
2. Direct3D 12
3. Vulkan

## Open-Source projects used
- SDL [project](https://github.com/libsdl-org/SDL) [license](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt)
- argparse [project](https://github.com/p-ranav/argparse) [license](https://github.com/p-ranav/argparse/blob/master/LICENSE)
- lz4 [project](https://github.com/lz4/lz4) [license](https://github.com/lz4/lz4/blob/release/LICENSE)
- spdlog [project](https://github.com/gabime/spdlog) [license](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)
- xxHash [project](https://github.com/Cyan4973/xxHash) [license](https://github.com/Cyan4973/xxHash/blob/dev/LICENSE)

## Note about contributions
Please consider using LLVM toolset for development, due to the stricter rules. That way we can reduce bugs and warnings in the code in less strict environments.
If you're running Windows with Visual Studio, add ClangCL support to your IDE.