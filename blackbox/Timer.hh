#ifndef TIMER_HH
#define TIMER_HH

#include <SDL2/SDL.h>

#include <cstdint>
#include <memory>


using Milliseconds = Uint32;

class Clock {

public:
                          Clock();

  const Milliseconds      GetElapsedTime() const;
  const Milliseconds      Restart();

private:
  Milliseconds            m_start;
};

class Timer {

public:
                          Timer(Milliseconds p_timeStep = sm_MILLISECONDS_PER_FRAME_AT_60FPS);

  void                    BeginFrame();
  void                    EndFrame();

  bool                    Tick();
  void                    Tock();

  const float             GetDeltaTime() const { return m_frameTimeStep; }
  std::shared_ptr<size_t> GetFrameRate() const { return m_statsFPS; }
  std::shared_ptr<size_t> GetFrameTime() const { return m_statsFrameTime; }

private:
  Clock                   m_clock;
  Milliseconds            m_frameTimeStep;
  Milliseconds            m_timeSinceLastStateChange;

  Milliseconds            m_timeSinceLastStatsUpdate;
  std::size_t             m_statsFrameCount;
  std::shared_ptr<size_t> m_statsFPS;
  std::shared_ptr<size_t> m_statsFrameTime;

  static constexpr Milliseconds sm_MILLISECONDS_PER_FRAME_AT_60FPS{1000 / 60};
  static constexpr Milliseconds sm_STATISTICS_UPDATE_INTERVAL{1000};
};

#endif  // TIMER
