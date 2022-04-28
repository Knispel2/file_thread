#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <string>
#include <mutex>


using namespace std;

void f_create(int begin, mutex& test_mutex)
{
    FILE* f_buf, * f;
    lock_guard <mutex> test(test_mutex);
    f = fopen("test.bin", "rb");
    f_buf = fopen(string("test" + to_string(begin) + ".bin").c_str(), "wb");
    int* buf = new int;
    fseek(f, begin*sizeof(int)*10, SEEK_SET);
    fseek(f_buf, 0, SEEK_SET);
    for (int i = 0; i < 10; i++)
    {
        fread(buf, sizeof(int), 1, f);
        fwrite(buf, sizeof(int), 1, f_buf);
    }
    fclose(f_buf);
    fclose(f);
    delete buf;
}


int main()
{
    FILE* f;
    f = fopen("test.bin", "wb");
    int* x = new int[100];
    for (int i = 0; i < 100; i++)
        x[i] = i;
    fwrite(x, sizeof(int), 100, f);
    mutex test_mutex;
    fclose(f);
    for (int i = 0; i < 10; i++)
    {
        //f_create(i, test_mutex);
        thread task(f_create, i, ref(test_mutex));
        if (i == 9) task.join();
        else task.detach();
    }

}