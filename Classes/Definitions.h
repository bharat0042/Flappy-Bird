#ifndef __DEFINATIONS__
#define __DEFINATIONS__

const static float DISPLAY_TIME_SPLASH_SCENE{ 2 };
const static bool DISPLAY_STATS{ false };
const static float TRANSITION_TIME{ 1.0 };

const static float PIPE_SPAWN_FREQUENCY{ 0.003 };
const static float UPPER_SCREEN_PIPE_THRESHOLD{ 0.7 };
const static float LOWER_SCREEN_PIPE_THRESHOLD{ 0.3 };
const static float PIPE_MOVEMENT_SPEED{ 0.01 };

const static float DOLLAR_SPAWN_FREQUENCY{ 0.004 };
const static float DOLLAR_MOVEMENT_SPEED{ 0.01 };

const static int BIRD_COLLISION_BITMASK{ 0x000001 };
const static int OBSTACLE_COLLISION_BITMASK{ 0x000002 };
const static int POINT_COLLISION_BITMASK{ 0x000003 };
const static int DOLLAR_COLLISION_BITMASK{ 0x000004 };

const static auto BIRD_FLYING_SPEED{ 0.00375 };
const static auto BIRD_FALLING_SPEED{ 0.0025 };
const static float BIRD_FLY_DURATION{ 0.20 };

const static int POINT_PASS_SCORE{ 10 };
const static int DOLLAR_SCORE{ 10 };

#endif // __DEFINATIONS__
