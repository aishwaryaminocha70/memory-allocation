The signature of the method is as follows:

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id);

*/

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id) {

struct MEMORY_BLOCK temp_memory_block, allocated_memory;

allocated_memory.end_address = 0;

allocated_memory.start_address = 0;

allocated_memory.process_id = 0;

allocated_memory.segment_size = 0;

bool match = false;

int memory_map_index = 0 , best_fit_segmant = 0;

// Identify the first-fit version, testing multiple memory to see which one is

first

for (int i = 0; i <= *map_cnt - 1; i++) {

if (request_size <= memory_map[i].segment_size) {

match = true;

memory_map_index = i;

best_fit_segmant = request_size;

break;

}

}

//After identifying the match, going to switch the load

if (match == true){

temp_memory_block = memory_map[memory_map_index];

allocated_memory.start_address = temp_memory_block.start_address;

allocated_memory.end_address = allocated_memory.start_address +

request_size - 1;

allocated_memory.process_id = process_id;

allocated_memory.segment_size = request_size;

*map_cnt = *map_cnt + 1;

for (int i = memory_map_index; i <= *map_cnt; i++){

memory_map[memory_map_index+1] = memory_map[i];

}

memory_map[memory_map_index+1].start_address =

allocated_memory.end_address + 1;

memory_map[memory_map_index+1].end_address =

memory_map[memory_map_index].end_address;

memory_map[memory_map_index+1].process_id =

memory_map[memory_map_index].process_id;

memory_map[memory_map_index+1].segment_size =

memory_map[memory_map_index].segment_size - request_size;

memory_map[memory_map_index] = allocated_memory;

}

return allocated_memory;

}

/*

------------------------------Third memory block structure allocating the worst

memory---------------------------------------

*/

/*

The signature of the method is as follows:

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id);

*/

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id) {

struct MEMORY_BLOCK temp_memory_block, allocated_memory;

allocated_memory.end_address = 0;

allocated_memory.start_address = 0;

allocated_memory.process_id = 0;

allocated_memory.segment_size = 0;

bool match = false;

int memory_map_index = 0 , worst_fit_segmant = 0;

// Identify the worst-fit version, identifying the worst match, and replacing

for (int i = 0; i <= *map_cnt - 1; i++) {

if ((memory_map[i].segment_size >= request_size) &&

(memory_map[i].process_id == 0)) {

if (match == false){

match = true;

memory_map_index = i;

worst_fit_segmant = memory_map[i].segment_size;

}

else {

if (worst_fit_segmant < memory_map[i].segment_size){

memory_map_index = i;

worst_fit_segmant = memory_map[i].segment_size;

}

}

}

}

//After identifying the match, going to switch the load

if (match == true){

temp_memory_block = memory_map[memory_map_index];

allocated_memory.start_address = temp_memory_block.start_address;

allocated_memory.end_address = allocated_memory.start_address +

request_size - 1;

allocated_memory.process_id = process_id;

allocated_memory.segment_size = request_size;

*map_cnt = *map_cnt + 1;

for (int i = memory_map_index; i <= *map_cnt; i++){

memory_map[memory_map_index+1] = memory_map[i];

}

memory_map[memory_map_index+1].start_address =

allocated_memory.end_address + 1;

memory_map[memory_map_index+1].end_address =

memory_map[memory_map_index].end_address;

memory_map[memory_map_index+1].process_id =

memory_map[memory_map_index].process_id;

memory_map[memory_map_index+1].segment_size =

memory_map[memory_map_index].segment_size - request_size;

memory_map[memory_map_index] = allocated_memory;

}

return allocated_memory;

}

/*

------------------------------Fourth memory block structure allocating the next

memory---------------------------------------

*/

