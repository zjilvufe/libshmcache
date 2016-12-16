/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

//shmopt.h

#ifndef _SHMOPT_H
#define _SHMOPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "common_define.h"
#include "shmcache_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
init share memory segment
parameters:
	context: the context pointer
    segment: the segment pointer
	proj_id: the project id to generate key
    size: the share memory size
return error no, 0 for success, != 0 for fail
*/
int shmopt_init_segment(struct shmcache_context *context,
        struct shmcache_segment_info *segment,
        const int proj_id, const int64_t size);

/**
create and init share memory value segment
parameters:
	context: the context pointer
return error no, 0 for success, != 0 for fail
*/
int shmopt_create_value_segment(struct shmcache_context *context);


/**
open share memory value segment
parameters:
	context: the context pointer
return error no, 0 for success, != 0 for fail
*/
int shmopt_open_value_segments(struct shmcache_context *context);

/**
alloc a node from the context
parameters:
	context: the context pointer
    index: value segment index
return the value segment ptr, return NULL if fail
*/
static inline char *shmopt_get_value_segment(struct shmcache_context *context,
        const int index)
{
    if (index < context->segments.values.count) {
        return context->segments.values.items[index].base;
    } else if (index < context->memory->vm_info.segment.count.current) {
        if (shmopt_open_value_segments(context) != 0) {
            return NULL;
        }
        return context->segments.values.items[index].base;
    } else {
        return NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif

