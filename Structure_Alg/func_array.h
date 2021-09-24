#include <cassert>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// UTILITY

#define ARRAY_SIZE(ARRAY) sizeof(ARRAY) / sizeof(ARRAY[0])

void rand_init(void) { srand(time(NULL)); }

int rand_range(int bottom, int top) {
    return bottom + rand() % (top - bottom + 1);
}

double rand_range(int bottom, int top, int digits) {
    return (bottom + rand() % (top - bottom + 1)) / (double)digits;
}

// INITIALIZATION

void initialize_with_random_value(int* array, size_t size) {
    rand_init();
    for (size_t i = 0; i < size; ++i)
        array[i] = rand_range(-100, 200);
}

void initialize_with_random_value(double* array, size_t size) {
    rand_init();
    for (size_t i = 0; i < size; ++i)
        array[i] = rand_range(-100, 100, 10);
}

// SUM & MULTIPLY

int sum(int* array, size_t size, size_t from, size_t to,
    bool (*predicate)(int value)) {
    assert(from < to);

    int sum = 0;
    for (size_t i = from; i <= to; ++i)
        if (predicate(array[i]))
            sum += array[i];

    return sum;
}

double sum(double* array, size_t size, size_t from, size_t to,
    bool (*predicate)(double value)) {
    assert(from < to);

    double sum = 0;
    for (size_t i = from; i <= to; ++i)
        if (predicate(array[i]))
            sum += array[i];

    return sum;
}

int multiply(int* array, size_t size, size_t from, size_t to,
    bool (*predicate)(int value)) {
    int res = 1;
    for (size_t i = from; i < to; ++i)
        if (predicate(array[i]))
            res *= array[i];

    return res;
}

double multiply(double* array, size_t size, size_t from, size_t to,
    bool (*predicate)(double value)) {
    double res = 1;
    for (size_t i = from; i < to; ++i)
        if (predicate(array[i]))
            res *= array[i];

    return res;
}

// INSERT / ERASE ELEMENT & SHIFT

void right_shift(int* array, size_t size, size_t startIndex) {
    for (size_t i = size - 1; i > startIndex; --i) {
        array[i] = array[i - 1];
    }
}

void right_shift(double* array, size_t size, size_t startIndex) {
    for (size_t i = size - 1; i > startIndex; --i) {
        array[i] = array[i - 1];
    }
}

void right_shift_cyclic(int* array, size_t size, size_t startIndex) {
    int temp = array[size - 1];
    for (size_t i = size - 1; i > startIndex; --i) {
        array[i] = array[i - 1];
    }
    array[0] = temp;
}

void right_shift_cyclic(double* array, size_t size, size_t startIndex) {
    double temp = array[size - 1];
    for (size_t i = size - 1; i > startIndex; --i) {
        array[i] = array[i - 1];
    }
    array[0] = temp;
}

