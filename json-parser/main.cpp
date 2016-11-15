#include<iostream>
using namespace std;
#include "../json.h"
#include "jsonparser/jsonparser.h"
#include "jsonparser/jsonconfig.h"

void test_jsonc()
{
	struct json_object* info_object = NULL;
	info_object = json_object_new_object();
	if(NULL == info_object)
	{
		cout<<"new json object failed"<<endl;
		return;
	}
	struct json_object* para_object = NULL;
	para_object = json_object_new_object();
	if(NULL == para_object)
	{
		json_object_put(info_object);// free
		printf("new json object failed");
		return;
	}

	struct json_object* array_object = NULL;
	array_object = json_object_new_array();
	if(NULL == array_object)
	{
		json_object_put(info_object);
		json_object_put(para_object);
		printf("new json object failed");
		return;
	}
	json_object_array_add(array_object,json_object_new_int(256));
	json_object_array_add(array_object,json_object_new_int(231));
	json_object_array_add(array_object,json_object_new_int(123));

//	JsonParser* j = new JsonParser();
//	j->Init(json_object_to_json_string(array_object));
// 	json_object* tmp = j->GetKeyHelper(0);
// 	int a = json_object_get_int(tmp);
	JsonParser parser;
	if(!parser.Init(JsonParser::EMPTY_OBJ))
	{
		return ;
	}
	if(!parser.ObjSetObjAndDown("json"))
	{
		return;
	}
	parser.ObjSetInt("hello",1);
	parser.ObjSetInt("world",2);
	parser.ObjSetBoolean("yes",false);

	if(!parser.ObjSetArrayAndDown("array"))
	{
		return;
	}
	for(int i = 0; i < 10; i++)
	{
		parser.ArraySetInt(i,i);
	}
	parser.Up();
	parser.ObjSetInt("world1",2);
	parser.Up();
	const char* str = parser.ToJsonString();
	printf("json : %s\n",parser.ToJsonString());

	 printf("%s\n", json_object_to_json_string(array_object));  
}

void test_jsonconfig()
{
	JsonConfig config;
	config.Init("wingjsonconfig.json");
	JsonItem item = config["open_level"];
	int openlevel = item.GetInt();
	printf("open level is %d\n",openlevel);
}

int main()
{
	test_jsonc();
	test_jsonconfig();

	cout<<"helloworld"<<endl;
	system("pause");
	return 0;
}