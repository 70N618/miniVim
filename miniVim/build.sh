#!bin/bash
if [ ! -d $"build/Desktop-Debug" ];then
mkdir -p build/Desktop-Debug
cd build/Desktop-Debug/
cmake ../..
compiledb make
else
  echo "Folder build/Desktop-Debug already exists";
fi
