#include "stdafx.h"
#include "MemoryHelper.h"


MemoryHelper::MemoryHelper()
{
	LOG("MemoryHelper Object Constructed");
}


MemoryHelper::~MemoryHelper()
{
	LOG("MemoryHelper Object Destroyed");
}


int MemoryHelper::store_hero(float x, float y, bool col) {
	Hero* h = new(find_available_block(hero_head)) Hero(x, y, col);
	return 0;
}

int MemoryHelper::store_soldier(float x, float y, bool col) {
	Soldier* s = new(find_available_block(soldier_head)) Soldier(x, y, col);
	std::cout << "soldier created" << std::endl;
	std::cout << "soldier Address: " << s << std::endl;
	std::cout << "soldier xpos: " << s->getX() << std::endl;
	std::cout << "soldier ypos: " << s->getY() << std::endl;
	std::cout << "soldier col: " << s->getCollision() << std::endl;
	return 0;
}

int MemoryHelper::store_spl_soldier(float x, float y, bool col) {
	SplSoldier* spl = new(find_available_block(spl_soldier_head)) SplSoldier(x, y, col);
	return 0;
}

int MemoryHelper::store_livingObj(float x, float y, bool col) {
	LivingObj* lobj = new(find_available_block(livingObj_head)) LivingObj(x, y, col);
	return 0;
}

int MemoryHelper::store_worldObj(float x, float y, bool col) {
	WorldObj* wobj = new(find_available_block(worldObj_head)) WorldObj(x, y, col);
	return 0;
}

int MemoryHelper::store_projectile(float x, float y, bool col) {
	Projectile* p = new(find_available_block(projectile_head)) Projectile(x, y, col);
	return 0;
}

int MemoryHelper::store_npc(float x, float y, bool col) {
	NPC* npc = new(find_available_block(npc_head)) NPC(x, y, col);
	return 0;
}

/////////////////////////////////////////
/*Stuff that was originally in Main*/
/////////////////////////////////////////


void* MemoryHelper::find_available_block(MemNode* head_ptr) {
	if (head_ptr == NULL)
		return NULL;
	MemNode* mnode = head_ptr;
	while (mnode != NULL) {
		if (mnode->getAvailability()) {
			mnode->setAvailability(false);
			return mnode->getBlockPointer();
		}
		mnode = mnode->getNext();
	}
	return NULL;
}

MemNode* MemoryHelper::make_Available(MemNode* head_ptr, MemoryPool* p, size_t node_number) {
	size_t count = 0;
	MemNode* h = head_ptr;
	if (node_number >= p->num_of_blocks)
		return NULL;
	for (size_t i = 0; i <= node_number; ++i) {
		if (node_number != 0) {
			if (h->hasNext())
				h = h->getNext();
		}
	}
	h->setAvailability(true);
	return h;
}

void MemoryHelper::destroy_MemNode_list(MemNode* head_ptr) {
	MemNode* tmp;
	while (head_ptr != NULL) {
		tmp = head_ptr;
		head_ptr = head_ptr->getNext();
		tmp->setBlockPointer(NULL);
		free(tmp);
	}
	std::cout << "Memory Nodes Destroyed" << std::endl;

}

/*Return Val: A pointer to the start of the malloced memory AKA the start
of the memory pool.
Argument(s): Takes an unsigned integer value that specifies the size of the
pool in bytes
Creates a memory pool, but does not call MemoryPool constructor.
Instead the pool exists as malloced memory that is
managed by next and end pointers. */

MemoryPool* MemoryHelper::create_pool(size_t sizeInBytes) {
	MemoryPool* p = (MemoryPool*)malloc(sizeInBytes + sizeof(MemoryPool));
	p->next = (char*)&p[1];
	p->end = p->next + sizeInBytes;
	p->pool_size = sizeInBytes;
	std::cout << "pool created" << std::endl;
	return p;
}

void MemoryHelper::destroy_pool(MemoryPool* p) {
	free(p);
	p->next = NULL;
	p->end = NULL;
	std::cout << "pool destroyed" << std::endl;
}

size_t MemoryHelper::get_free_pool_size(MemoryPool* p) {
	return p->end - p->next;
}

/*Return Value: Returns a pointer to the head of a MemNode linked list.
Arguments: Takes a pointer to the memory pool to initialize and the size in
bytes of each memory block/segment.
Creates a list of MemNodes that each store a pointer to the next node in the
list, a boolean specifying whether or not a block in the malloced memory
is available,and a pointer to a location in the malloced memory/a memory block.
Note. the block_size argument must be chosen based on the pool's size because
(pool size)/(block_size) = number of memory blocks. Must have whole number
for number of blocks.*/

MemNode* MemoryHelper::init_pool(MemoryPool *p, size_t bsize) {
	p->block_size = bsize;
	p->num_of_blocks = ((p->pool_size) / (p->block_size));
	if (get_free_pool_size(p) < bsize)
		return NULL;
	MemNode* tail;
	MemNode* head = new MemNode();
	void* memor = (void*)p->next;
	head->setAvailability(true);
	head->setBlockPointer(memor);
	p->next += bsize;
	tail = head;
	//create the list of MemNodes
	while (p->next != p->end) {
		MemNode* newNode = new MemNode();
		newNode->setAvailability(true);
		newNode->setNext(NULL);
		tail->setNext(newNode);
		tail = newNode;
		void* mem = (void*)p->next;
		newNode->setBlockPointer(mem);
		p->next += bsize;
	}
	std::cout << "pool initialized" << std::endl;
	return head;
}