void left_shift(int* array, size_t size, size_t startIndex) {
    for (size_t i = startIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
}

void left_shift(double* array, size_t size, size_t startIndex) {
    for (size_t i = startIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
}

void left_shift_cyclic(int* array, size_t size, size_t startIndex) {
    int temp = array[0];
    for (size_t i = startIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    array[size - 1] = temp;
}

void left_shift_cyclic(double* array, size_t size, size_t startIndex) {
    double temp = array[0];
    for (size_t i = startIndex; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    array[size - 1] = temp;
}

void insert(int* array, size_t size, size_t index, int value,
    int** out_array, size_t* out_size) {
    int* array_temp = new int[size + 1];

    for (size_t i = 0; i < size + 1; ++i)
        array_temp[i] = array[i];

    delete[] array;

    right_shift(array_temp, size + 1, index);

    array_temp[index] = value;

    *out_array = array_temp;
    *out_size = size + 1;
}

void insert(double* array, size_t size, size_t index, double value,
    double** out_array, size_t* out_size) {
    double* array_temp = new double[size + 1];

    for (size_t i = 0; i < size + 1; ++i)
        array_temp[i] = array[i];

    delete[] array;

    right_shift(array_temp, size + 1, index);

    array_temp[index] = value;

    *out_array = array_temp;
    *out_size = size + 1;
}

void erase(int* array, size_t size, size_t index, int** out_array,
    size_t* out_size) {
    int* array_temp = new int[size - 1];

    left_shift(array, size, index);

    for (size_t i = 0; i < size - 1; ++i)
        array_temp[i] = array[i];

    delete[] array;

    *out_array = array_temp;
    *out_size = size - 1;
}

void erase(double* array, size_t size, size_t index, double** out_array,
    size_t* out_size) {
    double* array_temp = new double[size - 1];

    left_shift(array, size, index);

    for (size_t i = 0; i < size - 1; ++i)
        array_temp[i] = array[i];

    delete[] array;

    *out_array = array_temp;
    *out_size = size - 1;
}

// SORTING

void bubble_sort(int* array, size_t size) {
    for (size_t j = 1; j < size; ++j)
        for (size_t i = 0; i < size - j; ++i) {
            if (array[i + 1] < array[i]) {
                int temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
            }
        }
}

void bubble_sort(double* array, size_t size) {
    for (size_t j = 1; j < size; ++j)
        for (size_t i = 0; i < size - j; ++i) {
            if (array[i + 1] < array[i]) {
                double temp = array[i + 1];
                array[i + 1] = array[i];
                array[i] = temp;
            }
        }
}

void selection_sort(int* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t min_index = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (array[j] < array[min_index])
                min_index = j;
        }

        if (min_index != i) {
            int temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
}

void selection_sort(double* array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t min_index = i;

        for (size_t j = i + 1; j < size; ++j) {
            if (array[j] < array[min_index])
                min_index = j;
        }

        if (min_index != i) {
            double temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
}

void shaker_sort(int* array, size_t size) {
    int control = size - 1;
    int left = 0;
    int right = size - 1;
    do {
        for (int i = left; i < right; i++) {
            if (array[i] > array[i + 1]) {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--) {
            if (array[i] < array[i - 1]) {
                int temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;
                control = i;
            }
        }
        left = control;
    } while (left < right);
}

void shaker_sort(double* array, size_t size) {
    int control = size - 1;
    int left = 0;
    int right = size - 1;
    do {
        for (int i = left; i < right; i++) {
            if (array[i] > array[i + 1]) {
                double temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--) {
            if (array[i] < array[i - 1]) {
                double temp = array[i];
                array[i] = array[i - 1];
                array[i - 1] = temp;
                control = i;
            }
        }
        left = control;
    } while (left < right);
}

// LINEAR-SEARCH

size_t find_max_value_index(int* array, size_t size) {
    size_t maxIndex = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > array[maxIndex])
            maxIndex = i;
    }

    return maxIndex;
}

size_t find_max_value_index(double* array, size_t size) {
    size_t maxIndex = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > array[maxIndex])
            maxIndex = i;
    }

    return maxIndex;
}

size_t find_min_value_index(int* array, size_t size) {
    size_t minIndex = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] < array[minIndex])
            minIndex = i;
    }

    return minIndex;
}

size_t find_min_value_index(double* array, size_t size) {
    size_t minIndex = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] < array[minIndex])
            minIndex = i;
    }

    return minIndex;
}

size_t find(int* array, size_t size, bool (*predicate)(int value)) {
    for (size_t i = 0; i < size; ++i)
        if (predicate(array[i]))
            return i;

    return -1;
}

size_t find(double* array, size_t size, bool (*predicate)(double value)) {
    for (size_t i = 0; i < size; ++i)
        if (predicate(array[i]))
            return i;

    return -1;
}

size_t find_reverse(int* array, size_t size,
    bool (*predicate)(int value)) {
    for (size_t i = size - 1; i >= 0; --i)
        if (predicate(array[i]))
            return i;

    return -1;
}

size_t find_reverse(double* array, size_t size,
    bool (*predicate)(double value)) {
    for (size_t i = size - 1; i >= 0; --i)
        if (predicate(array[i]))
            return i;

    return -1;
}

// BINARY_SEARCH

size_t bsearch(int* array, size_t size, int value) {
    size_t left = 0;
    size_t right = size;
    size_t middle = 0;

    while (left <= right) {
        middle = (left + right) / 2;

        if (array[middle] < value)
            left = middle + 1;
        else if (array[middle] > value)
            right = middle - 1;
        else
            return middle;
    }

    return -1;
}

size_t bsearch(double* array, size_t size, double value) {
    size_t left = 0;
    size_t right = size;
    size_t middle = 0;

    while (left <= right) {
        middle = (left + right) / 2;

        if (array[middle] < value)
            left = middle + 1;
        else if (array[middle] > value)
            right = middle - 1;
        else
            return middle;
    }

    return -1;
}

// COUNT ELEMENTS

