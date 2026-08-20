#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "string_util.h"

/// Prints the contents of a buffer up to a specific size
extern void prints(char* arr, size_t size){
	for (int i = 0; i < size; i++)	putchar(arr[i]);
	putchar('\n');
}

extern string_t string_new (string_t* arr, size_t n){
	arr->size = 0;
	arr->capacity = n;
	arr->content = (char*)malloc(sizeof(char) * n);

	return *arr;
}

extern string_t* string_create(char* text, size_t n){
	/// Creates a string_t from char *
	/// It only supports null terminated strings
	/// The length n must be specified for non null terminated strings, otherwise it must be 0.
	n = n == 0 ? strlen(text) : n;
	string_t* arr = (string_t*)malloc(sizeof(char) * n);
	string_new(arr, n);
	string_insert(arr, 0, text, n);
	
	return arr;
}

extern int8_t string_insert(string_t* arr, size_t index, char* elem, size_t n){
	if (n == 0) {
	       	return -1; 
	}
	if (n > strlen(elem)) n = strlen(elem);

	/// Doubles the capacity if the container would not contain it. If the doubled capacity is still not enough, then it sets it to the required capacity.
	if (arr->capacity < arr->size + n){
		arr->capacity = arr->capacity * 2 < arr->size + n ? arr->size + n : arr->capacity * 2;
	}

	if(arr->size == 0){
		if (index != 0) return -1;	
		memcpy(arr->content, elem, n);
	} else {
		/// Reallocate memory for the arr->content and copy the memory
		char* temp = arr->content; 
		arr->content = (char*)malloc(sizeof(char) * arr->capacity);
		
		/// Copy the element into the arr->content buffer
		memcpy(arr->content, temp, index); /// Copies the begining of the string until the index
		memcpy(arr->content + index, elem, n); /// Copies the text at the specific index
		memcpy(arr->content + index + n, temp + index, arr->size - index); /// Copies the rest of the array 
		free((void*)temp);
	}
	arr->size += n;
	return 0;
}

extern int8_t string_push(string_t* arr, char* elem, size_t n){
	return string_insert(arr, arr->size, elem, n);
}

static int8_t _remove_at(string_t* arr, size_t _index_s, size_t _index_e){
	if (_index_e > arr->size || _index_s >= _index_e) return -1;
	char* temp = arr->content;
	arr->content = (char*)malloc(sizeof(char) * arr->capacity);
	memcpy(arr->content, temp, _index_s);
	memcpy(arr->content + _index_s, temp + _index_e, arr->size - _index_e);
	arr->size -= _index_e - _index_s;
	free((void*)temp);
	return 0;
}

extern int8_t string_remove_at(string_t* arr, size_t _index_s, size_t _index_e){
	/// Removes a range of characters from the container
	/// _index_s is inclusive 
	/// _index_e is exclusive
	return _remove_at(arr, _index_s, _index_e);
}

extern string_t* string_substring(string_t* arr, string_t* dst, size_t _index_s, size_t _index_e){
	if (_index_e > arr->size) return nullptr;
	if(memcpy(dst->content, arr->content + _index_s, _index_e) == nullptr){
		return nullptr;
	}
	dst->size = _index_e - _index_s + 1;
	return dst;
}

/* String View Functions */
extern string_view_t* string_view(char* arr, size_t _index_s, size_t _index_e){
	if (_index_s >= _index_e) return nullptr;
	string_view_t* _view = (string_view_t*)malloc(sizeof(string_view_t));
	_view->size = _index_e - _index_s;
	_view->begin = arr + _index_s;
	_view->end = arr + _index_e;

	return _view;
}

