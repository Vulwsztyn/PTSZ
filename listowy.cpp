#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <chrono>
#include <algorithm>

using namespace std;
ifstream instanceFile;
ofstream solutionFile;

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

vector<vector<int>> listowy(int size, vector<vector<int>> instance)
{
    vector<vector<int>> solution;
    solution.resize(4);
    // for (int i=0;i<4;i++)solution[i].resize(size);
    // cout<<instance.size()<<endl;
    std::sort(instance.begin()+1, instance.end(), 
     [](vector<int> &a, vector<int> &b) {
        return a[2] < b[2]; 
    });
    // cout<<instance.size()<<endl;
    vector<int> machines{ 0,0,0,0 };

    for (int i=1; i<=size;i++){
        // cout<<i<<endl;
        int minMachine = 0;
        int minTime = machines[0];
        for (int j =1; j<4;j++){
            if (machines[j]<minTime){
                minTime = machines[j];
                minMachine = j;
            }
        }
        solution[minMachine].push_back(instance[i][3]);
        machines[minMachine] = max(machines[minMachine],instance[i][1]) + instance[i][0];
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

int main()
{
    vector<long long> times;
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
    //  "116753",
    //  "132264",
    //  "132078"
     };
    // string indexNumbers[] = {"", "", "132289", "132234", "132311", "132235", "132275", "132332", "132202", "132205", "132217", "132250", "132322", "132212", "", "132264", "132078"};
    
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

                instance.push_back(vector<int>{p, r, d, i + 1});
            }
            instanceFile.close();
            // cout << ind << "_" << num << endl;

            if (!checkInstance(size, instance))
                continue;
            
            auto start = std::chrono::high_resolution_clock::now();
            // print2dVector(instance);
            //TODO zglobalizuj wszystko jak młot
            vector<vector<int>> solution = listowy(size, instance);
            // print2dVector(solution);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            times.push_back(microseconds);
            if (!checkSolution(size, solution))
            {
                continue;
            };
            // print2dVector(instance);
            int sd = caclSD(size, instance, solution);
            print2dVector(solution);
            cout << sd << endl;
            solutionFile.open("./Instancje/out" + ind + "_" + num + ".txt");
            solutionFile <<sd << endl;
            for (auto const &v : solution)
            {
                for (auto const &a : v)
                {
                    solutionFile << a << " ";
                }
                solutionFile << endl;
            }
            solutionFile.close();
            // if (num == "50") break;
        }
        // break;
        // if (ind == "132290") break;
    }
    return 0;
}