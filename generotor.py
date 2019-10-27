import random

# instanceSizes=range(50,501,50)
instanceSizes = [50]

density = 5 
# how many tasks at average start at the same quant of time

readyToProcessingRatio = 2
# how many times larger is the range of ready times to the average time of processing 

readyToDeadlineAdditiveRatio = 4
# how many times larger is the range of ready times to the maximal deadline additive 


def generateInstance(n):
    tasks=[]
    for i in range(n):
        p = 1 + random.randrange(int(n/density/readyToProcessingRatio) - 1)
        r = random.randrange(int(n/density))
        d = p + r + random.randrange(int(n/density/readyToDeadlineAdditiveRatio))
        tasks.append("{} {} {}".format(p,r,d))
    return tasks

def save(n,instance):
    f=open(str(n)+'.txt','w+')
    f.write(str(n)+'\n')
    for i in instance:
        f.write(i+'\n')
    f.close()


def main():
  for i in instanceSizes:
        instance = generateInstance(i)
        save(i,instance)
        print(instance)

if __name__== "__main__":
  main()