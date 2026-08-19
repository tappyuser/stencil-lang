#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// A dynamic array that grows as elements are added.
typedef struct {
	char* content;   // The content of the container
	size_t size;     // The size of the elements in the container	
	size_t capacity; // The current maximum size of the container
} string_t; 

extern string_t string_new (string_t* arr, size_t n){
	arr->size = 0;
	arr->capacity = n;
	arr->content = (char*)malloc(sizeof(char) * n);

	return *arr;
}

extern int8_t string_push(string_t* arr, char* elem, size_t n){
	if (n == 0) return -1;

	/// Doubles the capacity if the container would not contain it. If the doubled capacity is still not enough, then it sets it to the required capacity.
	if (arr->capacity < arr->size + n){
		arr->capacity = arr->capacity * 2 < arr->size + n ? arr->size + n : arr->capacity * 2;
	}

	if(arr->size == 0){
		memcpy(arr->content, elem, n);
	} else {
		/// Reallocate memory for the arr->content and copy the memory
		char* temp = arr->content; 
		arr->content = (char*)malloc(sizeof(char) * arr->capacity);
		
		/// Copy the element into the arr->content buffer
		memcpy(arr->content, temp, arr->size);
		for (size_t i = arr->size; i < arr->size + n; i++){
			arr->content[i] = elem[i - arr->size];
		}
		free((void*)temp);
	}
	arr->size += n;
	return 0;
}

#endif
