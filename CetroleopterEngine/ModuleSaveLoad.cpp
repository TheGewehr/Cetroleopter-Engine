#include "ModuleSaveLoad.h"



ModuleSaveLoad::ModuleSaveLoad(bool start_enabled) : Module(start_enabled)
{
	
}

// Destructor
ModuleSaveLoad::~ModuleSaveLoad()
{
}

bool ModuleSaveLoad::Init()
{
	LOG("Initializing ModuleSaveLoad");

	//SaveInJson();
	LoadFromJson();

	return true;
}

update_status ModuleSaveLoad::PostUpdate(float dt)
{
    

	return UPDATE_CONTINUE;
}

bool ModuleSaveLoad::CleanUp()
{
	LOG("Cleaning ModuleSaveLoad");

	return true;
}

bool ModuleSaveLoad::SaveInJson()
{
	// loading a file
	JSON_Value* file = json_parse_file("Test.json");

	LOG("Saving testo");

	// saving content
	const char* buf = " Test buffer ";
	const int integer = 0;
	const float floato = 1.8765;

	json_object_dotset_string(json_object(file), "TestClass.Category01.TestString", buf);
	
	json_object_dotset_number(json_object(file), "TestClass.Category02.TestFloatOrDouble", (double)floato);

	json_object_dotset_number(json_object(file), "TestClass.Category03TestInteger", (double)integer);

	// Aplying save to the .json file
	json_serialize_to_file(file, "Test.json");

	// free the file ptr
	json_value_free(file);

	LOG("Saving testo");

	return true;
}

bool ModuleSaveLoad::LoadFromJson()
{
	// loading a file
	JSON_Value* file = json_parse_file("Test.json");

	LOG("loading testo");

	// Loading content
	const char* buf = json_object_dotget_string(json_object(file), "TestClass.Category01.TestString");
	const int integer = (int) json_object_dotget_number(json_object(file), "TestClass.Category03TestInteger");
	const float floato = (float)json_object_dotget_number(json_object(file), "TestClass.Category02.TestFloatOrDouble");

	// free the file ptr
	json_value_free(file);

	LOG("loading testo");

	return true;
}