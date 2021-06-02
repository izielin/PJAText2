#ifndef PJATEXT2_INVOKE_FUNCTIONS_H
#define PJATEXT2_INVOKE_FUNCTIONS_H

#include <iostream>
#include <vector>
#include "stream_helper.h"
#include "../wrappers/arguments_wrapper.h"

namespace invoke {

    void invoke_functions(wrappers::arguments_wrapper &arguments_vector, stream_helper &output_stream);


}


#endif
