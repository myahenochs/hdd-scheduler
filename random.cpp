#include <iostream>
#include <time.h>

int main(int argc, char *argv[]){
    int low=0, high=0, count=0;
    if(argc > 1){
        srand(time(NULL));
        count = atoi(argv[1]);
        if (argc == 4){
            low = atoi(argv[2]);
            high = atoi(argv[3]);
            for(int i = 0; i < count; i++){
                std::cout << rand()%high + low;
                if(i < count-1){
                    std::cout << std::endl;
                }
            }
        }
        else{
            for(int i = 0; i < count; i++){
                std::cout << rand();
                if(i < count-1){
                    std::cout << std::endl;
                }
            }
        }
    }
}