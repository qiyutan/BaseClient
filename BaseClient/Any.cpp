#include <cstring>
#include <cassert>
#include "Any.h"

namespace qy
{

AnyArray::AnyArray()
{
}

AnyArray::AnyArray(const AnyArray &array)
{
	for(array_t::const_iterator it = array.m_array.begin(); it != array.m_array.end(); it++)
	{
		AnyItem newItem = *it;
		switch(it->type)
		{
		case TYPE_INT32:
			newItem.value = new int32_t(*(int32_t*)it->value);
			break;
		case TYPE_INT64:
			newItem.value = new int64_t(*(int64_t*)it->value);
			break;
		case TYPE_CHAR:
			newItem.value = new char(*(char*)it->value);
			break;
		case TYPE_DOUBLE:
			newItem.value = new double(*(double*)it->value);
			break;
		case TYPE_STRING:
			newItem.value = new char[it->len + 1];
			memcpy(newItem.value, it->value, it->len + 1);
		case TYPE_BYTES:
			newItem.value = new char[it->len];
			memcpy(newItem.value, it->value, it->len);
			break;
		case TYPE_ARRAY:
			newItem.value = new AnyArray(*(AnyArray*)it->value);
			break;
		case TYPE_MAP:
			newItem.value = new AnyMap(*(AnyMap*)it->value);
			break;
		default:
			break;
		}
		m_array.push_back(newItem);
	}
}

AnyArray::~AnyArray()
{
	array_t::const_iterator it = m_array.begin();
	for(; it != m_array.end(); it++)
	{
		switch(it->type)
		{
			case TYPE_INT32:
				delete (int32_t*)it->value;
				break;
			case TYPE_INT64:
				delete (int64_t*)it->value;
				break;
			case TYPE_DOUBLE:
				delete (double*)it->value;
				break;
			case TYPE_CHAR:
			case TYPE_STRING:
			case TYPE_BYTES:
				delete[] (char*)it->value;
				break;
			case TYPE_ARRAY:
				delete (AnyArray*)it->value;
				break;
			case TYPE_MAP:
				delete (AnyMap*)it->value;
				break;
			default:
				break;
		}
	}
}

void AnyArray::addChar(char ch)
{
	AnyItem item;
	item.type = TYPE_CHAR;
	item.len = sizeof(char);
	item.value = new char(ch);
	m_array.push_back(item);
}

void AnyArray::addInt32(int32_t value)
{
	AnyItem item;
	item.type = TYPE_INT32;
	item.len = sizeof(int32_t);
	item.value = new int32_t(value);
	m_array.push_back(item);
}

void AnyArray::addInt64(int64_t value)
{
	AnyItem item;
	item.type = TYPE_INT64;
	item.len = sizeof(int64_t);
	item.value = new int64_t(value);
	m_array.push_back(item);
}

void AnyArray::addDouble(double value)
{
	AnyItem item;
	item.type = TYPE_DOUBLE;
	item.len = sizeof(double);
	item.value = new double(value);
	m_array.push_back(item);
}

void AnyArray::addString(const char *value)
{
	if(!value) return;

	size_t len = strlen(value);
	if(len == 0) return;

	AnyItem item;
	item.type = TYPE_STRING;
	item.len = len + 1;
	item.value = new char[len + 1];
	memcpy(item.value, value, len + 1);
	m_array.push_back(item);
}

void AnyArray::addBytes(const char *value, size_t len)
{
	AnyItem item;
	item.type = TYPE_BYTES;
	item.len = len;
	item.value = new char[len];
	memcpy(item.value, value, len);
	m_array.push_back(item);
}

void AnyArray::addArray(const AnyArray *value)
{
	AnyItem item;
	item.type = TYPE_ARRAY;
	item.len = value->byteLength();
	item.value = new AnyArray(*value);
	m_array.push_back(item);
}

void AnyArray::addMap(const AnyMap *value)
{
	AnyItem item;
	item.type = TYPE_MAP;
	item.len = value->byteLength();
	item.value = new AnyMap(*value);
	m_array.push_back(item);
}

bool AnyArray::getChar(size_t index, char *value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_CHAR)
	{
		return false;
	}
	*value = *(char*)item.value;
	return true;
}

