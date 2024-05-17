#include "eliza.cpp"

class eliza_test {

private:
        std::string hello_message;
        elizascript::script eliza_script;
        elizalogic::eliza eliza;

public:
        eliza_test();
        ~eliza_test() = default;

        std::string answer(std::string user_input);
};

eliza_test::eliza_test()
        :eliza_script([] {
                elizascript::script s;
                elizascript::read(elizascript::CACM_1966_01_DOCTOR_script, s);
                return s;
        }()),
        hello_message(join(eliza_script.hello_message)),
        eliza(eliza_script.rules, eliza_script.mem_rule)
{
}

std::string eliza_test::answer(std::string user_input)
{
        return eliza.response(user_input);
}

int main()
{
        elizascript::script eliza_script([] {
                elizascript::script s;
                elizascript::read(elizascript::CACM_1966_01_DOCTOR_script, s);
                return s;
        }());
        std::cout << eliza_script.hello_message;
}