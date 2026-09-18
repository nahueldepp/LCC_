/* 6. Write a program that asks the user to enter an hour value and a minute value. The
main() function should then pass these two values to a type void function that displays
the two values in the format shown in the following sample run:
Enter the number of hours: 9
Enter the number of minutes: 28
Time: 9:28 */
#include <iostream>

void time(int hora ,int min);
int main(){
    std::cout<<"Enter the number of hours: ";
    int horas;
    std::cin>>horas;

    std::cout<<"Enter the numbers of minutes: ";
    int minutos;
    std::cin>>minutos;

    time(horas,minutos);

    return 0;

}

//time: int int->void
//dado una hora y minuto imprime en pantalla hora:min
void time(int hora, int min){

    if(min<60){
        std::cout<<hora<<":"<<min<<std::endl;


    }
    //min>=60
    else{
        min=min/60;
        hora+=(min%60);

        std::cout<<hora<<":"<<min<<std::endl;

    }
}