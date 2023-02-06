%module py_hfst_ospell

%{
#include "py-hfst-ospell.h"
%}

%include "stdint.i"
%include "std_string.i" 
%include "std_vector.i"
%include "typemaps.i"

%template(ResVector) std::vector<std::string>;


%include "py-hfst-ospell.h"
