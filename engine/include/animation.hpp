#ifndef PTE_ANIMATION_HPP
#define PTE_ANIMATION_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace pte
{
    class Animation
    {
    private:
        sf::Texture spritesheet_texture;
        std::vector<sf::Sprite> sprites;

        int current_sprite = 0;
        float time_since_last_frame = 0.0f;
        float frame_interval = 0.1f;
        bool status = true;

    public:
        Animation(std::string filepath, int width, int height, int frames_qnt, int off_x, int off_y, float frame_interval);
        void update_animation(float delta_time);
        sf::Sprite *get_sprite();
        void reset();
        void pause();
        void play();
    };
}

#endif