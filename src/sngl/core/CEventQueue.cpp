#include "CEventQueue.h"

#include <SDL3/SDL.h>

using CEventQueue = sngl::core::CEventQueue;
using Event = sngl::core::Event;
using EngineEventType = sngl::core::EngineEventType;

void CEventQueue::pollWindowEvents()
{
   SDL_Event e;
   while (SDL_PollEvent(&e))
   {
      if (e.type == SDL_EVENT_QUIT)
      {
         m_events.emplace_back(Event{ .type = EngineEventType::WindowClose });
      }
   }
}