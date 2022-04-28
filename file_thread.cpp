#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

void f_create(FILE* f, int begin, int* x, mutex test_mutex)
{
    FILE* f_buf;
    f_buf = fopen(string("test" + to_string(int(begin / 10)) + ".bin").c_str(), "ab");
    fseek(f, begin, SEEK_SET);
    lock_guard<mutex> guard(test_mutex);
    for (int i = 0; i < 10; i++)
        fwrite(&x[begin + i], sizeof(int), 1, f_buf);

}


int main()
{
    FILE* f;
    f = fopen("test.bin", "ab");
    int* x = new int[100];
    for (int i = 0; i < 100; i++)
        x[i] = i;
    fwrite(x, sizeof(int), 100, f);
    mutex test_mutex;
    for (int i = 0; i < 10; i++)
    {
        thread task(f_create, f, i, x, test_mutex);
        task.detach();
    }        
    fclose(f);
}

