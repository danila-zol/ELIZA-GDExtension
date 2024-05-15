#ifndef ELIZA_INCLUDE
   #include "eliza.cpp"
   #define ELIZA_INCLUDE
#endif

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

class ELIZA : public RefCounted {
	GDCLASS(ELIZA, RefCounted)

private:
	godot::String hello_message;
	elizascript::script eliza_script;
	godot::String script;
	elizalogic::eliza eliza;

protected:
	static void _bind_methods();

public:
	ELIZA();
	~ELIZA();

	godot::String answer(godot::String input);

	void set_hello_message(godot::String s);
	godot::String get_hello_message();

	void set_script(godot::String s);
	godot::String get_script();
};