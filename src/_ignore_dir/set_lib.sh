#!/bin/bash

for f in */*cbp; do
  echo "File -> $f"

  sed -i "s|<Add library=\"../lib/libfreeglut32.a\" />|<Add option=\"-lGL\" />|" $f

  sed -i "s|<Add library=\"../lib/libopengl32.a\" />|<Add option=\"-lGLU\" />|" $f

  sed -i "s|<Add library=\"../lib/libglu32.a\" />|<Add option=\"-lglut\" />|" $f

  sed -i	"s|<Add library=\"../lib/libglfw3dll.a\" />|<Add option=\"-lglfw3\" />|" $f 
  sed -i	"s|<Add library=\"../lib/libglfw3.a\" />|\n|" $f 

done

