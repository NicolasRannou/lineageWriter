cmake_minimum_required(VERSION 2.6)
 
PROJECT(lineageTreeWriter)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
 
ADD_EXECUTABLE(lineageTreeWriter lineageTreeWriter.cxx)
TARGET_LINK_LIBRARIES(lineageTreeWriter vtkHybrid vtkInfovis vtkViews)
