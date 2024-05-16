

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
int i = 0;
int k = 0;
void visit()
{ 
    for (int j = 0; j < 1000000; j++)
    {
        i++;
    }
}
mutex mt;
void visitSafe()
{
    for (int j = 0; j < 1000000; j++)
    {
        mt.lock();

        k++;

        mt.unlock();
    }
}

atomic <int> at;

void visitAtom()
{
    at++;
}
int main()
{
    vector <thread> ths;
    for (int j = 0; j < 5; j++)
    {
        ths.push_back(thread(visit));
    }
    for (auto &th:ths)
    {
        th.join();
    }
    cout << i << endl;

    for (int j = 0; j < 5; j++)
    {
        ths.push_back(thread(visitSafe));
    }
    for (auto& th : ths)
    {
        th.join();
    }
    ths.clear();
    cout << k << endl;
}
