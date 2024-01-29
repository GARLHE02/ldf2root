# ldf2root
A simple script that takes the binary .ldf file and puts it into a ROOT tree. I have included the Lemor documentation for an .ldf file for convenience. 

To run: 
  1. Open ROOT
  2. [0] .L /path/to/ldf_binary_to_root_HG.cxx
  3. [1] ReadAnalogData("/path/to/file_to_read.ldf","newfilename.root")

Notes: 
  1. If you name the new file the same as an old one, it will overwrite it. 
  2. If you use this repository in your research, please cite as: 
    H. I. Garland, ldf2root, GitHub, https://github.com/GARLHE02/ldf2root.git (2024)