bool AnyArray::getInt32(size_t index, int32_t *value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_INT32)
	{
		return false;
	}
	*value = *(int32_t*)item.value;
	return true;
}

bool AnyArray::getInt64(size_t index, int64_t *value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_INT64)
	{
		return false;
	}
	*value = *(int64_t*)item.value;
	return true;
}

bool AnyArray::getDouble(size_t index, double *value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_DOUBLE)
	{
		return false;
	}
	*value = *(double*)item.value;
	return true;
}

bool AnyArray::getString(size_t index, char **value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_STRING)
	{
		return false;
	}
	*value = (char*)item.value;
	return true;
}

bool AnyArray::getBytes(size_t index, char **value, size_t *len) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_BYTES)
	{
		return false;
	}
	*value = (char*)item.value;
	*len = item.len;
	return true;
}

bool AnyArray::getArray(size_t index, AnyArray **value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_ARRAY)
	{
		return false;
	}
	*value = (AnyArray*)item.value;
	return true;
}

bool AnyArray::getMap(size_t index, AnyMap **value) const
{
	if(index >= m_array.size())
	{
		return false;
	}
	AnyItem item = m_array[index];
	if(item.type != TYPE_MAP)
	{
		return false;
	}
	*value = (AnyMap*)item.value;
	return true;
}

AnyType AnyArray::type(size_t index) const
{
	if(index >= m_array.size())
	{
		return TYPE_INVALID;
	}
	return m_array[index].type;
}

size_t AnyArray::byteLength() const
{
	size_t len = 0;
	array_t::const_iterator it = m_array.begin();
	while(it != m_array.end())
	{
		len += sizeof(it->type);
		len += sizeof(it->len);
		len += it->len;
		it++;
	}
	return len;
}

AnyArray *AnyArray::create(const char *data, size_t len)
{
	if(!data || len == 0)
	{
		return NULL;
	}

	size_t p = 0;
	AnyArray *pArray = new AnyArray();
	while(p < len)
	{
		AnyItem item;
		size_t k = sizeof(item.type);
		if(k + p > len) break;
		memcpy(&item.type, data + p, k);
		p += k;
		k = sizeof(item.len);
		if(k + p > len) break;
		memcpy(&item.len, data + p, k);
		p += k;
		k = item.len;
		if(k + p > len) break;
		if(item.type == TYPE_ARRAY)
		{
			AnyArray *pa = AnyArray::create(data + p, item.len);
			if(!pa) break;
			item.value = pa;
		}
		else if(item.type == TYPE_MAP)
		{
			AnyMap *pm = AnyMap::create(data + p, item.len);
			if(!pm) break;
			item.value = pm;
		}
		else
		{
			item.value = new char[item.len];
			memcpy(item.value, data + p, k);
		}
		p += k;
		pArray->m_array.push_back(item);
	}
	if(p != len)
	{
		delete pArray;
		pArray = NULL;
	}
	return pArray;
}

