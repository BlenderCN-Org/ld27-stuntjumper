//
//  k2_vec3.h
//  p1
//
//  Created by Justin Bowes on 2013-02-27.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef p1_k2_vec3_h
#define p1_k2_vec3_h

#include <stdbool.h>

#include "xpl.h"
#include "k2_vec2.h"
#include "k2_ivec2.h"

/**
 * Tuple of 3 floats
 *
 * Each field can be addressed using several aliases:
 *  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
 *  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
 *  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
 */
typedef union _xv3 {
	float data[3];   /**< All components at once    */
    
	struct {
		float x;     /**< Alias for first component */
		float y;     /**< Alias for second component */
		float z;     /**< Alias for third component  */
	};
    
	struct {
		float s;      /**< Alias for first component */
		float t;      /**< Alias for second component */
		float p;      /**< Alias for third component  */
	};
    
	struct {
		float r;     /**< Alias for first component */
		float g;     /**< Alias for second component */
		float b;     /**< Alias for third component  */
	};
    
	struct {
		float red;   /**< Alias for first component */
		float green; /**< Alias for second component */
		float blue; /**< Alias for third component  */
	};
    
    struct {
        xvec2 xy;
        float _z;
    };
    
    struct {
        float _x;
        xvec2 yz;
    };
} xvec3;

static const xvec3 xvec3_x_axis = {{ 1.0f, 0.0f, 0.0f }};
static const xvec3 xvec3_y_axis = {{ 0.0f, 1.0f, 0.0f }};
static const xvec3 xvec3_z_axis = {{ 0.0f, 0.0f, 1.0f }};
static const xvec3 xvec3_zero   = {{ 0.0f, 0.0f, 0.0f }};

K2_INLINE xvec3 xvec3_set(float x, float y, float z) {
	xvec3 r = {{ x, y, z }};
	return r;
}

K2_INLINE xvec3 xvec3_all(float v) {
    return xvec3_set(v, v, v);
}

K2_INLINE xvec3 xvec3_add(xvec3 a, xvec3 b) {
    return xvec3_set(a.x + b.x, a.y + b.y, a.z + b.z);
}

K2_INLINE xvec3 xvec3_sub(xvec3 a, xvec3 b) {
	xvec3 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
}


K2_INLINE xvec3 xvec3_copy(xvec3 v) {
	return xvec3_set(v.x, v.y, v.z);
}

