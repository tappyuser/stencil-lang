
## NAME
string_util.h

## DESCRIPTION
A header file that contains string_t type and functions.

## IDENTIFIER SYNOPSIS
typedef struct {
	char* content;   // The content of the container
	size_t size;     // The size of the elements in the container	
	size_t capacity; // The current maximum size of the container
} string_t; 

extern string_t string_new (string_t* arr, size_t n)
extern int8_t string_push(string_t* arr, char* elem, size_t n)
extern int8_t string_remove_at(string_t* arr, size_t _index_s, size_t _index_e)

## IDENTIFIER DESCRIPTION
string_t            - The string container or type
string_new          - Initializes the container
string_insert       - Inserts an element into the string_t container at a specific index. Returns -1 if it is out of bounds
string_remove_at    - Removes a range of characters from the container
string_substr       - Creates a new string that is the substring of another string
string_find         - Gets the index of an element from the container. Returns -1 if not found  
string_pop          - Removes the last element - NOT IMPLEMENTED
string_push         - Pushes an element to the end of a container
prints              - Prints the content of a buffer 



To initialize a new container, use the `string_new` function
```C
string_t arr;
string_new(&arr, 0);
string_insert(&arr, "Hwllo", 5);
string_insert(&arr, "Hellooi0\n", 10);
string_insert(&arr, "something random", 10);

printf(arr.content);
printf("%d\n", arr.size);
```
