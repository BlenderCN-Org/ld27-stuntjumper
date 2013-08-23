//
//  k2_gl.h
//  k2-osx
//
//  Created by Justin Bowes on 2012-09-29.
//  Copyright (c) 2012 Informi Software. All rights reserved.
//

#ifndef k2_osx_k2_gl_h
#define k2_osx_k2_gl_h

#error OOB for this project

// ------------- OpenGL -------------------
// Include this file first. gl3w macroizes
// calls to opengl and is sensitive to include
// order.
// ----------------------------------------

// Need to set winver before GL headers are included
#include "k2_platform.h"

#if defined(K2_PLATFORM_IOS)
#	define K2_GLES
#	import <OpenGLES/ES2/gl.h>
#	import <OpenGLES/ES2/glext.h>
#	define glBindFragDataLocation	glBindFragDataLocationOES
#	define glBindVertexArray		glBindVertexArrayOES
#	define glDeleteVertexArrays		glDeleteVertexArraysOES
#	define glDrawArraysInstanced	glDrawArraysInstancedOES
#	define glGenVertexArrays		glGenVertexArraysOES
#else
#	if defined(K2_PLATFORM_OSX)
#		define GL_ARB_shader_objects // disable conflicts in the apple GL headers
#	endif
#	include "GL3/gl3w.h"
#	include "GL3/gl3.h"
#endif

#endif
