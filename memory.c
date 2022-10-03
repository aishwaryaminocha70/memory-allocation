#include "oslabs.h"

#include

#include

#include

//This lab project addresses the various memory-management schemes in an

operating system.

//In this lab project, we address the various ways in which memory can be

allocated (based on different schemes - Best Fit, First Fit, Next Fit, Worst

(Largest) Fit). In addition, we also develop a method to manage the release of

memory blocks by processes.

//For the purposes of these labs we define the NULLBLOCK as [start_address: 0,

end_address: 0, segment_size: 0, process_id: 0]

/*

Data structure of block of memories:

struct MEMORY_BLOCK {

int start_address;

int end_address;

int segment_size;

int process_id;

}

*/

/*

------------------------------First memory block structure allocating the best

memory---------------------------------------

*/

/*

The signature of the method is as follows:

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id);

*/

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK

memory_map[MAPMAX],int *map_cnt, int process_id) {

struct MEMORY_BLOCK temp_memory_block, allocated_memory;

allocated_memory.end_address = 0;

allocated_memory.start_address = 0;

allocated_memory.process_id = 0;

allocated_memory.segment_size = 0;

bool match = false;

int memory_map_index = 0 , best_fit_segmant = 0;

// Identify the best-fit version, testing multiple memory to see which one is

better suited

for (int i = 0; i <= *map_cnt - 1; i++) {

if (request_size == memory_map[i].segment_size) {

match = true;

memory_map_index = i;

best_fit_segmant = request_size;

break;

}

else if ((memory_map[i].segment_size > request_size) &&

(memory_map[i].process_id == 0)) {

if (match == false){

match = true;

memory_map_index = i;

best_fit_segmant = memory_map[i].segment_size;

}

else {

if (best_fit_segmant > memory_map[i].segment_size){

memory_map_index = i;

best_fit_segmant = memory_map[i].segment_size;

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