bool AnyArray::serialize(char **data, size_t *len) const
{
	size_t dataSize = 0;
	for(array_t::const_iterator it = m_array.begin(); it != m_array.end(); it++)
	{
		dataSize += it->len + sizeof(it->type) + sizeof(it->len);
	}

	if(dataSize == 0)
	{
		return false;
	}

	*data = new char[dataSize];
	*len = dataSize;
	if(*data == NULL)
	{
		return false;
	}

	size_t pi = 0;
	for(array_t::const_iterator it = m_array.begin(); it != m_array.end(); it++)
	{
		memcpy(*data + pi, (char*)&it->type, sizeof(it->type));	
		pi += sizeof(it->type);
		memcpy(*data + pi, (char*)&it->len, sizeof(it->len));	
		pi += sizeof(it->len);

		switch(it->type)
		{
		case TYPE_CHAR:
		case TYPE_INT32:
		case TYPE_INT64:
		case TYPE_DOUBLE:
		case TYPE_STRING:
		case TYPE_BYTES:
			memcpy(*data + pi, (char*)it->value, it->len);	
			pi += it->len;
			break;
		case TYPE_ARRAY:
		{
			char *arrayData;
			size_t arrayLen;
			AnyArray *pArray = (AnyArray*)it->value;
			pArray->serialize(&arrayData, &arrayLen);
			assert(arrayLen == it->len);
			memcpy(*data + pi, arrayData, it->len);
			pi += it->len;
			delete[] arrayData;
		}
			break;
		case TYPE_MAP:
		{
			char *mapData;
			size_t mapLen;
			AnyMap *pMap = (AnyMap*)it->value;
			pMap->serialize(&mapData, &mapLen);
			assert(mapLen == it->len);
			memcpy(*data + pi, mapData, it->len);
			pi += it->len;
			delete[] mapData;
		}
			break;
		default:
			break;
		}
	}
	return true;
}

//-------------------------------------------------
//class AnyMap

AnyMap::AnyMap()
{
}

AnyMap::AnyMap(const AnyMap &aMap)
{
	map_t::const_iterator it = aMap.m_map.begin();
	for(; it != aMap.m_map.end(); it++)
	{
		AnyItem item = it->second;
		AnyItem newItem = item;
		switch(item.type)
		{
			case TYPE_INT32:
				newItem.value = new int32_t(*(int32_t*)item.value);
				break;
			case TYPE_INT64:
				newItem.value = new int64_t(*(int64_t*)item.value);
				break;
			case TYPE_CHAR:
				newItem.value = new char(*(char*)item.value);
				break;
			case TYPE_DOUBLE:
				newItem.value = new double(*(double*)item.value);
				break;
			case TYPE_STRING:
				newItem.value = new char[item.len + 1];
				memcpy(newItem.value, item.value, item.len + 1);
				break;
			case TYPE_ARRAY:
				newItem.value = new AnyArray(*(AnyArray*)item.value);
				break;
			case TYPE_MAP:
				newItem.value = new AnyMap(*(AnyMap*)item.value);
				break;
			default:
				break;
		}
		m_map[it->first] = newItem;
	}
}

AnyMap::~AnyMap()
{
	map_t::const_iterator it = m_map.begin();
	for(; it != m_map.end(); it++)
	{
		AnyItem item = it->second;
		switch(item.type)
		{
			case TYPE_INT32:
				delete (int32_t*)item.value;
				break;
			case TYPE_INT64:
				delete (int64_t*)item.value;
				break;
			case TYPE_CHAR:
				delete (char*)item.value;
				break;
			case TYPE_DOUBLE:
				delete (double*)item.value;
				break;
			case TYPE_STRING:
				delete[] (char*)item.value;
				break;
			case TYPE_ARRAY:
				delete (AnyArray*)item.value;
				break;
			case TYPE_MAP:
				delete (AnyMap*)item.value;
				break;
			default:
				break;
		}
	}
}

AnyMap *AnyMap::create(const char *data, size_t len)
{
	if(!data || len == 0)
	{
		return NULL;
	}

	size_t p = 0;
	AnyMap *pMap = new AnyMap();
	while(p < len)
	{
		key_t key;
		AnyItem item;
		size_t k = sizeof(key_t);
		if(k + p > len) break;
		memcpy(&key, data + p, k);
		p += k;

		k = sizeof(item.type);
		if(k + p > len) break;
		memcpy(&item.type, data + p, k);
		p += k;

		k = sizeof(item.len);
		if(k + p > len) break;
		memcpy(&item.len, data + p, k);
		p += k;

		k = item.len;
		if(k + p > len) break;
		if(item.type == TYPE_ARRAY)
		{
			AnyArray *pa = AnyArray::create(data + p, item.len);
			if(!pa) break;
			item.value = pa;
		}
		else if(item.type == TYPE_MAP)
		{
			AnyMap *pm = AnyMap::create(data + p, item.len);
			if(!pm) break;
			item.value = pm;
		}
		else
		{
			item.value = new char[item.len];
			memcpy(item.value, data + p, k);
		}
		p += k;
		pMap->m_map[key] = item;
	}
	return pMap;
}

