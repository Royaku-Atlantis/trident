print("Updating Makefile ...")
import os
# get list of all src files

#get all .cpp files
listof_cpp = os.listdir("src/definitions")

#deduct all .o files
def cpp_to_o(filestr):
        return "bin\\" + filestr.replace(".cpp",".o")
listof_o = [cpp_to_o(filestr) for filestr in listof_cpp]

#add the src\definition to the cpp file path
def cpp_addfullpath(filestr):
        return "src\\definitions\\" + filestr
listof_cpp = [cpp_addfullpath(filestr) for filestr in listof_cpp]

#manually add main.cpp and main.o
listof_cpp.append("src\\main.cpp")
listof_o.append("bin\\main.o")

#open makefile as write
makefile = open("makefile", "w")

#makefile "all"
makefile.write("all:")
for file_o in listof_o:
        makefile.write(" "+file_o)

makefile.write("\n\tg++")
for file_o in listof_o:
        makefile.write(" "+file_o)

makefile.write(" -g -o bin\\main.exe -std=c++20\n")
print("- wrote 'all' clause")

#makefile each src
for file_o, file_cpp in zip(listof_o, listof_cpp):
        makefile.write("\n"+file_o+": "+file_cpp)
        makefile.write("\n\tg++ -c "+file_cpp+" -g -o "+file_o)
        print("- wrote :", file_o)

#ending
makefile.write("\n\nclean:\n\tdel bin\\*.o\nveryclean:\n\tdel bin\\*.o\n\tdel bin\\*.exe")
print("- wrote 'clean' and 'veryclean' clause")
makefile.close()

print("Updated Makefile : Done")