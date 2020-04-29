#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

int main()
{
    srand(time(nullptr));

    int width, height, depth;
    cout << "width: ";
    cin >> width;
    cout << "height: ";
    cin >> height;
    cout << "depth: ";
    cin >> depth;
    vector<vector<vector<float>>> vect(depth);

    for (int i = 0; i < depth; ++i) {
        vect[i].resize(height);
        for (int j = 0; j < height; ++j) {
            vect[i][j].resize(width);
            for (int k = 0; k < width; ++k) {
                vect[i][j][k] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            }
        }
    }
    ofstream fout("data.txt");
    fout << width << ' ' << height << ' ' << depth << endl << endl;
    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < width; ++k) {
                fout << vect[i][j][k] << ' ';
            }
            fout << endl;
        }
        fout << endl;
    }

    fout.close();
    return 0;
}
