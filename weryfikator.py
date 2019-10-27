import math
machineCount = 4

def checkInstance(size,instance):
  pass


def checkSolution(size,instance,sumD,solution):
  assignedTasks=[0]*(size+1)  
  flatSolution = sum(solution,[])
  for i in flatSolution:
    if i<1 or i>size:
      print("niepoprawny nr zadania")
    assignedTasks[i]+=1

  if(sum(assignedTasks)<size):
      print("nie wszystkie zadania")
  for i in range(1,size+1):
      if(assignedTasks[i]>1):
          print("zadanie {} zduplikowane".format(str(i)))
  sD=0
  for machine in solution:
      lastEnded=0
      for task in machine:
          taskI = task-1
          timeStarted = max(lastEnded,instance[taskI][1])
          lastEnded = timeStarted + instance[taskI][0]
          delay = lastEnded - instance[taskI][2]
          sD += delay if delay>0 else 0
        #   print(sD, instance[taskI])
  if sD != sumD:
      print("zle policzony czas, podany {}, wyliczony {}".format(str(sumD),str(sD)))
  print("jest ok")

def algorytm(size):
    list=[[],[],[],[]]
    for i in range(1,size+1):
        list[i%(math.ceil(size/machineCount))]=i
    return (0,list)

def main():
  instanceFile = open("instance.txt", "r") 
  solutionFile = open("rozwiazanie.txt", "r")
  size = int(instanceFile.readline())
  taskList=[]
  for i in range(size):
      taskList.append([int(x) for x in instanceFile.readline().split()])
#   print(taskList)
  checkInstance(size,taskList)
  sD = int(solutionFile.readline())
  machineList=[]
  for i in range(machineCount):
      machineList.append([int(x) for x in solutionFile.readline().split()])
  checkSolution(size,taskList,sD,machineList)

if __name__== "__main__":
  main()