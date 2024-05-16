#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>
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
    for (int j = 0; j < 1000000; j++)
    {
        at++;
    }

}
int main()
{
    vector <thread> ths;
    clock_t start_time = clock();
    for (int j = 0; j < 5; j++)
    {
        ths.push_back(thread(visit));
    }
    for (auto& th : ths)
    {
        th.join();
    }
    cout << i << endl;
    clock_t end_time = clock();
    double search_time1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    cout << search_time1 << endl;
    ths.clear();
    start_time = clock();
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
    end_time = clock();
    search_time1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    cout << search_time1 << endl;
    start_time = clock();
    for (int j = 0; j < 5; j++)
    {
        ths.push_back(thread(visitAtom));
    }
    for (auto& th : ths)
    {
        th.join();
    }
    ths.clear();
    cout << at << endl;
    end_time = clock();
    search_time1 = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    cout << search_time1 << endl;
}
