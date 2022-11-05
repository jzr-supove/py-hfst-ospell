import os
import py_hfst_ospell as ospell


dirname = os.path.dirname(__file__)
lexicon_model = os.path.join(dirname, "iuzbek+.hfst")
error_model = os.path.join(dirname, "error.model.hfst")


speller = ospell.Speller(lexicon_model, error_model)


def test_spell():
    assert speller.spell("nima") == True
    assert speller.spell("nma") == False


def test_transducer():
    tr = ospell.createTransducer(lexicon_model)

    words = {
        "bola": "bola<NN>",
        "ketmoq": "ket<VB><moq>",
        "chmo": "",
        "kelishmoq": "kel<VB><Ish><moq>", 
        "borish": "bor<VB><Ish>", 
        "prak": "", 
        "jala": "jala<NN>"
    }

    for w in words:
        assert speller.lookup(w) == words[w]
        assert ospell.lookup(tr, w) == words[w]


def test_suggest():
    assert speller.suggest("nma")[0] == "nima"
    assert speller.suggest("qalesan")[0] == "qalaysan"