#include "../dsa/SortAlgorithms.h"
#include "../dsa/dsaUtils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// ¸´ÖÆÊı×é£¨±ÜÃâÅÅĞòºó¸²¸ÇÔ­Êı×é£©
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}
int main() {
    srand(time(0));
    const int N = 8;
    int arr[N];
    dsaUtils::RandomData(arr, N, rand());
    dsaUtils::Show(arr, N);
    int temp[N]; 
    // ²âÊÔ²åÈëÅÅĞò
    copyArray(arr, temp, N);
    sort::insertSort(temp, N);
    cout << "-------------------------" << endl;

    // ²âÊÔÃ°ÅİÅÅĞò
    copyArray(arr, temp, N);
    sort::bubbleSort(temp, N);
    cout << "-------------------------" << endl;

    // ²âÊÔÑ¡ÔñÅÅĞò
    copyArray(arr, temp, N);
    sort::selectSort(temp, N);
    cout << "-------------------------" << endl;

    // ²âÊÔ¿ìËÙÅÅĞò
    copyArray(arr, temp, N);
    sort::quickSort(temp, N);
    cout << "-------------------------" << endl;

    return 0;
}