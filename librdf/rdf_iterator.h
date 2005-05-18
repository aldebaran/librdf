/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * rdf_iterator.h - RDF Iterator definition
 *
 * $Id$
 *
 * Copyright (C) 2000-2004, David Beckett http://purl.org/net/dajobe/
 * Institute for Learning and Research Technology http://www.ilrt.bristol.ac.uk/
 * University of Bristol, UK http://www.bristol.ac.uk/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 * 
 */



#ifndef LIBRDF_ITERATOR_H
#define LIBRDF_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*librdf_iterator_map_handler)(librdf_iterator *iterator, void *map_context, void *item);
typedef void (*librdf_iterator_map_free_context_handler)(void *map_context);

#ifdef LIBRDF_INTERNAL

/* used in map_list below */
typedef struct {
  void *context; /* context to pass on to map */
  librdf_iterator_map_handler fn;
  librdf_iterator_map_free_context_handler free_context;
} librdf_iterator_map;

struct librdf_iterator_s {
  librdf_world *world;
  void *context;
  int is_finished; /* 1 when have no more elements */
  int is_updated; /* 1 when we know there is a current item */

  /* Used when mapping */
  void *current;            /* stores current element */
  librdf_list *map_list; /* non-empty means there is a list of maps */
  
  int (*is_end_method)(void*);
  int (*next_method)(void*);
  void* (*get_method)(void*, int); /* flags: type of get */
  void (*finished_method)(void*);
};

/* FIXME - should all short lists be enums */
#define LIBRDF_ITERATOR_GET_METHOD_GET_OBJECT  0
#define LIBRDF_ITERATOR_GET_METHOD_GET_CONTEXT 1
#define LIBRDF_ITERATOR_GET_METHOD_GET_KEY     2
#define LIBRDF_ITERATOR_GET_METHOD_GET_VALUE   3

#endif

REDLAND_API librdf_iterator* librdf_new_iterator(librdf_world *world, void *context, int (*is_end_method)(void*), int (*next_method)(void*), void* (*get_method)(void*, int), void (*finished_method)(void*));

REDLAND_API void librdf_free_iterator(librdf_iterator*);

REDLAND_API int librdf_iterator_end(librdf_iterator* iterator);
REDLAND_API REDLAND_DEPRECATED int librdf_iterator_have_elements(librdf_iterator* iterator);

REDLAND_API int librdf_iterator_finished(librdf_iterator* iterator);

REDLAND_API int librdf_iterator_next(librdf_iterator* iterator);
REDLAND_API void* librdf_iterator_get_object(librdf_iterator* iterator);
REDLAND_API void* librdf_iterator_get_context(librdf_iterator* iterator);
REDLAND_API void* librdf_iterator_get_key(librdf_iterator* iterator);
REDLAND_API void* librdf_iterator_get_value(librdf_iterator* iterator);

REDLAND_API int librdf_iterator_add_map(librdf_iterator* iterator, librdf_iterator_map_handler map_function, librdf_iterator_map_free_context_handler free_context, void *map_context);

REDLAND_API librdf_iterator* librdf_new_empty_iterator(librdf_world *world);

#ifdef __cplusplus
}
#endif

#endif
