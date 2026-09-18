
#include <iostream>


void imprimir(void){
    using namespace std;
    cout<< "come up and C++ me some time";
    cout<< endl;
    cout<< "you won't regret it!" << endl;

}

int suma(int x,int y){

    int z;
    z=x+y;

    return z; 
};

int suma_n(int n){

    int suma;
    for(int i=0;i>=n;i++){
        suma+=i;
    }
    return suma; 
    int azul; 
    azul+=5;
    
};

int triangulo(int diag){
    using namespace std;
    
    for(int i=0;i<=diag;i++){
        for(int j=0;j<=diag;j++){

            if(i<=j){
                
                cout<<' ';
            }
            else{
                cout<<'*';
            }
            
        }
        cout<<endl;
    }

    
    return 0;
}

int figuras()
{
    using namespace std;
    char figura;
    int diagonal;

    cout<<"Que figura quiere elegir";
    cin>>figura;
    cout<<"Escriba la medida de la diagonal";
    cin>>diagonal;
    
    

    if(figura=='t'){
        
        triangulo(diagonal);
    }

    

    return 0;
}


double cel_to_far(double cel){

    return (cel*1.8)+32;
}

int main(){
    using namespace std;
    cout<<"Escribe la cantidad de grados centigrados:";
    double celsius;
    cin>>celsius;
    double far=cel_to_far(celsius);

    cout<<"far= "<<far<< endl;

    return 0; 

} 

