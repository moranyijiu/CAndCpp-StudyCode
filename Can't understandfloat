float fast_sqrt(float x)
{
    uint32_t x_bits=0;
    x_bits=*((uint32_t*)&x);
    x_bits=(x_bits>>1)+532369198;
    return *((float*)&x_bits);
}
