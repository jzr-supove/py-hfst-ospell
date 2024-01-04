#include "ZHfstOspeller.h"
#include <vector>

class Speller {
private:
	hfst_ospell::Transducer *lex;
	hfst_ospell::Transducer *err;
	hfst_ospell::ZHfstOspeller speller;
    
public:
    Speller(std::string lex_path, std::string error_path);
    void do_suggest(const std::string str);
    void do_spell(const std::string str);
    bool spell(const std::string str);
    std::vector<std::string> suggest(const std::string str);
	void hello();
	std::vector<std::pair<std::string, float>> suggest_weighted(const std::string str);
    std::string lookup(std::string word);
    void set_beam(float beam);
    void set_weight_limit(float limit);
    void set_queue_limit(unsigned long limit);
};

hfst_ospell::Transducer *createTransducer(std::string lex_path);

std::vector<std::string> lookup(hfst_ospell::Transducer *tr, std::string word);

void lookup2(hfst_ospell::Transducer* tr, std::string word, std::string *OUTPUT);
