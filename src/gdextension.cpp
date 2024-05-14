#include "gdextension.h"
#include <godot_cpp/core/class_db.hpp>

ELIZA::ELIZA() 
{
	script = godot::String(elizascript::CACM_1966_01_DOCTOR_script);
	elizascript::read(elizascript::CACM_1966_01_DOCTOR_script, eliza_script);
	hello_message = godot::String(join(eliza_script.hello_message).c_str());
	elizalogic::eliza eliza(eliza_script.rules, eliza_script.mem_rule);
}

ELIZA::~ELIZA() {}

void ELIZA::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_script", "p_script"), &ELIZA::set_script);
	ClassDB::bind_method(D_METHOD("get_script"), &ELIZA::get_script);
	ClassDB::add_property("ELIZA", PropertyInfo(Variant::STRING, "script"), "set_script", "get_script");

	ClassDB::bind_method(D_METHOD("set_hello_message", "p_hello_message"), &ELIZA::set_hello_message);
	ClassDB::bind_method(D_METHOD("get_hello_message"), &ELIZA::get_hello_message);
	ClassDB::add_property("ELIZA", PropertyInfo(Variant::STRING, "hello_message"), "set_hello_message", "get_hello_message");

	ClassDB::bind_method(D_METHOD("answer"), &ELIZA::answer);
}

void ELIZA::set_script(godot::String s)
{
	std::stringstream ss(s.ascii().get_data());
	elizascript::read<std::stringstream>(ss, eliza_script);
}

godot::String ELIZA::get_script()
{
	return script;
}

void ELIZA::set_hello_message(godot::String s)
{
	hello_message = s;
}

godot::String ELIZA::get_hello_message()
{
	return hello_message;
}

godot::String ELIZA::answer(godot::String userinput)
{
	std::string s{ userinput.ascii().get_data() };
	const std::string response{ s };
	return godot::String(response.c_str());
}