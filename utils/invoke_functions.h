//
// Created by mmich on 31.05.2021.
//

#ifndef PJATEXT2_INVOKE_FUNCTIONS_H
#define PJATEXT2_INVOKE_FUNCTIONS_H

#include <iostream>
#include <vector>
#include "stream_helper.h"
#include "../custom_containers/argument_container.h"

namespace invoke {

    void invoke_functions(containers::argument_container &arguments_vector, stream_helper &output_stream);


}


#endif //PJATEXT2_INVOKE_FUNCTIONS_H
