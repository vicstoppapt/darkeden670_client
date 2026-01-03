#include "MMiniLZO.h"
#include "Assert.h"

HEAP_ALLOC(MMiniLZO::s_CompressWorkMemory, LZO1X_1_MEM_COMPRESS);
MMiniLZO MMiniLZO::s_MiniLZO;

MMiniLZO::MMiniLZO()
{
	int result = lzo_init();
	assert(result == LZO_E_OK);
}