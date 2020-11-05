#include <iostream>
#include <pthread.h>

int Matrix[2][50] = {0};
int Occupied=0;
int Full=100;
int turn= 0;

void CriticalRegion(int id){
    std::cout<<"Agency "<<id<<" Entered Critical Region"<<std::endl;
    int check,row,column;
    do{
    check = rand()%100;
    column = check%50;
    row = check/50;
    }while(Matrix[row][column]!=0);

    Matrix[row][column]= id;
    Occupied++;
    std::cout<<"Seat Number "<<check<<" is reserved by Agency "<<id<<" OCCUPIED"<<Occupied<<"OCCUPIED "<<std::endl;

}




void* thread_Agency1(void * id){
    while(true){
        while(turn!=0){;}
        if(Occupied==Full){
            turn=1;
            break;}
        CriticalRegion(*((int*) id));
        std::cout<<"Agency 1 Exit Critical Region"<<std::endl<<std::endl;
        turn=1;
        //NonCriticalRegion();
    }
}

void* thread_Agency2(void* id){
    while(true){
        while(turn!=1){;}
        if(Occupied==Full){
            turn=0;
            break;}
        CriticalRegion(*((int*) id));
        std::cout<<"Agency 2 Exit Critical Region"<<std::endl<<std::endl;
        turn=0;
        //NonCriticalRegion();
    }
}

void PrintMatrix(){
        for(int i=0;i<2;i++){
        for(int j=0;j<50;j++){
        std::cout<<Matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
int main(){
    srand(time(NULL));
    PrintMatrix();
    pthread_t Agency_1,Agency_2;
    int id_1 =1, id_2=2;
    pthread_create(&Agency_1,   NULL,   thread_Agency1, (void*) &id_1);
    pthread_create(&Agency_2,   NULL,   thread_Agency2, (void*) &id_2);

    
   

    while(true){
        if(Occupied==Full){break;}
    }
    pthread_join(Agency_1,NULL);
    pthread_join(Agency_2,NULL);
    std::cout<<"No Seats Left\n\nPlane is Full:\n\n";
    PrintMatrix();

    return 0;
}