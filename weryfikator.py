import math
import os
machineCount = 4

def checkInstance(size,instance):
  pass


def checkSolution(size,instance,sumD,solution,checkSumOfDelays):
  assignedTasks=[0]*(size+1)  
  flatSolution = sum(solution,[])
  for i in flatSolution:
    if i<1 or i>size:
      print("niepoprawny nr zadania {}".format(str(i)))
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
          print (taskI)
          timeStarted = max(lastEnded,instance[taskI][1])
          lastEnded = timeStarted + instance[taskI][0]
          delay = lastEnded - instance[taskI][2]
          sD += delay if delay>0 else 0
        #   print(sD, instance[taskI])
  if checkSumOfDelays and sD != sumD:
      print("zle policzony czas, podany {}, wyliczony {}".format(str(sumD),str(sD)))
  print(sD)

def algorytm(size):
    list=[[],[],[],[]]
    g = math.ceil(size/machineCount)
    for m in range(4):
      for i in range(1,g+1):
          if(i+m*g>size):
            break
          list[m].append(i+m*g)
    # for i in list:
    #   print (i)
    return (0,list)

def main_stary(files):
  for file in files: 
    instanceFile = open(file, "r") 
    # solutionFile = open("rozwiazanie.txt", "r")
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

def main(files):
  for student in ['132290','132234','132311',	'132235',	'132275',	'132332',		'132202',	'132217',	'132250',	'132322',	'132212', '132264', '132078']:
    for file in range(50,501,50): 
      instanceFile = open('Instancje/in'+student+'_'+str(file)+'.txt', "r") 
      # solutionFile = open("rozwiazanie.txt", "r")
      size = int(instanceFile.readline())
      taskList=[]
      for i in range(size):
          taskList.append([int(x) for x in instanceFile.readline().split()])
    #   print(taskList)
      checkInstance(size,taskList)
      # sD = int(solutionFile.readline())
      # machineList=[]
      # for i in range(machineCount):
      #     machineList.append([int(x) for x in solutionFile.readline().split()])
      (a,b) = algorytm(size)
      checkSolution(size,taskList,a,b,False)
      if file == 150:
        break
    break

if __name__== "__main__":
  main(os.listdir('Instancje'))