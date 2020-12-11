import matplotlib
import os
import random
import subprocess

def generateData(filePath,fileName):
   file = str(filePath + '/' +fileName)
   with open(file ,'w+') as f:
        for i in range(10,20):
            flag = []
            up = random.randint(100,200)
            f.write(str(i)+'\n')
            f.write(str(up)+'\n')
            for j in range(i):
                element = random.randint(0,up)
                while element in flag:
                    element = random.randint(i,up)

                flag.append(element)
                f.write(str(element)+' ')    
            f.write('\n')    

def execAlgorithm(exePath):
    if os.path.exists(exePath):
        # rc,out = subprocess.getstatusoutput(exePath)
        print(subprocess.getstatusoutput(exePath))


def main():
    filePath = 'testcases'
    fileName = 'example.txt'
    generateData(filePath,fileName)
    # exePath = '.\src\\main.exe'
    # execAlgorithm(exePath)
    # os.system(exePath)

if __name__ == '__main__':
    main()