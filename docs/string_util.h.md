
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

extern void prints(char* arr, size_t size);
extern string_t string_new (string_t* arr, size_t n);
extern string_t* string_create(char* text, size_t n);
extern string_view_t* string_view(char* arr, size_t _index_s, size_t _index_e);
extern int8_t string_push(string_t* arr, char* elem, size_t n);
extern int8_t string_remove_at(string_t* arr, size_t _index_s, size_t _index_e);
extern int8_t string_insert(string_t* arr, size_t index, char* elem, size_t n);
extern string_t* string_substring(string_t* arr, string_t* dst, size_t _index_s, size_t _index_e);


## IDENTIFIER DESCRIPTION
string_t            - The string container or type
string_new          - Initializes the container
string_create       - Creates a new string_t from a char* 
string_insert       - Inserts an element into the string_t container at a specific index. Returns -1 if it is out of bounds
string_remove_at    - Removes a range of characters from the container
string_substring    - Creates a new string that is the substring of another string
string_find         - Gets the index of the first occurence of a character from the container. Returns -1 if not found  
string_pop          - Removes the last element - **NOT IMPLEMENTED AND MAY NOT BE**
string_push         - Pushes an element to the end of a container
prints              - Prints the content of a buffer 



## EXAMPLES
To initialize a new container, use the `string_new` function
```C
string_t arr;
string_new(&arr, 0);

printf(arr.content);
printf("%d\n", arr.size);
```

To use the `prints` function
```C
string_t arr;
string_new(&arr, 0);
prints(&arr, arr.size);
```
To use the `string_push` function
```C
string_t arr;
string_new(&arr, 0);

// Push some strings into the string
string_push(&arr, "Hwllo", 5);
string_push(&arr, "Hellooi0\n", 10);
string_push(&arr, "something random", 16);

prints(&arr, arr.size);
```

To use the `string_insert` function
```C
string_t arr;
string_new(&arr, 0);

// Inserts into the string
string_insert(&arr, 0, "Hello", 5);
string_insert(&arr, 3, "h", 1);

prints(arr.content, arr.size);
printf("%zu\n", arr.size);
```

To use the `string_remove_at` function
```C
string_t arr;
string_new(&arr, 0);

// Removes from the third character till the end of the string
string_remove_at(&arr, 2, arr.size);

prints(arr.content, arr.size);
printf("%zu\n", arr.size);
```

To use the `string_create` function
```C
string_t* arr = string_create("Hellow", 0);
prints(arr->content, arr->size);
```
