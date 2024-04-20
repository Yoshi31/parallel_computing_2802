#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int m;
    int n;

    cout << "Enter thread count (m): ";
    cin >> m;

    cout << "Enter number count (n): ";
    cin >> n;

    int sum = 0;

#pragma omp parallel num_threads(m) reduction(+:sum)
    {
        int id = omp_get_thread_num();
        int partial_sum = 0;

        for (int i = id + 1; i <= n; i += m) {
            partial_sum += i;
        }

#pragma omp critical
        cout << "[" << id << "] : Partial Sum = " << partial_sum << endl;

#pragma omp atomic
        sum += partial_sum;
    }

    cout << "Total Sum = " << sum << endl;

    return 0;
}