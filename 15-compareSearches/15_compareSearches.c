#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;  // �� Ƚ��


//���� �迭 ����
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;  // 0~999 ������ ����
	}
}

//����Ž��
int seq_search(int key, int low, int high, int list[]) {
	int i;
	for (i = low; i <= high; i++) {
		compareCount++; // �� Ƚ�� ����
		if (list[i] == key) {
			return i; // Ž�� ����
		}
	}
	return -1; // Ž�� ����
}

// ��� �� Ƚ�� ���
double getAverageLinearSearchCompareCount(int array[]) {
	compareCount = 0; // �� Ƚ�� �ʱ�ȭ
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE]; // �׻� �����ϴ� �����Ϳ� ���� Ž���ϱ� ����
		seq_search(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 100.0; // ��� �� Ƚ�� ��ȯ
}

// �� ���� ����
int partition(int array[], int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	int temp;

	for (int j = low; j < high; j++) {
		compareCount++; // �� Ƚ�� ����
		if (array[j] <= pivot) {
			i++;
			SWAP(array[i], array[j], temp);
		}
	}
	SWAP(array[i + 1], array[high], temp);
	return i + 1;
}

// �� ����
void quickSort(int array[], int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

// �� ���� �� Ƚ�� ���
void getQuickSortCompareCount(int array[]) {
	compareCount = 0; // �� Ƚ�� �ʱ�ȭ
	quickSort(array, 0, SIZE - 1);
}


//����Ž��
int search_binary2(int key, int low, int high, int list[])
{
	int middle;

	while (low <= high) { 				// ���� ���ڵ��� ���� ������

		compareCount++; //��Ƚ�� ����

		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// Ž�� ����
		else if (key > list[middle]) low = middle + 1; 	// ���� �κи���Ʈ Ž��
		else high = middle - 1; 			// ������ �κи���Ʈ Ž��
	}
	return -1; 					// Ž�� ����
}


// ��� �� Ƚ�� ��� �Լ� (����Ž��)
double getAverageBinarySearchCompareCount(int array[]) {
	compareCount = 0; // �� Ƚ�� �ʱ�ȭ
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE]; // �׻� �����ϴ� �����Ϳ� ���� Ž���ϱ� ����
		search_binary2(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 100.0; // ��� �� Ƚ�� ��ȯ
}


//����Լ�
void printArray(int* array) {
	printf("Array Sorting Result:\n");

	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

int main() {
	srand(time(NULL));
	int array[SIZE];

	for (int i = 1; i <= 3; i++) { // 3���� ���ӵ� ��°���� �����ֱ� ���� �ݺ������� ����
		printf("\n\n");

		generateRandomArray(array);

		//��հ��� ��ȯ�ڱ� ���� ��ġ
		printf("Average Linear Search Compare Count: %2f\n", getAverageLinearSearchCompareCount(array));

		//compareCount�� global variable�̹Ƿ�, ������ ���� ����
		//array�� ���ؼ� ���� �����ϸ� �ȴ�
		getQuickSortCompareCount(array);
		printf("Quick Sort Compare Count: %d\n", compareCount);

		//���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���
		printf("Average Binary Search Compare Count: %.2f\n\n",
			getAverageBinarySearchCompareCount(array));

		printArray(array);

	}

	return 0;
}