import matplotlib
import os
import random
import subprocess

def generateData(filePath,fileName):
   file = str(filePath + '/' +fileName)
   with open(file ,'w+') as f:
        for i in range(1,100):
            flag = []
            up = random.randint(1,10000)
            f.write(str(up))
            f.write(' ')
            for j in range(i):
                print(up)
                element = random.randint(0,up)
                print(flag)
                while element in flag:
                    element = random.randint(i,up)

                flag.append(element)
                f.write(str(element))
                f.write(' ')    
            f.write('\n')    

def execAlgorithm(exePath):
    if os.path.exists(exePath):
        # rc,out = subprocess.getstatusoutput(exePath)
        print(subprocess.getstatusoutput(exePath))


def main():
    # filePath = 'testcases'
    # fileName = 'example.txt'
    # generateData(filePath,fileName)
    exePath = '.\src\\main.exe'
    # execAlgorithm(exePath)
    os.system(exePath)
    exit()

if __name__ == '__main__':
    main()