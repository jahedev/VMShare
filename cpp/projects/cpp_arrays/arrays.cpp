#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int test_scores [5] {100, 99, 98, 87, 65}; 
    int n = sizeof(test_scores) / sizeof(test_scores[0]);
    // int cars_per_garage [5] {3, 2}; // rest are equal to 0

    cout << "Printing Array:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << *(test_scores+i) << endl; 
    };

    // VECTORS

    vector<char> vowels {'a', 'e', 'i', 'o', 'u'};
    // vector<int> tests (5); // all initialized to 0
    // vector<double> temperatures (5, 100.0); // all 5 doubles are equal to 100.0

    // for (char vowel : vowels)
    // {
    //     cout << "Vowel: " << vowel << endl;
    // }

    // for (auto it = vowels.begin(); it != vowels.end(); it++) {
    //     int idx = std::distance(vowels.begin(), it);
    //     cout << "Vowel " << idx << ": " << vowels[idx] << endl;
    // }

    // for (long unsigned int i = 0; i < vowels.size(); i++) {
    //     cout << "Vowel " << i << ": " << vowels[i] << endl;
    // }

    for (char &i : vowels)
    {
        int idx = &i - &vowels[0];
        cout << "Vowel " << idx << ": " << vowels[idx] << endl;
    }

    vector<int> nums (5, 10);
    // nums.push_back(5); // adds to end of list
    // nums.clear(); // deletes everything
    nums.push_back(6);
    nums.push_back(7);
    nums.push_back(8);


    for (long unsigned int i = 0; i < nums.size(); i++)
    {
        cout << "Nums: " << nums.at(i) << endl;
    }

    // 2D Vector
    vector<vector<int>> movie_ratings
    {
        {1,2,3,4},
        {3,5,3,2},
        {4,4,5,5}
    };

    cout << endl << "Movie Ratings:" << endl;

    for (auto ratings : movie_ratings)
    {
        for (auto rating : ratings)
        {
            cout << rating << " ";
        }

        cout << endl;
    }

    for (auto c : "America") cout << c << endl;
}