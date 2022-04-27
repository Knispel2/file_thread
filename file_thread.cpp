#include <iostream>
#include <thread>

using namespace std;

void f_create(FILE* f, int begin, int* x)
{
    FILE* f_buf;
    f_buf = fopen(string("test" +string(int(begin / 10))+ ".bin"), "ab");
    fseek(f, begin, SEEK_SET);
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
    fseek(f, 0, SEEK_SET);
    fread(x, sizeof(int), 1, f);
    for (int i = 0; i < 1; i++)
        cout << x[i] << " ";
    fclose(f);
}

