#ifndef _QY_ANY_H
#define _QY_ANY_H

#include <cstring>
#include <map>
#include <vector>
#include <stdint.h>

namespace qy
{

typedef enum 
{
	TYPE_CHAR = 'rahc',
	TYPE_INT32 = '4tni',
	TYPE_INT64 = '8tni',
	TYPE_DOUBLE = 'elbd',
	TYPE_STRING = 'grts',
	TYPE_BYTES = 'bolb',
	TYPE_ARRAY = 'yrra',
	TYPE_MAP = 'pam',
	TYPE_INVALID = 'avni'
}AnyType;

typedef struct
{
	AnyType type;
	size_t len;
	void *value;
}AnyItem;

class AnyArray;
class AnyMap;

class AnyArray
{
	typedef std::vector<AnyItem> array_t;
public:
	static AnyArray *create(const char *data, size_t len);
	bool serialize(char **data, size_t *len) const;

	AnyArray();
	AnyArray(const AnyArray &array);
	~AnyArray();

	void addChar(char value);
	void addInt32(int32_t value);
	void addInt64(int64_t value);
	void addDouble(double value);
	void addString(const char *value);
	void addBytes(const char *value, size_t len);
	void addArray(const AnyArray *value);
	void addMap(const AnyMap *value);

	bool getChar(size_t index, char *value) const;
	bool getInt32(size_t index, int32_t *value) const;
	bool getInt64(size_t index, int64_t *value) const;
	bool getDouble(size_t index, double *value) const;
	bool getString(size_t index, char **value) const;
	bool getBytes(size_t index, char **value, size_t *len) const;
	bool getArray(size_t index, AnyArray **value) const;
	bool getMap(size_t index, AnyMap **value) const;

	AnyType type(size_t index) const;

	size_t size() const { return m_array.size(); }
	size_t byteLength() const;

private:
	array_t m_array;
};

class AnyMap
{
	typedef int64_t key_t;
	typedef std::map<key_t, AnyItem> map_t;
public:
	static AnyMap *create(const char *data, size_t len);
	bool serialize(char **data, size_t *len) const;

	AnyMap();
	AnyMap(const AnyMap &aMap);
	~AnyMap();

	//all value will be copied then inserted.
	void insertChar(const char *key, char value);
	void insertInt32(const char *key, int32_t value);
	void insertInt64(const char *key, int64_t value);
	void insertDouble(const char *key, double value);
	void insertString(const char *key, char *value);
	void insertBytes(const char *key, char *value, size_t len);
	void insertArray(const char *key, AnyArray *value);
	void insertMap(const char *key, AnyMap *value);

	//return results are not cloned. they will be destroyed when the map destroyed
	bool getChar(const char *key, char *value) const;
	bool getInt32(const char *key, int32_t *value) const;
	bool getInt64(const char *key, int64_t *value) const;
	bool getDouble(const char *key, double *value) const;
	bool getString(const char *key, char **value) const;
	bool getBytes(const char *key, char **value, size_t *len) const;
	bool getArray(const char *key, AnyArray **value) const;
	bool getMap(const char *key, AnyMap **value) const;

	bool contain(const char *key) const;
	AnyType type(const char *key) const;

	size_t size() const { return m_map.size(); }
	size_t byteLength() const;

private:
	const AnyItem *get(const char *key) const;
	void insert(const char *key, const AnyItem &item);

private:
	map_t m_map;
};

}

#endif
