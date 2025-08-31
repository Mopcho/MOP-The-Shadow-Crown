#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define GRID_CELL_SIZE 100.0f;
#define FPS 60

#if defined(_WIN32) && defined(MOPENGINE_SHARED)
  #if defined(MOPENGINE_MAKEDLL)
    #define MOPENGINE_API __declspec(dllexport)
  #else
    #define MOPENGINE_API __declspec(dllimport)
  #endif
#else
  #define MOPENGINE_API
#endif

#endif //CONSTANTS_HPP
