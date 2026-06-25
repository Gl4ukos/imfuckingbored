#include "rtweekend.h"
#include <unistd.h> 
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


int main() {

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 100;
    cam.update_image_height();
    cam.samples_per_pixel = 10;

    double cam_x =0;
    double cam_y =0;
    double cam_z =0;
    const double cam_speed = 0.5;

    int move=0;

    sf::RenderWindow window(
        sf::VideoMode(cam.image_width, cam.get_image_height()),
        "Ray Tracer"
    );
    sf::Texture texture;
    texture.create(cam.image_width, cam.get_image_height());
    sf::Sprite sprite(texture);


    cam.set_camera_center(0,0,0);
    // cam.render(world);    

    // exit(0);
    while(window.isOpen()){
        sf::Event event;
    
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            cam_z -= cam_speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            cam_z += cam_speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            cam_x -= cam_speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            cam_x += cam_speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            cam_y -= cam_speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            cam_y += cam_speed;



        cam.set_camera_center(cam_x,cam_y,cam_z);
    
        std::clog << "\rCamera position: " << cam_x << "      " << std::flush;

        std::vector<uint8_t> frame = cam.render_frame(world);
        texture.update(frame.data());

        window.clear();
        window.draw(sprite);
        window.display();
    }
}


