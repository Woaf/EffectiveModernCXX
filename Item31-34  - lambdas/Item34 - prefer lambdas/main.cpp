#include <iostream>
#include <functional>
#include <chrono>

using Time = std::chrono::steady_clock::time_point;

enum class Sound {
    Beep, 
    Siren, 
    Whistle
};

using Duration = std::chrono::steady_clock::duration;

void SetAlarm (Time t, Sound s, Duration d); // defined elsewhere

using namespace std::chrono;
using namespace std::literals;
// using lambda
auto setSoundL = [] (Sound s) {

    SetAlarm (steady_clock::now () + 1h, 
              s, 
              30s);
};  

// using std::bind
using std::placeholders;
auto setSoundB = std::bind (SetAlarm, 
                            steady_clock::now () + 1h, 
                            _1, 
                            30s);

int main ()
{
    // ...

    return 0;
}
