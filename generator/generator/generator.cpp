#include<iostream>
#include<cmath>
#include<vector>
#include<iomanip>

long long FindPeriod(long long A, long long B, long long C, long long D,
    long long seed_0, long long seed_1, long long seed_2) {
    long long achilles_1 = seed_2, achilles_2 = seed_1, achilles_3 = seed_0;
    long long turtle_1 = seed_2, turtle_2 = seed_1, turtle_3 = seed_0;
    achilles_1 = (achilles_1 * A % D + achilles_2 * B % D + achilles_3 * C % D) % D;
    achilles_2 = turtle_1;
    achilles_3 = turtle_2;
    for (;;) {
        long long tmp = achilles_1;
        achilles_1 = (achilles_1 * A % D + achilles_2 * B % D + achilles_3 * C % D) % D;
        achilles_3 = achilles_2;
        achilles_2 = tmp;
        tmp = achilles_1;
        achilles_1 = (achilles_1 * A % D + achilles_2 * B % D + achilles_3 * C % D) % D;
        achilles_3 = achilles_2;
        achilles_2 = tmp;
        tmp = turtle_1;
        turtle_1 = (turtle_1 * A % D + turtle_2 * B % D + turtle_3 * C % D) % D;
        turtle_3 = turtle_2;
        turtle_2 = tmp;
        if (turtle_1 == achilles_1 && turtle_2 == achilles_2 && turtle_3 == achilles_3) break;
    }
    long long cnt = 1;
    turtle_1 = (turtle_1 * A % D + turtle_2 * B % D + turtle_3 * C % D) % D;
    turtle_3 = turtle_2;
    turtle_2 = achilles_1;
    for (;;) {
        long long tmp = turtle_1;
        turtle_1 = (turtle_1 * A % D + turtle_2 * B % D + turtle_3 * C % D) % D;
        turtle_3 = turtle_2;
        turtle_2 = tmp;
        ++cnt;
        if (turtle_1 == achilles_1 && turtle_2 == achilles_2 && achilles_3 == turtle_3) {
            break;
        }
    }
    return cnt;
}

long long FindPreperiod(long long A, long long B, long long C, long long D, 
    long long seed_0, long long seed_1, long long seed_2, long long P) {
    long long a_1 = seed_2, a_2 = seed_1, a_3 = seed_0;
    long long b_1 = seed_2, b_2 = seed_1, b_3 = seed_0;
    for (long long i = 0; i < P; ++i) {
        long long tmp = b_1;
        b_1 = (b_1 * A % D + b_2 * B % D + b_3 * C % D) % D;
        b_3 = b_2;
        b_2 = tmp;
    }
    if (a_1 == b_1 && a_2 == b_2 && a_3 == b_3) {
        return 0;
    }
    long long cnt = 0;
    for (;;) {
        long long tmp = b_1;
        b_1 = (b_1 * A % D + b_2 * B % D + b_3 * C % D) % D;
        b_3 = b_2;
        b_2 = tmp;
        tmp = a_1;
        a_1 = (a_1 * A % D + a_2 * B % D + a_3 * C % D) % D;
        a_3 = a_2;
        a_2 = tmp;
        ++cnt;
        if (a_1 == b_1 && a_2 == b_2 && a_3 == b_3) {
            break;
        }
    }
    return cnt;
}

std::vector<double> GetNumbers(long long A, long long B, long long C, long long D,
    long long seed_0, long long seed_1, long long seed_2) {
    std::vector<double> numbers;
    numbers.reserve(400);
    numbers.push_back(static_cast<double>(seed_0) / D);
    numbers.push_back(static_cast<double>(seed_1) / D);
    numbers.push_back(static_cast<double>(seed_2) / D);
    long long x_1 = seed_2, x_2 = seed_1, x_3 = seed_0;
    for (long long i = 0; i < 397; ++i) {
        long long tmp = x_1;
        x_1 = (x_1 * A % D + x_2 * B % D + x_3 * C % D) % D;
        x_3 = x_2;
        x_2 = tmp;
        numbers.push_back(static_cast<double>(x_1) / D);
    }
    return numbers;
}

double Goodness(long long A, long long B, long long C, long long D, std::vector<double>& numbers) {
    std::vector<long long> segments(20);
    for (int i = 0; i < 400; ++i) {
        ++segments[floor(numbers[i] * 20)];
    }
    double sigma = 0;
    for (int i = 0; i < 19; ++i) {
        sigma += ((static_cast<double>(segments[i] - 20) * (segments[i] - 20))) / 400;
    }
    return sigma;
}

int main() {
    std::cout << std::setprecision(5);
    std::cout << std::fixed;
    long long A, B, C, D, seed_0, seed_1, seed_2;
    std::cin >> A >> B >> C >> D >> seed_0 >> seed_1 >> seed_2;
    seed_1 %= D, seed_2 %= D, seed_0 %= D;
    long long P = FindPeriod(A, B, C, D, seed_0, seed_1, seed_2);
    long long N = FindPreperiod(A, B, C, D, seed_0, seed_1, seed_2, P);
    std::vector<double> numbers = GetNumbers(A, B, C, D, seed_0, seed_1, seed_2);
    double goodness = Goodness(A, B, C, D, numbers);
    std::cout << "Length of period is " << P << '\n';
    std::cout << "Length of pre-period is " << N << '\n';
    std::cout << "Goodness of the generator is " << goodness;
}