K2_INLINE xvec3 xvec3_cross(xvec3 a, xvec3 b) {
    xvec3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

K2_INLINE float xvec3_dot(xvec3 a, xvec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

K2_INLINE int xvec3_equal(xvec3 a, xvec3 b, float epsilon) {
    return fabsf(a.x - b.x) < epsilon &&
    fabsf(a.y - b.y) < epsilon &&
    fabsf(a.z - b.z) < epsilon;
}

K2_INLINE xvec3 xvec3_extend(xvec2 v, float z) {
	return xvec3_set(v.x, v.y, z);
}

K2_INLINE xvec3 xvec3_extendi(xivec2 v, float z) {
	return xvec3_set((float)v.x, (float)v.y, z);
}

K2_INLINE float xvec3_length_sq(xvec3 v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

K2_INLINE float xvec3_length(xvec3 v) {
	return sqrtf(xvec3_length_sq(v));
}

K2_INLINE xvec3 xvec3_abs(xvec3 v) {
    xvec3 r = {{ fabsf(v.x), fabsf(v.y), fabsf(v.z) }};
    return r;
}

K2_INLINE xvec3 xvec3_absmin(xvec3 a, xvec3 b) {
    xvec3 abs_a = xvec3_abs(a);
    xvec3 abs_b = xvec3_abs(b);
    xvec3 r = {{
        abs_a.x < abs_b.x ? a.x : b.x,
        abs_a.y < abs_b.y ? a.y : b.y,
        abs_a.z < abs_b.z ? a.z : b.z
    }};
    return r;
}


K2_INLINE xvec3 xvec3_absmax(xvec3 a, xvec3 b) {
    xvec3 abs_a = xvec3_abs(a);
    xvec3 abs_b = xvec3_abs(b);
    xvec3 r = {{
        abs_a.x > abs_b.x ? a.x : b.x,
        abs_a.y > abs_b.y ? a.y : b.y,
        abs_a.z > abs_b.z ? a.z : b.z
    }};
    return r;
}

K2_INLINE float xvec3_max_component(xvec3 v) {
    return xmax(v.x, xmax(v.y, v.z));
}

K2_INLINE float xvec3_min_component(xvec3 v) {
    return xmin(v.x, xmin(v.y, v.z));
}

K2_INLINE xvec3 xvec3_mul(xvec3 a, xvec3 b) {
    xvec3 r = {{
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    }};
    return r;
}

K2_INLINE xvec3 xvec3_scale(xvec3 v, float s) {
	xvec3 r = v;
	r.x *= s;
	r.y *= s;
	r.z *= s;
	return r;
}

K2_INLINE xvec3 xvec3_mix(const xvec3 a, const xvec3 b, float mix) {
	if (mix < 0.f) return xvec3_mix(b, a, -mix);
	return xvec3_add(xvec3_scale(a, 1.0f - mix),
                     xvec3_scale(b, mix));
}

K2_INLINE xvec3 xvec3_normalize(const xvec3 v) {
	return xvec3_scale(v, 1.0 / xvec3_length(v));
}

K2_INLINE float xvec3_distance_sq(const xvec3 p1, const xvec3 p2) {
	return xvec3_length_sq(xvec3_sub(p1, p2));
}

K2_INLINE float xvec3_distance(const xvec3 p1, const xvec3 p2) {
	return sqrtf(xvec3_distance_sq(p1, p2));
}

K2_INLINE float xvec3_distance_sq_to_line(const xvec3 point, const xvec3 line_p0, const xvec3 line_p1, xvec3 *point_on_line_out) {
    xvec3 v = xvec3_sub(point, line_p0);
    xvec3 s = xvec3_sub(line_p1, line_p0);
    float s_len_sq = xvec3_length_sq(s);
    float dot = xvec3_dot(v, s) / s_len_sq;
    xvec3 disp = xvec3_scale(s, dot);
    
    if (point_on_line_out) *point_on_line_out = xvec3_add(line_p0, disp);
    
    xvec3 r = xvec3_sub(v, disp);
    return xvec3_length_sq(r);
}

K2_INLINE float xvec3_distance_to_line(const xvec3 point, const xvec3 line_p0, const xvec3 line_p1, xvec3 *point_on_line_out) {
    return sqrtf(xvec3_distance_sq_to_line(point, line_p0, line_p1, point_on_line_out));
}

K2_INLINE float xvec3_point_inside_triangle(const xvec3 triangle[3], const xvec3 point) {
    xvec3 u = xvec3_sub(triangle[1], triangle[0]);
    xvec3 v = xvec3_sub(triangle[2], triangle[0]);
    xvec3 w = xvec3_sub(point, triangle[0]);
    
    float uu = xvec3_dot(u, u);
    float uv = xvec3_dot(u, v);
    float vv = xvec3_dot(v, v);
    float wu = xvec3_dot(w, u);
    float wv = xvec3_dot(w, v);
    float d = uv * uv - uu * vv;
    
    float inv_d = 1.0f / d;
    float s = (uv * wv - vv * wu) * inv_d;
    if (s < 0 || s > 1) return false;
    
    float t = (uv * wu - uu * wv) * inv_d;
    if (t < 0 || (s + t) > 1) return false;
    
    return true;
}

K2_INLINE float xvec3_point_inside_polygon(const xvec3 *vertices, size_t vertex_count, const xvec3 point) {
    size_t triangle_count = vertex_count - 2;
    for (size_t i = 0; i < triangle_count; ++i) {
        if (xvec3_point_inside_triangle(&vertices[i], point)) return true;
    }
    return false;
}

#include "k2_ivec3.h"
K2_INLINE void xvec3_decompose(xvec3 v, xivec3 *i0, xivec3 *ix, float *mixx, xivec3 *iy, float *mixy, xivec3 *iz, float *mixz) {
	*i0 = (xivec3) { floorf(v.x),	floorf(v.y),	floorf(v.z) };
	*ix = (xivec3) { ceilf(v.x),	i0->y,			i0->z		};
	*iy = (xivec3) { i0->x,			ceilf(v.y),		i0->z		};
	*iz = (xivec3) { i0->x,			i0->y,			ceilf(v.z)	};
	*mixx = fabsf(v.x - i0->x);
	*mixy = fabsf(v.y - i0->y);
	*mixz = fabsf(v.z - i0->z);
}

static char cbuf[128];
K2_INLINE const char * xvec3_str(xvec3 *vec) {
	snprintf(cbuf, 128, "[%f, %f, %f]", vec->data[0], vec->data[1], vec->data[2]);
    return cbuf;
}

#endif

