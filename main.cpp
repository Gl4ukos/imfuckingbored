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
    cam.samples_per_pixel = 4;

    const double cam_translation_speed = 0.2;
    const double cam_rotation_speed = 0.1;
    vec3 cam_pos(0,0,0);

    int move=0;

    sf::RenderWindow window(
        sf::VideoMode(cam.image_width, cam.get_image_height()),
        "Ray Tracer"
    );
    sf::Texture texture;
    texture.create(cam.image_width, cam.get_image_height());
    sf::Sprite sprite(texture);


    cam.set_camera_center(0,0,0);

    while(window.isOpen()){
        sf::Event event;
    
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        vec3 move_direction(0,0,0);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            move_direction += cam.get_forward()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            move_direction += - cam.get_forward()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            move_direction += - cam.get_right()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            move_direction += cam.get_right()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            move_direction += cam.get_up()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            move_direction += - cam.get_up()*cam_translation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            cam.yaw -= cam_rotation_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            cam.yaw += cam_rotation_speed;
        }
        cam_pos += move_direction;
        cam.set_camera_center(cam_pos.x(), cam_pos.y(), cam_pos.z());
        std::cout<<"\r"<<cam_pos.x()<<std::flush;

        std::vector<uint8_t> frame = cam.render_frame(world);
        texture.update(frame.data());

        window.clear();
        window.draw(sprite);
        window.display();
    }
}


