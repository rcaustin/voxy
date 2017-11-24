#include "Timer.hh"


Clock::Clock()
  : m_start{0} {

}

const Milliseconds Clock::GetElapsedTime() const {

  return SDL_GetTicks() - m_start;
}

const Milliseconds Clock::Restart() {

  Milliseconds elapsed = SDL_GetTicks() - m_start;
  m_start = 0;
  return elapsed;
}

Timer::Timer(Milliseconds p_timeStep)
  : m_frameTimeStep{p_timeStep},
    m_timeSinceLastStateChange{0},
    m_timeSinceLastStatsUpdate{0},
    m_statsFrameCount{0} {

  m_statsFPS       = std::make_shared<size_t>(0);
  m_statsFrameTime = std::make_shared<size_t>(0);
}

void Timer::BeginFrame() {

  Milliseconds elapsedMilliseconds = m_clock.Restart();
  m_timeSinceLastStateChange      += elapsedMilliseconds;
  m_timeSinceLastStatsUpdate      += elapsedMilliseconds;
  m_statsFrameCount               += 1;
}

void Timer::EndFrame() {

  if (m_timeSinceLastStatsUpdate >= sm_STATISTICS_UPDATE_INTERVAL) {
    (*m_statsFPS)              = m_statsFrameCount;
    (*m_statsFrameTime)        = m_timeSinceLastStatsUpdate * 1000 / m_statsFrameCount;
    m_statsFrameCount          = 0;
    m_timeSinceLastStatsUpdate = 0;
  }
}

bool Timer::Tick() {

  return m_timeSinceLastStateChange >= m_frameTimeStep;
}

void Timer::Tock() {

  m_timeSinceLastStateChange -= m_frameTimeStep;
}