bool AnyMap::serialize(char **data, size_t *len) const
{
	size_t dataSize = 0;
	for(map_t::const_iterator it = m_map.begin(); it != m_map.end(); it++)
	{
		dataSize += sizeof(it->first);
		dataSize += it->second.len;
		dataSize += sizeof(it->second.type);
		dataSize += sizeof(it->second.len);
	}

	if(dataSize == 0)
	{
		return false;
	}

	*data = new char[dataSize];
	*len = dataSize;
	if(*data == NULL)
	{
		return false;
	}

	size_t pi = 0;
	for(map_t::const_iterator it = m_map.begin(); it != m_map.end(); it++)
	{
		memcpy(*data + pi, (char*)&it->first, sizeof(it->first));
		pi += sizeof(it->first);
		memcpy(*data + pi, (char*)&it->second.type, sizeof(it->second.type));	
		pi += sizeof(it->second.type);
		memcpy(*data + pi, (char*)&it->second.len, sizeof(it->second.len));	
		pi += sizeof(it->second.len);

		switch(it->second.type)
		{
		case TYPE_CHAR:
		case TYPE_INT32:
		case TYPE_INT64:
		case TYPE_DOUBLE:
		case TYPE_STRING:
		case TYPE_BYTES:
			memcpy(*data + pi, (char*)it->second.value, it->second.len);	
			pi += it->second.len;
			break;
		case TYPE_ARRAY:
		{
			char *arrayData;
			size_t arrayLen = 0;
			AnyArray *pArray = (AnyArray*)it->second.value;
			if(pArray->serialize(&arrayData, &arrayLen) && arrayLen == it->second.len)
			{
				memcpy(*data + pi, arrayData, it->second.len);
				pi += it->second.len;
				delete[] arrayData;
			}
			else
			{
				if(arrayData)
				{
					delete[] arrayData;
				}
				return false;
			}
		}
			break;
		case TYPE_MAP:
		{
			char *mapData = NULL;
			size_t mapLen = 0;
			AnyMap *pMap = (AnyMap*)it->second.value;
			if(pMap->serialize(&mapData, &mapLen) && mapLen == it->second.len)
			{
				memcpy(*data + pi, mapData, it->second.len);
				pi += it->second.len;
				delete[] mapData;
			}
			else
			{
				if(mapData) 
				{
					delete[] mapData;
				}
				return false;
			}
		}
			break;
		default:
			break;
		}
	}
	return true;
}

void AnyMap::insertInt32(const char *key, int32_t value)
{
	AnyItem item;
	item.type = TYPE_INT32;
	item.len = sizeof(value);
	item.value = new int32_t(value);
	insert(key, item);
}

void AnyMap::insertInt64(const char *key, int64_t value)
{
	AnyItem item;
	item.type = TYPE_INT64;
	item.len = sizeof(value);
	item.value = new int64_t(value);
	insert(key, item);
}

void AnyMap::insertChar(const char *key, char value)
{
	AnyItem item;
	item.type = TYPE_INT64;
	item.len = sizeof(value);
	item.value = new char(value);
	insert(key, item);
}

void AnyMap::insertDouble(const char *key, double value)
{
	AnyItem item;
	item.type = TYPE_INT64;
	item.len = sizeof(value);
	item.value = new double(value);
	insert(key, item);
}

void AnyMap::insertString(const char *key, char *value)
{
	if(!value)
	{
		return;
	}

	size_t len = strlen(value);
	if(len == 0)
	{
		return;
	}

	AnyItem item;
	item.type = TYPE_STRING;
	item.len = len;
	item.value = new char[len + 1];
	memcpy(item.value, value, len + 1);
	insert(key, item);
}

