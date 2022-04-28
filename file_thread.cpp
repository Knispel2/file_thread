#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <string>
#include <mutex>


using namespace std;

void f_create(FILE* f, int begin, mutex & test_mutex)
{
    FILE* f_buf;
    f_buf = fopen(string("test" + to_string(begin) + ".bin").c_str(), "ab");
    int* buf = new int;
    fseek(f, begin, SEEK_SET);
    test_mutex.lock();
    for (int i = 0; i < 10; i++)
    {
        fread(buf, sizeof(int), 1, f);
        fwrite(buf, sizeof(int), 1, f_buf);
    }  
    test_mutex.unlock();
    fclose(f_buf);
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
        thread task( f_create, f, i, ref(test_mutex) );
        task.join();
    }    
    fclose(f);
}

