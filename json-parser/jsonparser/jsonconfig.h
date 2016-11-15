#ifndef JSON_CONFIG_H
#define JSON_CONFIG_H

struct json_object;

class JsonItem
{
public:
	JsonItem():m_obj(0){}
	JsonItem(json_object *obj):m_obj(obj){}
	virtual ~JsonItem(){}

	int GetArrayLength() const;
	int GetInt() const;
	double GetDouble() const;
	bool GetBool() const;
	const char* GetString() const;

	JsonItem operator[](int index) const;
	JsonItem operator[](const char *key) const;
	bool operator!=(const JsonItem& r) const {return m_obj != r.m_obj;}

private:
	json_object	*m_obj;
};

class JsonConfig
{
public:
	JsonConfig():m_root(0){}
	virtual ~JsonConfig();

	bool Init(const char *path);
	JsonItem operator[](const char* key) const;

private:
	json_object * m_root;
};


#endif