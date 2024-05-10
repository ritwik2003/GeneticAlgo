#include <bits/stdc++.h>

using namespace std;

struct Solution
{

    double rank, x, y, z;
    void fitness()
    {
        double ans = (6 * x - y + pow(z, 200)) - 25;
        rank = (ans == 0) ? 9999 : abs(1 / ans);
    }
};

int main()
{
    int iterations;
    cout << "enter the number of iterations: ";
    cin >> iterations;
    // create intial random solutions

    random_device device;
    uniform_real_distribution<double> unif(-100, 100);
    vector<Solution> solutions;

    const int NUM = 100000;
    for (int i = 0; i < NUM; i++)
    {
        solutions.push_back(Solution{
            0, unif(device), unif(device), unif(device)});
    }

    int curr = 0;

    while (curr < iterations)
    {
        cout << "results after " << curr << " mutations" << endl;
        // Run fitness function
        for (auto &s : solutions)
        {
            s.fitness();
        }

        // sorting solutions based on fitness
        sort(solutions.begin(), solutions.end(),
             [](const auto &lhs, const auto &rhs)
             {
                 return lhs.rank > rhs.rank;
             });

        //  print top solutions
        std::for_each(solutions.begin(), solutions.begin() + 10, [](const auto &s)
                      { cout << fixed << "Rank : " << static_cast<int>(s.rank) << "\n x: " << s.x << " y: " << s.y << " z: " << s.z << "\n"; });

        cout << endl
             << endl
             << endl;

        //  take top solutions
        const int sample_size = 1000;
        vector<Solution> sample;
        std::copy(solutions.begin(), solutions.begin() + 1000, back_inserter(sample));
        solutions.clear();

        //  mutate top solutions by %

        uniform_real_distribution<double> m(0.99, 1.01);
        std::for_each(sample.begin(), sample.end(), [&](auto &s)
                      { 
        s.x *= m(device);
        s.y *= m(device);
        s.z *= m(device); });

        // crossover
        uniform_int_distribution<int> cross(0, sample_size - 1);
        for (int i = 0; i < NUM; i++)
        {
            solutions.push_back(Solution{
                0,
                sample[cross(device)].x,
                sample[cross(device)].y,
                sample[cross(device)].z});
        }
        curr++;
    }
}