/*

The signature of the method is as follows:

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id, int last_address);

*/

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id, int last_address) {

struct MEMORY_BLOCK temp_memory_block, allocated_memory;

allocated_memory.end_address = 0;

allocated_memory.start_address = 0;

allocated_memory.process_id = 0;

allocated_memory.segment_size = 0;

bool match = false;

int memory_map_index = 0 , best_fit_segmant = 0;

int index = 0;

// Identify the next-fit version, seeing which one is next, saving

for (int i = last_address; i <= *map_cnt+ last_address - 1; i++) {

if (i >= *map_cnt){

index = i - *map_cnt;

}

else

index = i;

if ((request_size <= memory_map[index].segment_size) &&

(memory_map[i].process_id == 0)){

match = true;

memory_map_index = index;

best_fit_segmant = request_size;

break;

}

}

//After identifying the match, going to switch the load

if (match == true){

temp_memory_block = memory_map[memory_map_index];

allocated_memory.start_address =

temp_memory_block.start_address;

allocated_memory.end_address = allocated_memory.start_address

+ request_size - 1;

allocated_memory.process_id = process_id;

allocated_memory.segment_size = request_size;

*map_cnt = *map_cnt + 1;

for (int i = memory_map_index; i <= *map_cnt; i++){

memory_map[memory_map_index+1] = memory_map[i];

}

memory_map[memory_map_index+1].start_address =

allocated_memory.end_address + 1;

memory_map[memory_map_index+1].end_address =

memory_map[memory_map_index].end_address;

memory_map[memory_map_index+1].process_id =

memory_map[memory_map_index].process_id;

memory_map[memory_map_index+1].segment_size =

memory_map[memory_map_index].segment_size - request_size;

memory_map[memory_map_index] = allocated_memory;

}

return allocated_memory;

}

/*

--------------------Final Section for releasing the

memory-----------------------------

*/

/*

The signature of the method is as follows:

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt);

*/

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt) {

bool flag = false;

if ((*map_cnt == 1) && (memory_map[0].end_address == 0) &&

(memory_map[0].start_address == 0) && (memory_map[0].process_id == 0) &&

(memory_map[0].segment_size == 0))

return;

else {

for (int i = 0; i < *map_cnt; i++){

if((freed_block.start_address == memory_map[i].start_address)

&& (freed_block.end_address == memory_map[i].end_address) &&

(freed_block.process_id == memory_map[i].process_id)) {

memory_map[i].process_id = 0;

if (i > 0){

if (memory_map[i-1].process_id == 0){

memory_map[i-1].end_address =

freed_block.end_address;

memory_map[i-1].segment_size = memory_map[i1].segment_size + freed_block.segment_size;

for (int index = i; index <= *map_cnt;

index++){

memory_map[index] = memory_map[index +

1];

}

*map_cnt = *map_cnt - 1;

flag = true;

}

}

if (i < *map_cnt-1){

if (flag == false){

i = i+1;

}

if (memory_map[i].process_id == 0){

memory_map[i].start_address = memory_map[i1].start_address;

memory_map[i].segment_size =

memory_map[i].end_address -memory_map[i].start_address+1;

for (int index = i; index <= *map_cnt;

index++){

memory_map[index-1] =

memory_map[index];

}

*map_cnt = *map_cnt - 1;

}

}

break;

}

}

}

}

/*

------------------------------End of the main memory.c code, the main would be

implemented below this if not run through

CL---------------------------------------

*/

/*

Main file used if we were to TEST IT LOCALLY, and for REFERENCE

int main () {

struct MEMORY_BLOCK memory_map[MAPMAX], new_memory_block;

int cnt = 1;

int *map_cnt;

map_cnt = &cnt;

memory_map[0].end_address = 1023;

memory_map[0].start_address = 0;

memory_map[0].process_id = 0;

memory_map[0].segment_size = 1024;

new_memory_block = best_fit_allocate(10, memory_map, map_cnt, 1);

new_memory_block = best_fit_allocate(15, memory_map, map_cnt, 2);

new_memory_block = best_fit_allocate(120, memory_map, map_cnt, 3);

new_memory_block = best_fit_allocate(50, memory_map, map_cnt, 4);

new_memory_block = best_fit_allocate(32, memory_map, map_cnt, 5);

struct MEMORY_BLOCK free;

free.start_address = FILL;

free.end_address = FILL;

free.segment_size = FILL;

free.process_id = 2;

release_memory(free, memory_map, map_cnt);

free.start_address = FILL;

free.end_address = FILL;

free.segment_size = FILL;

free.process_id = 3;

release_memory(free, memory_map, map_cnt);

free.start_address = FILL;

free.end_address = FILL;

free.segment_size = FILL;

free.process_id = 4;

release_memory(free, memory_map, map_cnt);

return 0;

}

*/
