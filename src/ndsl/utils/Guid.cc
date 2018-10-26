////
// @file Guid.cc
// @brief
// Guid实现类
//
// @author why
// @email 136046355@qq.com
//
#include "Guid.h"
#include <stdio.h>
#include <uuid/uuid.h>

namespace ndsl {
namespace utils {

Guid::Guid(){}

void Guid::guidGenerate(guid_t gu){
	uuid_generate(gu);
	
}
void Guid::guid2String(guid_t gu,  char* str){
	char* str2 = str;
	for(int i = 0; i < 16; i++){
		sprintf(str2, "%02X", gu[i]);
		str2 += 2;
	}
}
int Guid::guidCompare(guid_t gu1, guid_t gu2){
	return uuid_compare(gu1, gu2);
}

void Guid::guidStringGenerate(char* str){
	guid_t gu;
	guidGenerate(gu);
	guid2String(gu, str);
}

int Guid::guidStringCompare(char* str1, char* str2){
	for(int i = 0; i < 32; i++){
		if(str1 == str2){
			str1++;
			str2++;
		}else{
			return -1;
		}
	}
	return 0;
}

} // namespace utils
} // namespace ndsl