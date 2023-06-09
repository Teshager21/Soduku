#include<iostream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<string>
int generateNumberofFilledCells();
void generateFilledPositions(int (&filledPositions)[],const int filledCells);

void populateInitialCells(int (&tableArray)[3][3][3][3],const int filledCells,int filledPositions[]);
void renderTables(int tableArray[3][3][3][3],int filledPositions[],const int filledCells);
bool isItRepeated(std::string scope,int scopeSpecifier,double value,int (&tableArray)[3][3][3][3]);
void receiveInput(int (&tableArray)[3][3][3][3],int position,int value);
bool checkSelectedPosition(int selectedPosition, int filledPositions[],int filledCells);
bool isgameWon(int tableArray[3][3][3][3]);

int main(){
int tableArray[3][3][3][3];
int selectedPos=0,selectedPosition=0,selectedValue=0;

//intialize the array
for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0; l<3;l++){
                       tableArray[i][j][k][l]=0;
                        }
                    }
                   
                } 
            }   
//decide the number of items to be filled 
const int filledCells=generateNumberofFilledCells();
int filledPositions[filledCells];
std::cout<<filledCells<<std::endl;
generateFilledPositions(filledPositions,filledCells);
populateInitialCells(tableArray,filledCells,filledPositions);
renderTables(tableArray,filledPositions,filledCells);

//Prompt users for input
do{ 
    std::cout<<"Press e to exit"<<std::endl;
    std::cout<<"Choose the cell to change: ";
    std::cin>>selectedPos;
    selectedPosition= static_cast<int>(selectedPos);
    std::cout<<"Choose the value you would to insert: ";
    std::cin>>selectedValue;
    if(checkSelectedPosition(selectedPosition,filledPositions,filledCells)){
       receiveInput(tableArray,selectedPosition,selectedValue);
    }else {
        std::cout<<"Cell not available!"<<std::endl;
        std::cout<<"filled cells!"<<filledCells<<std::endl;
        //break;
     }
    
    system("CLS");
    renderTables(tableArray,filledPositions,filledCells);
    //std::cout<<"you did good! "<<selectedPosition;
} while( selectedPosition!=90  && isgameWon(tableArray)==false);

if(isgameWon(tableArray)){
    std::cout<<std::endl<<"CONGRATULATIONS, YOU HAVE SUCCESSFULLY COMPLETED THE GAME!"<<std::endl;
}
if(selectedValue==0){
    std::cout<<std::endl<<"HAVE A NICE DAY!"<<std::endl;
}

}






// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                FUNCTION
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int generateNumberofFilledCells(){
    srand(time(NULL));
int filledCells= rand()%11+30;

return filledCells;
}

//===================================================================================

void generateFilledPositions(int (&filledPositions)[],const int filledCells){
    srand(time(NULL));

for( int i=0; i<filledCells;i++){
   
    int randPos= rand()%81;
    //check if the value already exists and repeate the loop step and try again if it does
    int* begin =filledPositions;
    int* end = filledPositions + filledCells/sizeof(int);
    auto ptr=std::find(begin,end,randPos);
    if(ptr!=end) {
        i=i-1;
        continue;
    }
    filledPositions[i]=randPos;
}

}

//======================================================================================

void populateInitialCells(int (&tableArray)[3][3][3][3],const int filledCells,int filledPositions[]){

     // print oout the filled positions
                    std::cout<<std::endl<<"filled cells include: ";
                    for(int q=0 ;q<filledCells;q++){
                        std::cout<<filledPositions[q]<<", ";
                    }
 srand(time(NULL));
  int* start =filledPositions;
  int* finish=filledPositions + filledCells*sizeof(int);
int pos=0;
    for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0; l<3;l++){
                    pos=27*i+9*k+3*j+l;
                    auto exists= std::find(start,finish,pos);
                    std::cout<<std::endl;
                   // std:: cout<<"we did: "<<i<<j<<k<<l<<" pos: "<<pos<<" exists "<<(exists!=finish)<<" filled cells "<<filledCells<<std::endl;
                    for(int a=0;a<filledCells;a++){
                    if(filledPositions[a]==pos){
                        int fill;
                        do{
                            fill=rand() % 9 + 1;
                            //std::cout<<"been here fill:"<<fill<<" "<<i<<","<<j<<","<<k<<","<<l<<" repetead? "<<isItRepeated("row",i*3+k,fill,tableArray)<<isItRepeated("col",j*3+l,fill,tableArray)<<" row:"<<i*3+k<<" col:"<<j*3+l<<std::endl;
                        } while(isItRepeated("row",i*3+k,fill,tableArray) || isItRepeated("col",j*3+l,fill,tableArray)|| isItRepeated("block",i*3+j,fill,tableArray));
                       
                          tableArray[i][j][k][l] = fill;
                    }
                    } 
                    
                } 
            }   
       }
    }

}

//===============================================================================================================================

