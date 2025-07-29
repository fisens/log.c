/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct {
  va_list ap;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#if defined(LOG_C_DISABLE_FATAL) && !defined(LOG_C_DISABLE_ERROR)
#define LOG_C_DISABLE_ERROR
#endif
#if defined(LOG_C_DISABLE_ERROR) && !defined(LOG_C_DISABLE_WARN)
#define LOG_C_DISABLE_WARN
#endif
#if defined(LOG_C_DISABLE_WARN) && !defined(LOG_C_DISABLE_INFO)
#define LOG_C_DISABLE_INFO
#endif
#if defined(LOG_C_DISABLE_INFO) && !defined(LOG_C_DISABLE_DEBUG)
#define LOG_C_DISABLE_DEBUG
#endif
#if defined(LOG_C_DISABLE_DEBUG) && !defined(LOG_C_DISABLE_TRACE)
#define LOG_C_DISABLE_TRACE
#endif

#if !defined(LOG_C_DISABLE_TRACE)
#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_trace(...)
#endif

#if !defined(LOG_C_DISABLE_DEBUG)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_debug(...)
#endif

#if !defined(LOG_C_DISABLE_INFO)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_info(...)
#endif

#if !defined(LOG_C_DISABLE_WARN)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_warn(...)
#endif

#if !defined(LOG_C_DISABLE_ERROR)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_error(...)
#endif

#if !defined(LOG_C_DISABLE_FATAL)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#else
#define log_fatal(...)
#endif

const char* log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
int log_get_level();
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
