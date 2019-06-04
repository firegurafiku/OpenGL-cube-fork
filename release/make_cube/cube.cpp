#include "cube.h"

void Cube::writeData(const std::string& normal, float x, float y, float z)
{
    int width = 13;
    vertices << normal << std::setw(width) << x << ' ' <<
                          std::setw(width) << y << ' ' <<
                          std::setw(width) << z << ' ' <<
                          std::endl;
}

Cube::Cube(int segmentation)
    : segmentation(segmentation)
{
    vertices << std::fixed << std::setprecision(10);
    int count = 0;
    float curr_x;
    float curr_y;
    float curr_z;
    float step;

    // front
    curr_y = -0.5;
    curr_z = 0.5;
    step = 1.0 / segmentation;
    std::string normal = " 0.0  0.0  1.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_x = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x,        curr_y,        curr_z);
            writeData(normal, curr_x + step, curr_y,        curr_z);
            writeData(normal, curr_x + step, curr_y + step, curr_z);
            writeData(normal, curr_x,        curr_y + step, curr_z);
            curr_x += step;
            count += 4;
        }
        curr_y += step;
    }


    // back
    curr_y = -0.5;
    curr_z = -0.5;
    normal = " 0.0  0.0 -1.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_x = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x,        curr_y,        curr_z);
            writeData(normal, curr_x,        curr_y + step, curr_z);
            writeData(normal, curr_x + step, curr_y + step, curr_z);
            writeData(normal, curr_x + step, curr_y,        curr_z);
            curr_x += step;
            count += 4;
        }
        curr_y += step;
    }


    // left
    curr_x = -0.5;
    curr_y = -0.5;
    normal = "-1.0  0.0  0.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_z = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x, curr_y,        curr_z       );
            writeData(normal, curr_x, curr_y,        curr_z + step);
            writeData(normal, curr_x, curr_y + step, curr_z + step);
            writeData(normal, curr_x, curr_y + step, curr_z       );
            curr_z += step;
            count += 4;
        }
        curr_y += step;
    }

    // right
    curr_x = 0.5;
    curr_y = -0.5;
    normal = " 1.0  0.0  0.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_z = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x, curr_y,        curr_z       );
            writeData(normal, curr_x, curr_y + step, curr_z       );
            writeData(normal, curr_x, curr_y + step, curr_z + step);
            writeData(normal, curr_x, curr_y,        curr_z + step);
            curr_z += step;
            count += 4;
        }
        curr_y += step;
    }

    // top
    curr_x = -0.5;
    curr_y = 0.5;
    normal = " 0.0  1.0  0.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_z = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x,        curr_y, curr_z       );
            writeData(normal, curr_x,        curr_y, curr_z + step);
            writeData(normal, curr_x + step, curr_y, curr_z + step);
            writeData(normal, curr_x + step, curr_y, curr_z       );
            curr_z += step;
            count += 4;
        }
        curr_x += step;
    }

    // bottom
    curr_x = -0.5;
    curr_y = -0.5;
    normal = " 0.0 -1.0  0.0 ";
    for(int i = 0; i < segmentation; ++i){
        curr_z = -0.5;
        for(int j = 0; j < segmentation; ++j){
            writeData(normal, curr_x,        curr_y, curr_z       );
            writeData(normal, curr_x + step, curr_y, curr_z       );
            writeData(normal, curr_x + step, curr_y, curr_z + step);
            writeData(normal, curr_x,        curr_y, curr_z + step);
            curr_z += step;
            count += 4;
        }
        curr_x += step;
    }


    std::ofstream out("../vertices.txt");
    out << count << std::endl;
    out << vertices.rdbuf();
}
