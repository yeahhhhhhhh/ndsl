#include <stdio.h>
#include <string.h>
#include "uuid.h"
#include "Guid.h"

namespace ndsl {
namespace utils {

Guid::Guid(){}

void Guid::generate(guid_t gu){
	uuid_generate(gu);
	unpack(gu, *this);
}

void Guid::toString(guid_t gu,  char* str){
	char* str2 = str;
	for(int i = 0; i < 16; i++){
		sprintf(str2, "%02X", gu[i]);
		str2 += 2;
	}
}

bool Guid::operator==(const Guid& guid){
	COMPARE(this->time_low, guid.time_low);
	COMPARE(this->time_mid, guid.time_mid);
	COMPARE(this->time_hi_and_version, guid.time_hi_and_version);
	COMPARE(this->clock_seq, guid.clock_seq);
	for (int i = 0; i < 6; i++){
		COMPARE(this->node[i], guid.node[i]);
	}
	return true;
}

void Guid::pack(const Guid &guid, guid_t &ptr){
	uint32_t tmp;
	unsigned char *out = ptr;
	
	tmp = guid.time_low;
	out[3] = (unsigned char) tmp;
	tmp >>= 8;
	out[2] = (unsigned char) tmp;
	tmp >>= 8;
	out[1] = (unsigned char) tmp;
	tmp >>= 8;
	out[0] = (unsigned char) tmp;
	
	tmp = guid.time_mid;
	out[5] = (unsigned char) tmp;
	tmp >>= 8;
	out[4] = (unsigned char) tmp;
	
	tmp = guid.time_hi_and_version;
	out[7] = (unsigned char) tmp;
	tmp >>= 8;
	out[6] = (unsigned char) tmp;
	
	tmp = guid.clock_seq;
	out[9] = (unsigned char) tmp;
	tmp >>= 8;
	out[8] = (unsigned char) tmp;
	
	memcpy(out+10, guid.node, 6);
}

void Guid::unpack(const guid_t in, Guid &guid){
	const uint8_t *ptr = in;
	uint32_t tmp;
	
	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	tmp = (tmp << 8) | *ptr++;
	tmp = (tmp << 8) | *ptr++;
	guid.time_low = tmp;
	
	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	guid.time_mid = tmp;
	
	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	guid.time_hi_and_version = tmp;
	
	tmp = *ptr++;
	tmp = (tmp << 8) | *ptr++;
	guid.clock_seq = tmp;
	
	memcpy(guid.node, ptr, 6);
}


} // namespace utils
} // namespace ndsl
