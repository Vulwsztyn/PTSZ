#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;
ifstream instanceFile;
ifstream mySolutionFile;
ofstream solutionFile;
void print1dVector(vector<int> vec)
{
    for (auto const &v : vec)
    {
        cout << v << " ";
        cout << endl;
    }
}
void print2dVector(vector<vector<int>> vec)
{
    for (auto const &v : vec)
    {
        for (auto const &a : v)
        {
            cout << a << " ";
        }
        cout << endl;
    }
}

bool checkSolution(int size, vector<vector<int>> solution)
{
    int zadanieJest[size + 1];
    for (int i = 0; i < size + 1; i++)
    {
        zadanieJest[i] = 0;
    }
    for (auto const &v : solution)
    {
        for (auto const &a : v)
        {
            if (a < 1)
            {
                cout << "Nr zadania (" << a << ") w rozwiazaniu mniejszy od 1" << endl;
                return false;
            }
            else if (a > size)
            {
                cout << "Nr zadania (" << a << ") w rozwiazaniu większy od rozmiaru instancji" << endl;
                return false;
            }
            zadanieJest[a]++;
            if (zadanieJest[a] > 1)
            {
                cout << "Nr zadania (" << a << ") w rozwiazaniu się powtarza" << endl;
                return false;
            }
        }
    }
    // for (int i =1;i<size+1;i++){
    //     cout<<i<<" "<<zadanieJest[i]<<endl;
    // }
    for (int i = 1; i < size + 1; i++)
    {
        if (zadanieJest[i] < 1)
        {
            cout << "Nr zadania (" << i << ") w rozwiazaniu nie występuje" << endl;
            return false;
        }
    }
    return true;
}

vector<vector<int>> naiwny(int size)
{
    vector<vector<int>> solution;
    int g = ceil(size / 4.0);
    for (int i = 0; i < 4; i++)
    {
        vector<int> a;
        for (int j = 1; j <= g; j++)
        {
            int c = j + i * g;
            if (c > size)
                break;
            a.push_back(c);
        }
        solution.push_back(a);
    }
    return solution;
}

int caclSD(int size, vector<vector<int>> instance, vector<vector<int>> solution)
{
    int result = 0;
    for (auto const &m : solution)
    {
        int lastEnded = 0;
        for (auto const &t : m)
        {
            int timeStarted = lastEnded > instance[t][1] ? lastEnded : instance[t][1];
            lastEnded = timeStarted + instance[t][0];
            int delay = lastEnded - instance[t][2];
            result += delay > 0 ? delay : 0;
            // cout << t << " " << result << endl;
        }
    }
    return result;
}

bool checkInstance(int size, vector<vector<int>> instance)
{
    if (size + 1 != instance.size())
    {
        cout << "Niepoprawna liczba zadań" << endl;
        return false;
    }
    for (int i = 1; i < size + 1; i++)
    {
        if (instance[i][0] < 0 || instance[i][1] < 0 || instance[i][2] < 0)
        {
            cout << "Zadanie " << i << " ma czas trwania mniejszy od 0, możlwie, że plik nie zawiera wszystkich zadan" << endl;
            return false;
        }
        if (instance[i][2] < instance[i][0] + instance[i][1])
        {
            cout << "Zadanie " << i << " ma deadline przed sumą p i r" << endl;
            return false;
        }
        if (instance[i][0] < 1)
        {
            cout << "Zadanie " << i << " ma czas trwania 0" << endl;
            return false;
        }
    }
    return true;
}

vector<int> split(string a){
 vector<int> res;
 string tmp="";
 for (int i =0 ;i< a.length();i++){
  if (a[i]==' ' || a[i] == '\n'){
   if(tmp.length()>0){
    res.push_back(stoi(tmp));
    tmp="";
   }
  } else {
      if(isdigit(a[i])) tmp+=a[i];   
  }
 }
 if(tmp.length()>0){
    res.push_back(stoi(tmp));
   }
 return res;
}

int main()
{
    string indexNumbers[] = {
        "132290",
    //  "132324",
    //  "132289",
    //  "132234",
    //  "132311",
    //  "132235",
    //  "132275",
    //  "132332",
    //  "132202",
    //  "132205",
    //  "132217",
    //  "132250",
    //  "132322",
    //  "132212",
    //  "",
    //  "132264",
    //  "132078"
    };
    string instanceSizes[] = {
        // "50",
     "100",
    //  "150",
    //  "200",
    //  "250",
    //  "300",
    //  "350",
    //  "400",
    //  "450",
    //  "500"
     };
    bool isVerificationRun=true;
    for (auto const &ind : indexNumbers)
    {
        for (auto const &num : instanceSizes)
        {
            instanceFile.open("./Instancje/in" + ind + "_" + num + ".txt");
            int size = 0, p, r, d;
            vector<vector<int>> instance;
            instance.push_back(vector<int>()); //coby sie zaczynalo od 1
            instanceFile >> size;
            for (int i = 0; i < size; i++)
            {
                if (instanceFile.eof())
                {
                    p = -1;
                }
                else
                {
                    instanceFile >> p;
                }
                if (instanceFile.eof())
                {
                    r = -1;
                }
                else
                {
                    instanceFile >> r;
                }

                if (instanceFile.eof())
                {
                    d = -1;
                }
                else
                {
                    instanceFile >> d;
                }

                instance.push_back(vector<int>{p, r, d});
            }
            instanceFile.close();
            // cout << ind << "_" << num << endl;

            if (!checkInstance(size, instance))
                continue;
            // print2dVector(naiwny(size));

            vector<vector<int>> solution;
            int potencjalneSD;
            if (isVerificationRun){
                mySolutionFile.open("./Solucje/out" + ind + "_" + num + ".txt");
                mySolutionFile >> potencjalneSD;
                string line;
                getline(mySolutionFile,line);
                while (getline(mySolutionFile, line))
                {
                    solution.push_back(split(line));
                }
                mySolutionFile.close();
                // print2dVector(solution);
            } else {
                solution = naiwny(size);
            }
            if (!checkSolution(size, solution))
            {
                continue;
            };
            print2dVector(instance);
            print2dVector(solution);
            int prawdziweSD = caclSD(size, instance, solution);
            if (isVerificationRun && prawdziweSD != potencjalneSD){
            cout << "Złe sd " <<prawdziweSD<<endl;
            }
            if (!isVerificationRun){
                cout << caclSD(size, instance, solution) << endl;
            } else {
                cout<<size<<" ok"<<endl;
            }
            
        }
    }
    return 0;
}