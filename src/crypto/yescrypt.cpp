#include "yescrypt.h"
#include <yescrypt/yescrypt.h>

uint256 Yescrypt(const std::vector<unsigned char>& input)
{
    // Initialize Yescrypt parameters
    yescrypt_params_t params;
    yescrypt_init_shared(&params);
    params.N = 2048;
    params.r = 8;
    params.p = 1;
    params.flags = YESCRYPT_RW;
    
    uint256 hash;
    yescrypt(input.data(), input.size(), params, hash.begin(), hash.size());
    
    yescrypt_free_shared(&params);
    
    return hash;
}