void AnyMap::insertBytes(const char *key, char *value, size_t len)
{
	AnyItem item;
	item.type = TYPE_BYTES;
	item.len = len;
	item.value = new char[len];
	memcpy(item.value, value, len);
	insert(key, item);
}

void AnyMap::insertArray(const char *key, AnyArray *value)
{
	AnyItem item;
	item.type = TYPE_ARRAY;
	item.len = value->byteLength();
	item.value = new AnyArray(*value);
	insert(key, item);
}

void AnyMap::insertMap(const char *key, AnyMap *value)
{
	AnyItem item;
	item.type = TYPE_MAP;
	item.len = value->byteLength();
	item.value = new AnyMap(*value);
	insert(key, item);
}

bool AnyMap::getInt32(const char *key, int32_t *value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_INT32)
	{
		memcpy(value, item->value, 4);	
		return true;
	}
	return false;
}

bool AnyMap::getInt64(const char *key, int64_t *value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_INT64)
	{
		memcpy(value, item->value, 8);	
		return true;
	}
	return false;
}

bool AnyMap::getChar(const char *key, char *value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_CHAR)
	{
		memcpy(value, item->value, sizeof(char));	
		return true;
	}
	return false;
}

bool AnyMap::getDouble(const char *key, double *value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_DOUBLE)
	{
		memcpy(value, item->value, sizeof(double));	
		return true;
	}
	return false;
}

bool AnyMap::getString(const char *key, char **value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_STRING)
	{
		*value = (char*)item->value;
		return true;
	}
	return false;
}

bool AnyMap::getBytes(const char *key, char **value, size_t *len) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_BYTES)
	{
		*value = (char*)item->value;
		*len = item->len;
		return true;
	}
	return false;
}

bool AnyMap::getArray(const char *key, AnyArray **value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_ARRAY)
	{
		*value = (AnyArray*)item->value; 
		return true;
	}
	return false;
}

bool AnyMap::getMap(const char *key, AnyMap **value) const
{
	const AnyItem *item = get(key);
	if(item && item->type == TYPE_MAP)
	{
		*value = (AnyMap*)item->value; 
		return true;
	}
	return false;
}

const AnyItem *AnyMap::get(const char *key) const
{
	int64_t k;
	memcpy(&k, key, sizeof(k));
	map_t::const_iterator it = m_map.find(k);	
	if(it != m_map.end())
	{
		return &it->second;
	}
	return NULL;
}

void AnyMap::insert(const char *key, const AnyItem &item)
{
	key_t k;
	memcpy(&k, key, sizeof(k));
	map_t::iterator it = m_map.find(k);
	if(it != m_map.end())
	{
		switch(it->second.type)
		{
		case TYPE_CHAR:
		case TYPE_INT32:
		case TYPE_INT64:
		case TYPE_DOUBLE:
		case TYPE_STRING:
		case TYPE_BYTES:
			delete[] (char*)it->second.value;
			break;
		case TYPE_ARRAY:
			delete (AnyArray*)it->second.value;
			break;
		case TYPE_MAP:
			delete (AnyMap*)it->second.value;
			break;
		default:
			break;
		}
	}
	m_map[k] = item;
}

bool AnyMap::contain(const char *key) const
{
	int64_t k;
	memcpy(&k, key, sizeof(k));
	return m_map.find(k) != m_map.end();
}

AnyType AnyMap::type(const char *key) const
{
	int64_t k;
	memcpy(&k, key, sizeof(k));
	map_t::const_iterator it = m_map.find(k);
	if(it != m_map.end())
	{
		return it->second.type;
	}
	return TYPE_INVALID;
}

size_t AnyMap::byteLength() const
{
	size_t len = 0;
	map_t::const_iterator it = m_map.begin();
	while(it != m_map.end())
	{
		len += sizeof(it->first);
		len += sizeof(it->second.type);
		len += sizeof(it->second.len);
		len += it->second.len;
		it++;
	}
	return len;
}


}

