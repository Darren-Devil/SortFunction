#include "SortFunction.h"

int main() {
	printf("≈≈–Ú«∞£∫\n");
	int arr[30] = { 0 };
	for (int i = 0; i < 30; i++) {
		arr[i] = rand();
		printf("%d ", arr[i]);
	}
	printf("\n");

	QuickSort(arr, 30);
	printf("≈≈–Ú∫Û£∫\n");
	for (int i = 0; i < 30; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	system("PAUSE");
}