#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <stdlib.h>
#include <stdint.h>

/// A dynamic array that grows as elements are added.
struct __string_t{
	char* content;   /// The content of the container
	size_t size;     /// The size of the elements in the container	
	size_t capacity; /// The current maximum size of the container
}; 

struct __string_view_t{
	size_t size;     /// The size of the elements in the container	
	char* begin; 	/// Points to the part of the content which begins the string_view
	char* end; 	/// Points to the part of the content which ends the string_view
}; 

typedef struct __string_t string_t;
typedef struct __string_view_t string_view_t;

extern void prints(char* arr, size_t size);
extern string_t string_new (string_t* arr, size_t n);
extern string_t* string_create(char* text, size_t n);
extern string_view_t* string_view(char* arr, size_t _index_s, size_t _index_e);
extern int8_t string_push(string_t* arr, char* elem, size_t n);
extern int8_t string_remove_at(string_t* arr, size_t _index_s, size_t _index_e);
extern int8_t string_insert(string_t* arr, size_t index, char* elem, size_t n);
extern string_t* string_substring(string_t* arr, string_t* dst, size_t _index_s, size_t _index_e);

#endif
