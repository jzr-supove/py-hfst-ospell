#include <iostream>
#include "py-hfst-ospell.h"


Speller::Speller(std::string lex_path, std::string error_path) {
	FILE *lex_source = fopen(lex_path.c_str(), "r");
	FILE *error_source = fopen(error_path.c_str(), "r");

	lex = new hfst_ospell::Transducer(lex_source);
	err = new hfst_ospell::Transducer(error_source);

	hfst_ospell::Speller *s = new hfst_ospell::Speller(err, lex);

	speller.inject_speller(s);
}

void Speller::do_suggest(const std::string str) {
	hfst_ospell::CorrectionQueue corrections = speller.suggest(str);
	bool analyse = true;

	if (corrections.size() > 0) {
		printf("Corrections for \"%s\":\n", str.c_str());

		while (corrections.size() > 0) {
			const std::string& corr = corrections.top().first;

			if (analyse) {
				hfst_ospell::AnalysisQueue anals = speller.analyse(corr, true);
				bool all_discarded = true;

				while (anals.size() > 0) {
					if (anals.top().first.find("Use/SpellNoSugg") != std::string::npos) {
						printf(
							"%s    %f    %s    [DISCARDED BY ANALYSES]\n",
							corr.c_str(), corrections.top().second, anals.top().first.c_str()
						);
					}
					else {
						all_discarded = false;
						printf(
							"%s    %f    %s\n",
							corr.c_str(), corrections.top().second, anals.top().first.c_str()
						);
					}
					anals.pop();
				}
				if (all_discarded) {
					printf("All corrections were invalidated by analysis! No score!\n");
				}
			}
			else {
				printf("%s    %f\n", corr.c_str(), corrections.top().second);
			}
			corrections.pop();
		}
		printf("\n");
	}
	else {
		printf("Unable to correct \"%s\"!\n\n", str.c_str());
	}
}

void Speller::do_spell(const std::string str) {
	bool analyse = true;
	bool suggest_reals = true;
	bool suggest = true;

	if (speller.spell(str)) {
		printf("\"%s\" is in the lexicon...\n", str.c_str());

		if (analyse) {
			printf("analysing:\n");
			hfst_ospell::AnalysisQueue anals = speller.analyse(str, false);
			bool all_no_spell = true;
			while (anals.size() > 0) {
				if (anals.top().first.find("Use/-Spell") != std::string::npos) {
					printf("%s   %f [DISCARDED AS -Spell]\n", anals.top().first.c_str(), anals.top().second);
				}
				else {
					all_no_spell = false;
					printf("%s   %f\n", anals.top().first.c_str(), anals.top().second);
				}
				anals.pop();
			}
			if (all_no_spell) {
				printf("All spellings were invalidated by analysis! .:. Not in lexicon!\n");
			}
		}
		if (suggest_reals) {
			printf("\"%s\" (but correcting anyways)\n", str.c_str());
			do_suggest(str);
		}
	}
	else {
		printf("\"%s\" is NOT in the lexicon:\n", str.c_str());
		if (suggest) {
			do_suggest(str);
		}
	}
}

bool Speller::spell(const std::string str) {
	return speller.spell(str);
}

std::vector<std::string> Speller::suggest(const std::string str) {
	hfst_ospell::CorrectionQueue corrections = speller.suggest(str);
	std::vector<std::string> results;

	while (corrections.size() > 0) {
		const std::string& corr = corrections.top().first;
		results.push_back(corr.c_str());
		corrections.pop();
	}
	return results;
}

std::string Speller::lookup(std::string word){
	hfst_ospell::AnalysisQueue aq = lex->lookup(&word[0]);
	if (aq.size() > 0){
		return aq.top().first;
	}
	return "";
}

void Speller::set_beam(float beam){
	speller.set_beam(beam);
}

void Speller::set_weight_limit(float limit){
	speller.set_weight_limit(limit);
}

void Speller::set_queue_limit(unsigned long limit){
	speller.set_queue_limit(limit);
}

hfst_ospell::Transducer* createTransducer(std::string lex_path) {
	FILE *lex_source = fopen(lex_path.c_str(), "r");
	hfst_ospell::Transducer *lex = new hfst_ospell::Transducer(lex_source);
	return lex;
}

std::string lookup(hfst_ospell::Transducer* tr, std::string word) {
	hfst_ospell::AnalysisQueue aq = tr->lookup(&word[0]);
	if (aq.size() > 0){
		return aq.top().first;
	}
	return "";
}

void lookup2(hfst_ospell::Transducer* tr, std::string word, std::string *OUTPUT) {
	*OUTPUT = tr->lookup(&word[0]).top().first;
}
