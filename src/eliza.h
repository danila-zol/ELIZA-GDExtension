#pragma once
#include <string>
#include <deque>

using stringlist = std::deque<std::string>;

template<typename T>
auto pop_front(T &container);
std::string to_upper(std::string s);
stringlist split(const std::string &s);
std::string join(const stringlist &words);

namespace elizalogic {
        // map tag word -> associated words
        // e.g. "BELIEF" -> ("BELIEVE" "FEEL" "THINK" "WISH")
        using tagmap = std::map<std::string, stringlist>;
        using vecstr = std::vector<std::string>;


        constexpr unsigned char hollerith_undefined = 0xFFu; // (must be > 63)

        // This table maps ordinary character code units to their Hollerith
        // encoding, or hollerith_undefined if that character does not exist
        // in the Hollerith character set.
        const std::array<unsigned char, 256> hollerith_encoding{ [] {

                /*  
                   "The 7090 BCD character codes are given in the accompanying table.
                    Six bits are used for each character. [...] The code is generally
                    termed binary-coded-decimal or BCD. For compactness, the codes are
                    generally expressed as 2-digit octal numbers, as in the table. The
                    term Hollerith is used synonomously with BCD." [1]

                    The following array is derived from the above mentioned table, with
                    one exception: BCD code 14 (octal) is a single quote (prime), not a
                    double quote. See [2].
                 */
                static constexpr unsigned char bcd[64] = {
                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0, '=', '\'', 0, 0, 0,
                    '+', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 0, '.', ')',  0, 0, 0,
                    '-', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 0, '$', '*',  0, 0, 0,
                    ' ', '/', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0, ',', '(',  0, 0, 0
                };

                static_assert(std::numeric_limits<unsigned char>::max() == 255);
                std::array<unsigned char, 256> to_bcd;
                to_bcd.fill(hollerith_undefined);
                for (unsigned char c = 0; c < 64; ++c)
                    if (bcd[c])
                        to_bcd[bcd[c]] = c;
                return to_bcd;
            }() };

        bool hollerith_defined(char c);
        std::u32string utf8_to_utf32(const std::string &utf8_string);
        std::string filter_bcd(const std::string &utf8_string);
        int to_int(const std::string &s);
        const std::string tag_six_char_matching_behavior{ "USE_SIX_CHAR_MATCHING_BEHAVIOR" };
        bool inlist(const std::string &word, std::string wordlist, const tagmap &tags);
        bool xmatch(                // return true iff words matched pattern
                const tagmap &tags,
                const vecstr pat_array,
                const vecstr word_array,
                const int p_begin,  // index into pat_array where match pattern begins
                const int p_end,    // index into pat_array just after match pattern ends
                const int w_begin,  // index into word_array where pattern must begin matching
                const int fixed_len,// total number of words required to match non-0-wildcard part
                int &w_end,         // out: index into word_array just after pattern matching ended
                vecstr &result
        );
        bool match(const tagmap &tags, const stringlist &pattern,
                const stringlist &words, stringlist &matching_components);
        stringlist reassemble(const stringlist &reassembly_rule, const stringlist &components);
        uint_least32_t hash(uint_least64_t d, int n);
        uint_least64_t last_chunk_as_bcd(std::string s);

        /*  The ELIZA script contains the opening_remarks followed by rules.
            (The formal syntax is given in the elizascript namespace below.)
            There are two types of rule: keyword_rule and memory_rule. They
            are represented by the following classes. */

        // interface and data shared by both rules
        class rule_base {
        public:
                rule_base() = default;

                rule_base(const std::string &keyword, const std::string &word_substitution, int precedence)
                        : keyword_(keyword), word_substitution_(word_substitution), precedence_(precedence)
                {}

                virtual ~rule_base() = default;


                void set_keyword(const std::string &keyword) { keyword_ = keyword; }

                void add_transformation_rule(const stringlist &decomposition,
                        const std::vector<stringlist> &reassembly_rules)
                {
                        trans_.emplace_back(decomposition, reassembly_rules);
                }

                int precedence() const { return precedence_; }
                std::string keyword() const { return keyword_; }


                enum class action {
                        inapplicable,   // no transformation could be performed
                        complete,       // transformation of input is complete
                        newkey,         // request caller try next keyword in keystack
                        linkkey         // request caller try returned keyword
                };

                // replace 'word' with substitute specified by script rule, if any
                virtual action apply_word_substitution(std::string &word)
                {
                        if (word_substitution_.empty() || word != keyword_)
                                return action::inapplicable;
                        word = word_substitution_;
                        return action::complete;
                }

                // replace 'word' with substitute specified by script rule, if any
                virtual std::string word_substitute(const std::string &word) const
                {
                        if (word_substitution_.empty() || word != keyword_)
                                return word;
                        return word_substitution_;
                }

                // return true iff this rule has whole-sentence transformation rules associated with it
                virtual bool has_transformation() const { return false; }

                // use this rule's decomposition/reassembly rules to transform given 'words'
                virtual action apply_transformation(stringlist & /*words*/,
                        const tagmap & /*tags*/, std::string & /*link_keyword*/)
                {
                        return action::inapplicable;
                }

                virtual stringlist dlist_tags() const { return stringlist(); }

                virtual std::string to_string() const = 0;

                virtual std::string trace() const { return std::string(); }

        protected:
                std::string keyword_;           // the word that triggers this rule
                std::string word_substitution_; // the word that is to replace the keyword, if any
                int precedence_{ 0 };           // the highest priority rule is selected first

                struct transform {              // decomposition and associated reassembly rules
                        stringlist decomposition;
                        std::vector<stringlist> reassembly_rules;
                        unsigned next_reassembly_rule{ 0 };
                        transform() = default;
                        transform(const stringlist &decomposition,
                                const std::vector<stringlist> &reassembly_rules)
                                : decomposition(decomposition), reassembly_rules(reassembly_rules)
                        {}
                };
                std::vector<transform> trans_;  // transformations associated with this rule
        };

}
