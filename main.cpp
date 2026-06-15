#include <iostream>

#include "color.h"
#include "vec3.h"

int main(){
    // Image
    int image_width = 256;
    int image_height = 256;

    //Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j=0; j<image_height; j++){
        int progress = (int)((double)j/(image_height-1) * 10);
        
        // Cosmetic 
        std::clog << "\r [";
        for (int i=0; i<progress; i++){
            std::clog <<"|";
        }
        for(int i=progress; i<10; i++){
            std::clog<<"-";
        }
        std::clog << "]"<<std::flush;


        for (int i=0; i<image_width; i++){
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }
}