size_t count(int* array, size_t size, bool (*predicate)(int value)) {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
        if (predicate(array[i]))
            count++;

    return count;
}

size_t count(double* array, size_t size, bool (*predicate)(double value)) {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
        if (predicate(array[i]))
            count++;

    return count;
}

// INPUT / OUTPUT

void _Input(int* array, size_t size) {
    cout << "Enter " << size << "elements" << endl;

    for (size_t i = 0; i < size; ++i) {
        cout << "array[" << i << "] = " << array[i];
        cin >> array[i];
    }
}

void _Input(double* array, size_t size) {
    cout << "Enter " << size << "elements" << endl;

    for (size_t i = 0; i < size; ++i) {
        cout << "array[" << i << "] = " << array[i];
        cin >> array[i];
    }
}

void _Input(int** out_array, size_t* out_size, const char* fileName) {
    ifstream file(fileName);
    string value;
    size_t size;

    file >> value;

    size = stoll(value);

    int* array = new int[size];

    for (size_t i = 0; i < size; ++i) {
        file >> value;
        array[i] = stoi(value);
    }

    file.close();

    *out_size = size;
    *out_array = array;
}

void _fileInput(double** out_array, size_t* out_size,
    const char* fileName) {
    ifstream file(fileName);
    string value;
    size_t size;

    file >> value;

    size = stoll(value);

    double* array = new double[size];

    for (size_t i = 0; i < size; ++i) {
        file >> value;
        array[i] = stof(value);
    }

    file.close();

    *out_size = size;
    *out_array = array;
}

void _binfileInput(int** out_array, size_t* out_size,
    const char* fileName) {
    ifstream file(fileName);

    size_t size;

    file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    int* array = new int[size];

    for (size_t i = 0; i < size; ++i) {
        file.read(reinterpret_cast<char*>(&array[i]), sizeof(int));
    }

    file.close();

    *out_array = array;
}

void _binfileInput(double** out_array, size_t* out_size,
    const char* fileName) {
    ifstream file(fileName);

    size_t size;

    file.read(reinterpret_cast<char*>(&size), sizeof(size_t));

    double* array = new double[size];

    for (size_t i = 0; i < size; ++i) {
        file.read(reinterpret_cast<char*>(&array[i]), sizeof(double));
    }

    file.close();

    *out_array = array;
}

void _Output(int* array, size_t size) {
    for (size_t i = 0; i < size; ++i)
        cout << "array[" << i << "] = " << array[i] << endl;
}

void _Output(double* array, size_t size) {
    for (size_t i = 0; i < size; ++i)
        cout << "array[" << i << "] = " << array[i] << endl;
}

void _fileOutput(int* array, size_t size, const char* fileName) {
    ofstream file(fileName);
    string value;

    value = to_string(size);

    file.write(value.c_str(), value.size());
    file.put('\n');

    for (size_t i = 0; i < size; ++i) {
        value = to_string(array[i]);
        file.write(value.c_str(), value.size());
        file.put('\n');
    }

    file.close();
}

void _fileOutput(double* array, size_t size, const char* fileName) {
    ofstream file(fileName);
    string value;

    value = to_string(size);

    file.write(value.c_str(), value.size());
    file.put('\n');

    for (size_t i = 0; i < size; ++i) {
        value = to_string(array[i]);
        file.write(value.c_str(), value.size());
        file.put('\n');
    }

    file.close();
}

void binfileOutput(int* array, size_t size, const char* fileName) {
    ofstream file(fileName);

    file.write(reinterpret_cast<char*>(&size), sizeof(size_t));

    for (size_t i = 0; i < size; ++i) {
        file.write(reinterpret_cast<char*>(&array[i]), sizeof(int));
    }

    file.close();
}

void binfileOutput(double* array, size_t size, const char* fileName) {
    ofstream file(fileName);

    file.write(reinterpret_cast<char*>(&size), sizeof(size_t));

    for (size_t i = 0; i < size; ++i) {
        file.write(reinterpret_cast<char*>(&array[i]), sizeof(double));
    }

    file.close();
}

// PREDICATES

bool predicateTrue(int value) { return true; }

bool predicateTrue(double value) { return true; }

bool predicateFalse(int value) { return false; }

bool predicateFalse(double value) { return false; }

bool predicatePositive(int value) { return value >= 0; }

bool predicatePositive(double value) { return value >= 0.f; }

bool predicateNegative(int value) { return value < 0; }

bool predicateNegative(double value) { return value < 0.f; }
