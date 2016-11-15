#include "jsonconfig.h"
#include "../../json.h"
#include <stdio.h>
#include <string.h>

const JsonItem JSON_DEFAULT_ITEM;

int JsonItem::GetInt() const
{
	if(0 == m_obj || json_type_int != json_object_get_type(m_obj)) return 0;
	return json_object_get_int(m_obj);
}

double JsonItem::GetDouble() const
{
	if(0 == m_obj || json_type_int != json_object_get_type(m_obj) && json_type_double != json_object_get_type(m_obj)) return 0;
	return json_object_get_double(m_obj);
}

bool JsonItem::GetBool() const
{
	if(0 == m_obj || json_type_boolean != json_object_get_type(m_obj)) return false;
	return 0 != json_object_get_boolean(m_obj);
}

const char* JsonItem::GetString() const
{
	if(0 == m_obj || json_object_get_type(m_obj) != json_type_string) return "";
	const char* str = json_object_get_string(m_obj);
	return str == 0 ? "" : str;
}

int JsonItem::GetArrayLength() const
{
	if(0 == m_obj || json_type_array != json_object_get_type(m_obj)) return 0;
	return json_object_array_length(m_obj);
}

JsonItem JsonItem::operator [](const char *key) const
{
	if(0 == m_obj || json_type_object != json_object_get_type(m_obj))
	{
		return JSON_DEFAULT_ITEM;
	}
	json_object* get_obj = json_object_object_get(m_obj,key);
	if(0 == get_obj)
	{
		return JSON_DEFAULT_ITEM;
	}
	return JsonItem(get_obj);
}

JsonItem JsonItem::operator [](const int index) const
{
	if(index < 0 || 0 == m_obj || json_type_array != json_object_get_type(m_obj))
	{
		return JSON_DEFAULT_ITEM;
	}
	json_object* get_object = json_object_array_get_idx(m_obj,index);
	if(0 == get_object)
	{
		return JSON_DEFAULT_ITEM;
	}
	return JsonItem(get_object);
}

JsonConfig::~JsonConfig()
{
	if(0 != m_root)
	{
		json_object_put(m_root);
	}
}

bool JsonConfig::Init(const char* path)
{
	json_object* init_obj = json_object_from_file(path);
	if(is_error(init_obj))
	{
		return false;
	}
	if(0 != init_obj)
	{
		json_object_put(m_root);
	}
	m_root = init_obj;
	return true;
}

JsonItem JsonConfig::operator [](const char *key) const
{
	if(0 == m_root || json_type_object != json_object_get_type(m_root))
	{
		return JSON_DEFAULT_ITEM;
	}
	json_object *get_object = json_object_object_get(m_root,key);
	if(0 == get_object)
	{
		return JSON_DEFAULT_ITEM;
	}
	return JsonItem(get_object);
}




