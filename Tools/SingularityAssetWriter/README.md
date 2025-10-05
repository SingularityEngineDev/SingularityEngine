# Informations about virtual filesystem and format of archives
## Design
The virtual filesystem of Singularity Engine is designed to be fast and flexible. That means that the archives that the engine loads
contain metadata that can be loaded in 2 ways:
1. Using generated headers (currently being implemented)
2. Using TOC (Table Of Contents) placed at the end of archive

Thus modders can add easily new assets and use them, because virtual filesystem will still detect them (with slightly bigger lookup time than O(1) of course).
To get better compression ratio with LZ4 frame API which is used to compress archive data, files in the archive are grouped into blocks that have 
more than 128mb (files are being added to the block until it's more than 128mb).

## TOC
TOC contains metadata for each block. Metadata is structured using the following scheme:   
[Block offset]   
[Compressed size]   
[Uncompressed size]   
[Checksum (TODO: add more informations when algorithm is chosen)]   
[Number of files that it contains]   
[File Info]

## File Info
File info scheme:   
[File name length]   
[File size]   
[File name (variable length specified in first entry)]

## Archive layout
[Block 0]   
[Block 1]   
[Block 2]   
...   
[Block N]   
[TOC]   