void renderTables(int tableArray[3][3][3][3],int filledPositions[],int filledCells){
        std::cout<<"\n\033[1;33m===========================================================";
        std::cout<<"              =========================================================== "<<std::endl;
    int counter=0,colcounter=0;
    for(int i=0; i<3;i++){
        for(int k=0;k<3;k++){
            std::cout<<"  ";
            for(int j=0;j<3;j++){
                for(int l=0; l<3;l++){
                    colcounter=colcounter+1;
                    if (tableArray[i][j][k][l]==0 && colcounter%3==0){
                        std::cout<<"\033[1;33m   |  ";
                    }
                    if (tableArray[i][j][k][l]==0 && colcounter%3!=0){
                        std::cout<<"\033[1;30m   |  ";
                    } 
                    int selectedPosition= 27*i+9*k+3*j+l;

                    if(checkSelectedPosition(selectedPosition,filledPositions,filledCells)){
                    
                            if( tableArray[i][j][k][l]<=9 &&tableArray[i][j][k][l]>0 && colcounter%3==0 && colcounter>2){
                        
                            std::cout<<"\033[1;34m"<< tableArray[i][j][k][l]<<"\033[1;33m  |  ";
                            } 
                            if(tableArray[i][j][k][l]<=9 &&tableArray[i][j][k][l]>0 && colcounter%3!=0 && colcounter>2){
                            std::cout<<"\033[1;34m"<< tableArray[i][j][k][l]<<"\033[0m  |  ";   
                            }  
                    } else {
                        //std::cout<<"selected Position red: "<<selectedPosition<<" : "<<checkSelectedPosition(selectedPosition,filledPositions,filledCells)<<" ";
                         if( tableArray[i][j][k][l]<=9 &&tableArray[i][j][k][l]>0 && colcounter%3==0 && colcounter>2){
                        
                            std::cout<<"\033[1;31m"<< tableArray[i][j][k][l]<<"\033[1;33m  |  ";
                            } 
                            if(tableArray[i][j][k][l]<=9 &&tableArray[i][j][k][l]>0 && colcounter%3!=0 && colcounter>2){
                            std::cout<<"\033[1;31m"<< tableArray[i][j][k][l]<<"\033[0m  |  ";   
                            }  

                    }
                }   
            }
                     counter=counter+1;
                    if(counter%3==0 && counter>1){
                        std::cout<<"\033[1;30m                 "<< colcounter-9<<"  |  "<<colcounter-8<<"  |  "<<colcounter-7<<"\033[1;33m |  "<<"\033[1;30m"<<colcounter-6<<"  |  "<<colcounter-5<<"  |  "<<colcounter-4<<"\033[1;33m  |  "<<"\033[1;30m"<<colcounter-3<<"  |  "<<colcounter-2<<" | "<<colcounter-1<<"\033[1;33m | "<<std::endl;
                        std::cout<<"\033[1;33m"<<"============================================================";
                        std::cout<<"             ==========================================================="<<std::endl;

                    }else{
                       std::cout<<"\033[1;30m                 "<< colcounter-9<<"  |  "<<colcounter-8<<"  |  "<<colcounter-7<<"\033[1;33m |  "<<"\033[1;30m"<<colcounter-6<<"  |  "<<colcounter-5<<"  |  "<<colcounter-4<<"\033[1;33m  |  "<<"\033[1;30m"<<colcounter-3<<"  |  "<<colcounter-2<<" | "<<colcounter-1<<"\033[1;33m | "<<std::endl;

                   std::cout<<"\033[1;30m------------------------------------------------------------";
                   std::cout<<"                 -------------------------------------------------------"<<std::endl;
                    }   
                }    
            }
}

//==============================================================================================================================

bool isItRepeated(std::string scope,int scopeSpecifier,double value,int (&tableArray)[3][3][3][3]){
std::string rowElem;

if (scope=="row"){
    for(int i=0; i<3;i++){
        for(int k=0;k<3;k++){
            for(int j=0;j<3;j++){
                for(int l=0; l<3;l++){
                      
                    if(i*3+k==scopeSpecifier){
                       rowElem = rowElem +"["+std::to_string(scopeSpecifier)+"]"+ ", " + std::to_string(tableArray[i][j][k][l])+"("+std::to_string(i) + std::to_string(j)+std::to_string(k)+std::to_string(l)+")";
                        if(value==tableArray[i][j][k][l]){
                            return true;
                            //std::cout<<"the row elements were "<<rowElem<<"from repetead! row="<<scopeSpecifier;
                        }
                    }
                   
                } 
            }   
        }
    }
}

if (scope=="col"){
    for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0; l<3;l++){
                    
                    if(j*3+l==scopeSpecifier){
                        if(value==tableArray[i][j][k][l]){
                            return true;
                        }
                    }
                   
                } 
            }   
        }
    }
}

if (scope=="block"){
    for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0; l<3;l++){
                    
                    if(i*3+j==scopeSpecifier){
                        if(value==tableArray[i][j][k][l]){
                            return true;
                        }
                    }
                   
                } 
            }   
        }
    }
}
 return false;

}

//================================================================================

void receiveInput(int (&tableArray)[3][3][3][3],int position,int value){
int i,j,k,l;
l=position%3;
if(position<27){
    i=0;
    k=position/9;
    }
if(position>26&&position<54){
    i=1;
    k=(position-27)/9;
}

if(position>53 && position<81){
    i=2;
    k=(position-54)/9;
}
    j=(position-27*i-9*k-1)/3;
if(isItRepeated("row",i*3+k,value,tableArray) || isItRepeated("col",j*3+l,value,tableArray)|| isItRepeated("block",i*3+j,value,tableArray)){
    std::cout<<"Repetition, please use another value"<<std::endl;
}else{
    tableArray[i][j][k][l]=value;
}
//std::cout<<"the coordinates of :"<<position<<" are: "<<i<<", "<<j<<", "<<k<<", "<<l<<std::endl;
}

//===========================================================================================

bool checkSelectedPosition(int selectedPosition, int filledPositions[],int filledCells){
for (int i=0;i<filledCells;i++){
     if(filledPositions[i]==selectedPosition){
        return false;
     } 
}
     return true;
}

//==============================================================================================
bool isgameWon(int tableArray[3][3][3][3]){
for(int i=0; i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                for(int l=0; l<3;l++){
                      if( tableArray[i][j][k][l]==0){
                        return false;
                      }
                        }
                    }
                   
                } 
            } 
    return true;
}
