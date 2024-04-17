#pragma once
#include <dispatch/dispatch.h>

typedef void (*TimerHandler)(void);

static void timerHandlerWrapper(void *context) {
  TimerHandler handler = *(TimerHandler *)context;
  handler();
}

static void timerFinalizer(void *context) {
  TimerHandler *handlerPtr = (TimerHandler *)context;
  free(handlerPtr);
}

static dispatch_source_t createTimer(TimerHandler handler) {
  dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0));
  TimerHandler *handlerPtr = malloc(sizeof(TimerHandler));
  *handlerPtr = handler;
  dispatch_set_context(timer, handlerPtr);
  dispatch_set_finalizer_f(timer, timerFinalizer);
  dispatch_source_set_event_handler_f(timer, timerHandlerWrapper);
  return timer;
}

static void startIntervalTimer(dispatch_source_t timer, long long nsec) {
  uint64_t interval = nsec / NSEC_PER_SEC;
  dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, 0), interval * NSEC_PER_SEC, 0);
  dispatch_resume(timer);
}

static inline long long ns(int ns) { return ns; }

static inline long long us(int us) { return us * 1000; }

static inline long long ms(int ms) { return ms * 1000000; }

static inline long long s(int s) { return s * 1000000000; }
