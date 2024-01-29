# ldf2root
A simple script that takes the binary .ldf file and puts it into a ROOT tree. 

To run: 
  1. Open ROOT
  2. [0] .L /path/to/ldf_binary_to_root_HG.cxx
  3. [1] ReadAnalogData("/path/to/file_to_read.ldf","newfilename.root")

Notes: 
  a. If you name the new file the same as an old one, it will overwrite it. 
