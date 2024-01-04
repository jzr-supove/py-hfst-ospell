%module py_hfst_ospell

%{
#include "py-hfst-ospell.h"
%}

%include "stdint.i"
%include "std_string.i" 
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

%template(ResVector) std::vector<std::string>;
%template(ResWeightedPair) std::pair<std::string, float>;
%template(ResWeightedVector) std::vector<std::pair<std::string, float>>;


%include "py-hfst-ospell.h"
