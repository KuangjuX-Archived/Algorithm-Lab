import matplotlib.pyplot as plt
import os
import random
import numpy as np

def generateData(filePath,fileName):
   file = str(filePath + '/' +fileName)
   with open(file ,'w+') as f:
        for i in range(10,100):
            flag = []
            up = random.randint(10,10000)
            f.write(str(i)+'\n')
            f.write(str(up)+'\n')
            for j in range(i):
                element = random.randint(0,up)
                # element = (int)(random.random()*up)
                while element in flag:
                    element = random.randint(0,up)
                    # element = (int)(random.random()*up)

                flag.append(element)
                f.write(str(element)+' ')
            f.write('\n')    

# def execAlgorithm(exePath):
#     if os.path.exists(exePath):

def dataVisual(path):
    data = np.loadtxt(path)
    x, _ = data.shape
    plt.plot([data[i][0] for i in range(x)], [data[i][1] for i in range(x)])
    plt.show()
   


def main():
    # filePath = 'testcases'
    # fileName = 'example.txt'
    # generateData(filePath,fileName)
    # exePath = '.\src\\main.exe'
    # execAlgorithm(exePath)
    # os.system(exePath)
    path = 'testcases/time.txt'
    dataVisual(path)

if __name__ == '__main__':
    main()