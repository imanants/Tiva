#include"ds\ds.h"
#include"generic\generic.h"
uint16_t strlen( const unsigned  char *  str_ptr)
{
	uint16_t length = 0u;
	while(*(str_ptr++) != NULL)
	{
		length++;
	}
	return length;
}