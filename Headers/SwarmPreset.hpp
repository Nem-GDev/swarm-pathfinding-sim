#pragma once
#include <SFML\Graphics.hpp>

namespace swt
{
    struct SwarmPreset
    {
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        //! Screen dimensions must be divisable by heatmap resolution!
        const int HEATMAP_SOURCE_RESOLUTION;
        const int HEATMAP_PATH_RESOLUTION;
        const int SWARM_WIDTH;
        const int SWARM_HEIGHT;

        const int COLONY_SIZE;
        const float SWARM_OBEDIENCE;
        //? Lower MaxPheromone = Higher Unity, Stability.
        //? Higher MaxPheromone = Higher mutation & new paths; Faster pathmap regeneration. Less Stability & Unity.
        const float SWARM_MAX_PHEROMONE;
        //? Depletion >= Decay for reversed path disappearance
        //? (Depletion+Decay)/Max_Pheromone = Relative range
        const float SWARM_PHEROMONE_DEPLETION;
        const float SWARM_PHEROMONE_DECAY;
        const float SWARM_MOVE_STEPS;
        const float SWARM_NOISE;
        const int SWARM_NOISE_POLLRATE;
        const int SWARM_NOISE_DIRECTIONS;
    };
    static constexpr SwarmPreset PRESET_CUSTOM{
        1024, // SCREEN_WIDTH;
        1024, // SCREEN_HEIGHT;
        32,   // HEATMAP_SOURCE_RESOLUTION;
        2,    // HEATMAP_PATH_RESOLUTION;
        4,    // SWARM_WIDTH
        8,    // SWARM_HEIGHT;

        1200,  // COLONY_SIZE;
        400,   // SWARM_OBEDIENCE;h
        28000, // SWARM_MAX_PHEROMONE;
        20,    // SWARM_PHEROMONE_DEPLETION;
        20,    // SWARM_PHEROMONE_DECAY;
        100,   // SWARM_MOVE_STEPS;
        0.25f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };

    static constexpr SwarmPreset PRESET_1{
        896, // SCREEN_WIDTH;
        896, // SCREEN_HEIGHT;
        64,  // HEATMAP_SOURCE_RESOLUTION;
        4,   // HEATMAP_PATH_RESOLUTION;
        10,  // SWARM_WIDTH
        20,  // SWARM_HEIGHT;

        300,   // COLONY_SIZE;
        600,   // SWARM_OBEDIENCE;
        3000,  // SWARM_MAX_PHEROMONE;
        2,     // SWARM_PHEROMONE_DEPLETION;
        2,     // SWARM_PHEROMONE_DECAY;
        200,   // SWARM_MOVE_STEPS;
        0.15f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };
    static constexpr SwarmPreset PRESET_2{
        896, // SCREEN_WIDTH;
        896, // SCREEN_HEIGHT;
        64,  // HEATMAP_SOURCE_RESOLUTION;
        4,   // HEATMAP_PATH_RESOLUTION;
        10,  // SWARM_WIDTH
        20,  // SWARM_HEIGHT;

        300,   // COLONY_SIZE;
        600,   // SWARM_OBEDIENCE;
        6000,  // SWARM_MAX_PHEROMONE;
        5,     // SWARM_PHEROMONE_DEPLETION;
        5,     // SWARM_PHEROMONE_DECAY;
        200,   // SWARM_MOVE_STEPS;
        0.15f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };

    static constexpr SwarmPreset PRESET_3{
        896, // SCREEN_WIDTH;
        896, // SCREEN_HEIGHT;
        64,  // HEATMAP_SOURCE_RESOLUTION;
        4,   // HEATMAP_PATH_RESOLUTION;
        10,  // SWARM_WIDTH
        20,  // SWARM_HEIGHT;

        300,   // COLONY_SIZE;
        700,   // SWARM_OBEDIENCE;
        8000,  // SWARM_MAX_PHEROMONE;
        8,     // SWARM_PHEROMONE_DEPLETION;
        8,     // SWARM_PHEROMONE_DECAY;
        200,   // SWARM_MOVE_STEPS;
        0.15f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };
    static constexpr SwarmPreset PRESET_LARGE1{
        1024, // SCREEN_WIDTH;
        1024, // SCREEN_HEIGHT;
        64,   // HEATMAP_SOURCE_RESOLUTION;
        4,    // HEATMAP_PATH_RESOLUTION;
        8,    // SWARM_WIDTH
        16,   // SWARM_HEIGHT;

        900,   // COLONY_SIZE;
        600,   // SWARM_OBEDIENCE;h
        2000,  // SWARM_MAX_PHEROMONE;
        2,     // SWARM_PHEROMONE_DEPLETION;
        2,     // SWARM_PHEROMONE_DECAY;
        200,   // SWARM_MOVE_STEPS;
        0.15f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };
    static constexpr SwarmPreset PRESET_MASSIVE1{
        1024, // SCREEN_WIDTH;
        1024, // SCREEN_HEIGHT;
        32,   // HEATMAP_SOURCE_RESOLUTION;
        2,    // HEATMAP_PATH_RESOLUTION;
        4,    // SWARM_WIDTH
        8,    // SWARM_HEIGHT;

        1200,  // COLONY_SIZE;
        300,   // SWARM_OBEDIENCE;h
        12000, // SWARM_MAX_PHEROMONE;
        8,     // SWARM_PHEROMONE_DEPLETION;
        8,     // SWARM_PHEROMONE_DECAY;
        50,    // SWARM_MOVE_STEPS;
        0.15f, // SWARM_NOISE;
        9,     // SWARM_NOISE_POLLRATE;
        23     // SWARM_NOISE_DIRECTIONS;
    };
}
