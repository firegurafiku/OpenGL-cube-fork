#include <sstream>
#include <fstream>
#include <iomanip>

class Cube{
public:
    Cube(int segmentation);
private:
    int segmentation;
    std::stringstream vertices;
    void writeData(const std::string& normal, float x, float y, float z);
};