//
//  k2_gl_debug.h
//  xpl-osx
//
//  Created by Justin Bowes on 2012-09-29.
//  Copyright (c) 2012 Informi Software. All rights reserved.
//

#ifndef k2_osx_k2_gl_debug_h
#define k2_osx_k2_gl_debug_h

#include "k2_gl.h"

const char *k2_gl_get_error_string(GLenum e);

#ifdef DEBUG
#define DEBUG_GL
#endif

#ifdef DEBUG_GL
/** DEBUG macros. **/

#include "k2_log.h"

#define GL_DEBUG() \
    { \
        GLenum e; \
        while ((e = glGetError()) != GL_NO_ERROR) { \
            LOG_ERROR("GL_DEBUG error: 0x%x %s", e, k2_gl_get_error_string(e)); \
            k2_gl_breakpoint_func(); \
        } \
    }

#define GL_DEBUG_THIS(x) \
    x; \
    GL_DEBUG();

#define GL_CLEAR_ERROR() \
	{ \
		GLenum e; \
		while ((e = glGetError()) != GL_NO_ERROR) { \
			LOG_INFO("Clearing error: 0x%x %s", e, k2_gl_get_error_string(e)); \
		} \
	}


// end debug macros

void k2_gl_breakpoint_func(void);
void k2_gl_debug_install(void);
void k2_gl_log_bound_textures(void);

#else
/** Non GL_DEBUG macros. Should be no-ops. */

#define GL_DEBUG_THIS(x) x
#define GL_DEBUG()
#define GL_CLEAR_ERROR()
#define k2_gl_breakpoint_func()
#define k2_gl_debug_install()
#define k2_gl_log_bound_textures()

// end release macros
#endif

#endif
