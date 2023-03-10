/**
 * @file player.hpp
 * @author mateuskrause
 *
 * @brief
 *
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <cmath>
#include "box2d/box2d.h"
#include "game-objects.hpp"
#include "engine/include/animation.hpp"
#include "audio.hpp"

#define PLAYER_MAX_LINEAR_VELOCITY 4

// raycast callback. check for closest object
struct RayCastClosestCallback : public b2RayCastCallback
{
    b2Fixture *m_closestFixture = nullptr;
    b2Vec2 m_closestPoint;
    float m_closestFraction = 1.0f;
    b2Body *m_closestBody = nullptr;

    float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction);
};

// player action
enum player_action
{
    idle,
    running_left,
    running_right,
    jump,
    hook,
    glide,
    falling,
};

// everything related to player
class Player
{
private:
    Box hook_end;
    // sf::RectangleShape player_aim;
    sf::Texture player_aim_texture;
    sf::Sprite player_aim;
    float aim_angle;
    float aim_angle_rad;

    // hook
    b2DistanceJointDef hook_joint_def;
    b2DistanceJoint *hook_joint;
    sf::Texture hook_texture;

    bool hook_end_attached;
    bool player_on_ground;
    bool in_action_jump;
    bool in_action_glide;
    bool is_hook_impulse_applied;

    float original_gravity_scale;

    b2World *world;

    // player animations
    player_action previous_action;

    // audio
    Audio walking_audio;
    Audio jump_audio;
    Audio hook_hit_audio;
    Audio hit_ground_audio;
    Audio glide_audio;

public:
    std::vector<pte::Animation *> animations;
    float width;
    float height;
    b2BodyDef body_def;
    b2Body *body;
    player_action action;

    sf::RectangleShape shape;
    sf::Color color;

    Player(b2World *world, int x, int y, float width, float height, float density, float friction, sf::Color color);

    void update_player_state(sf::RenderWindow &window, sf::View &view);
    void update_player_animation(float delta_time);
    void move_player_right();
    void move_player_left();
    void action_jump();
    void action_glide();
    void use_hook(sf::RenderWindow &window, std::vector<Box> &box_vec);
    void decrease_hook_length();
    void destroy_hook();

    void render_player(sf::RenderWindow &window);
    void render_player_aim(sf::RenderWindow &window);
    void render_hook(sf::RenderWindow &window);
};

#endif