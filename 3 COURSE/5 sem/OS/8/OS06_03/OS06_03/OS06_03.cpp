#include <iostream>
#include <Windows.h>

using namespace std;

#define PAGE_SIZE (4096)
int numPages = 256;

int main() {

    int* arr = (int*)VirtualAlloc(NULL, numPages * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < numPages * PAGE_SIZE / sizeof(int); i++) {
        arr[i] = i;
    }

    /*
        Х=F5=245
        а=E0=224
        л=EB=235
        Страница C1 = 245, смещение E0E=3598
        адрес страницы 4096 * 245 = 1003520(10) = 0x000F5000
        смещение 0x000F5000 => 3598 (3596)
        адрес смещения = 1003520 + 3596 = 1007116, 0xF5E0C
        (1007116)/4 (sizeof(int) = 4) = 251779
    */

    const int targetPage = 245;
    const int offset = 3598;

    int* value = arr + (targetPage * PAGE_SIZE + offset) / sizeof(int);

    cout << "Value: " << *value << endl;
    cout << "Address: " << hex << value << endl;

    system("pause");

    return 0;
}