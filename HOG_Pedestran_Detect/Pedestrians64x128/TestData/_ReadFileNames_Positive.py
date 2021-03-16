import os

dir_path = os.path.dirname(os.path.abspath(__file__))

if os.path.exists("FileNameList.txt"):
    os.remove("FileNameList.txt")

file_object = open("FileNameList.txt","w")

for root, dirs, files in os.walk("."):
    for file in files:
        if ".jpg" in file:
            file_object.write(dir_path+"\\"+file+"\n")
            
print("OK!")