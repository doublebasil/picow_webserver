int main( void )
{
    volatile int a = 12;
    for( ;; ++a );
}