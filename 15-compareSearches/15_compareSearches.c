#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;  // 비교 횟수


//난수 배열 생성
void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 1000;  // 0~999 사이의 난수
	}
}

//순차탐색
int seq_search(int key, int low, int high, int list[]) {
	int i;
	for (i = low; i <= high; i++) {
		compareCount++; // 비교 횟수 증가
		if (list[i] == key) {
			return i; // 탐색 성공
		}
	}
	return -1; // 탐색 실패
}

// 평균 비교 횟수 계산
double getAverageLinearSearchCompareCount(int array[]) {
	compareCount = 0; // 비교 횟수 초기화
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE]; // 항상 존재하는 데이터에 대해 탐색하기 위함
		seq_search(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 100.0; // 평균 비교 횟수 반환
}

// 퀵 정렬 분할
int partition(int array[], int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	int temp;

	for (int j = low; j < high; j++) {
		compareCount++; // 비교 횟수 증가
		if (array[j] <= pivot) {
			i++;
			SWAP(array[i], array[j], temp);
		}
	}
	SWAP(array[i + 1], array[high], temp);
	return i + 1;
}

// 퀵 정렬
void quickSort(int array[], int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

// 퀵 정렬 비교 횟수 계산
void getQuickSortCompareCount(int array[]) {
	compareCount = 0; // 비교 횟수 초기화
	quickSort(array, 0, SIZE - 1);
}


//이진탐색
int search_binary2(int key, int low, int high, int list[])
{
	int middle;

	while (low <= high) { 				// 아직 숫자들이 남아 있으면

		compareCount++; //비교횟수 증가

		middle = (low + high) / 2;
		if (key == list[middle]) return middle; 	// 탐색 성공
		else if (key > list[middle]) low = middle + 1; 	// 왼쪽 부분리스트 탐색
		else high = middle - 1; 			// 오른쪽 부분리스트 탐색
	}
	return -1; 					// 탐색 실패
}


// 평균 비교 횟수 계산 함수 (이진탐색)
double getAverageBinarySearchCompareCount(int array[]) {
	compareCount = 0; // 비교 횟수 초기화
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE]; // 항상 존재하는 데이터에 대해 탐색하기 위함
		search_binary2(target, 0, SIZE - 1, array);
	}
	return (double)compareCount / 100.0; // 평균 비교 횟수 반환
}


//출력함수
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

	for (int i = 1; i <= 3; i++) { // 3번의 연속된 출력결과를 보여주기 위해 반복문으로 돌림
		printf("\n\n");

		generateRandomArray(array);

		//평균값을 반환박기 위한 조치
		printf("Average Linear Search Compare Count: %2f\n", getAverageLinearSearchCompareCount(array));

		//compareCount가 global variable이므로, 다음과 같이 구현
		//array에 대해서 직접 정렬하면 된다
		getQuickSortCompareCount(array);
		printf("Quick Sort Compare Count: %d\n", compareCount);

		//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
		printf("Average Binary Search Compare Count: %.2f\n\n",
			getAverageBinarySearchCompareCount(array));

		printArray(array);

	}

	return 0;
}