#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Must read comments on related functions i.e. "put()" before checking main.
struct center // to keep the record of placed operators center and operator size
{
    int row_center ;
    int column_center ;
    int op_size_center ;
};

struct grid
{
    char grid_max[10][10] ;
    int row_size ;
    int column_size ;
    char sign[1] ;
    int row ;
    int column ;
    int op_size ; 
    bool check2();
    bool check();
    void erase();
    void create();
    void put();
    void put2() ;
    void move();
    char inst[4] ;
    int inst_row ;
    int inst_column ;
    int inst_size ;
    center center_of[10][10] ;
};

using namespace std ;

int main(int argc , char* argv[])
{
    
 char filename[20] ;
 char filename2[20] ;
 strcpy(filename , argv[1]) ;
 strcpy(filename2 , argv[2]) ;
 
 
 grid mygrid;
 
 
 FILE* toread ;
 toread = fopen(filename, "r+");
 if(!toread)
 {
     cerr << "Cannot open file" << endl;
			exit(1);
 }
 fseek(toread, 0, SEEK_SET);
 fscanf(toread , "%d %d" , &mygrid.row_size , &mygrid.column_size) ;
 mygrid.create() ;

    while(!feof(toread))
    {
        if
        ( fscanf(toread , "%s %d %d %d" , mygrid.sign , &mygrid.row, &mygrid.column, &mygrid.op_size) == EOF)
        {
            break;
        }
        
        bool a = mygrid.check() ; //checks if the instruction in grid.txt is doable.
        if(a)
        {
            mygrid.put() ;
            cout<<"SUCCESS: Operator " <<mygrid.sign<<" with size "<<mygrid.op_size<<" is placed on ("<<mygrid.row<<","<<mygrid.column<<")."<<endl;
        }

    }
    
    fclose(toread) ;
    
    FILE* toread2 ;
    toread2 = fopen(filename2, "r+");
            if(!toread2)
            {
                 cerr << "Cannot open file" << endl;
		            exit(1);
            }
    fseek(toread2, 0, SEEK_SET);

 
    while(!feof(toread2))
    {
        
        
        if
        ( fscanf(toread2 , "%s %d %d %d" , mygrid.inst 
        , &mygrid.inst_row, &mygrid.inst_column, &mygrid.inst_size) == EOF)
        {
            break;
        }
            
        
        
        
        if(mygrid.inst[2] == 'R') //if the instruction is MVR, letter will be R.
        {
            //
            if(mygrid.grid_max[mygrid.inst_row-1][mygrid.inst_column-1] != '\0')
            {
                
                mygrid.row = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].row_center + 1 ;
                mygrid.column = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].column_center + 1 ;
                mygrid.sign[0] = mygrid.grid_max[mygrid.row-1][mygrid.column-1] ;
                
                mygrid.erase();
                    
                mygrid.column = mygrid.column + mygrid.inst_size ;
                
                if(mygrid.check2()) //uses a smilar check with above, reason for it will be explained function def.
                {
                    
                    
                    mygrid.put() ;
                    cout<<"SUCCESS: "<<mygrid.sign[0]<<" moved from "
                    <<"("<<mygrid.row<<","<<mygrid.column - mygrid.inst_size<<") "
                    <<"to "
                    <<"("<<mygrid.row<<","<<mygrid.column<<")"
                    <<endl ;
    
                }
                else
                {
                    mygrid.column = mygrid.column - mygrid.inst_size ;
                    mygrid.put2();
                }
                

            }
            
        }
        
        if(mygrid.inst[2] == 'L')
        {
            
            if(mygrid.grid_max[mygrid.inst_row-1][mygrid.inst_column-1] != '\0')
            {
                mygrid.row = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].row_center + 1 ;
                mygrid.column = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].column_center + 1 ;
                mygrid.sign[0] = mygrid.grid_max[mygrid.row-1][mygrid.column-1] ;
                
                mygrid.erase();
                mygrid.column = mygrid.column - mygrid.inst_size ;
                bool b = mygrid.check2() ;
                if(b)
                {

                    mygrid.put() ;
                    cout<<"SUCCESS: "<<mygrid.sign[0]<<" moved from "
                    <<"("<<mygrid.row<<","<<mygrid.column + mygrid.inst_size<<") "
                    <<"to "
                    <<"("<<mygrid.row<<","<<mygrid.column<<")"
                    <<endl ;
                }
                else
                {
                    mygrid.column = mygrid.column + mygrid.inst_size ;
                    mygrid.put2();

                }
                

            }
            
        }
        
        if(mygrid.inst[2] == 'U')
        {
            
            if(mygrid.grid_max[mygrid.inst_row-1][mygrid.inst_column-1] != '\0')
            {
                mygrid.row = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].row_center + 1 ;
                mygrid.column = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].column_center + 1 ;
                mygrid.sign[0] = mygrid.grid_max[mygrid.row-1][mygrid.column-1] ;
                
                mygrid.erase();
                mygrid.row = mygrid.row - mygrid.inst_size ;
                bool b = mygrid.check2() ;
                if(b)
                {

                    mygrid.put() ;
                    
                    cout<<"SUCCESS: "<<mygrid.sign[0]<<" moved from "
                    <<"("<<mygrid.row + mygrid.inst_size<<","<<mygrid.column<<") "
                    <<"to "
                    <<"("<<mygrid.row<<","<<mygrid.column<<")"
                    <<endl ;
                }
                else
                {
                    mygrid.row = mygrid.row + mygrid.inst_size ;
                    mygrid.put2();

                }
            
            }
        }    
        
        if(mygrid.inst[2] == 'D')
        {
            
           if(mygrid.grid_max[mygrid.inst_row-1][mygrid.inst_column-1] != '\0')
            {
                mygrid.row = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].row_center + 1 ;
                mygrid.column = mygrid.center_of[mygrid.inst_row-1][mygrid.inst_column-1].column_center + 1 ;
                mygrid.sign[0] = mygrid.grid_max[mygrid.row-1][mygrid.column-1] ;
                
                mygrid.erase();
                mygrid.row = mygrid.row + mygrid.inst_size ;
                bool b = mygrid.check2() ;
                if(b)
                {

                    mygrid.put() ;
                    
                    cout<<"SUCCESS: "<<mygrid.sign[0]<<" moved from "
                    <<"("<<mygrid.row - mygrid.inst_size<<","<<mygrid.column<<") "
                    <<"to "
                    <<"("<<mygrid.row<<","<<mygrid.column<<")"
                    <<endl ;
                   // cout<<mygrid.grid_max[4][3]<<endl ;
                }
                else
                {
                    mygrid.row = mygrid.row - mygrid.inst_size ;
                    mygrid.put2();

                }
           
            }
            
        
        
        }
            
    }

}    
 




bool grid::check() // checks for each operator if the instruction is doable
{
    
    bool safe = true ;
    char sign_ch = sign[0] ;
	// safe is a bool to check if it is okey to place the operator
	// counter is there to seperate border error and conflict error when the safe is false.
    if(sign_ch == '+')
    {
    	
        int counter = 0 ;
        		// to check edges, compares with 1 and row size
        		//for example if the column is 3 and grid size is 5x5 operator size with 2 would be on the edge
        		//anything bigger than 3 would be a overflow on the left and if it is 3 overflow on the right.
                if((column - op_size < 1 || column + op_size > column_size
                    || row - op_size < 1 || row + op_size > row_size  ))
                    {
                        counter++ ;
                        safe = false ;
                        
                        cout<<"BORDER ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                //same logic with + operator is applied according to the other operators behaviour.
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    if(grid_max[row_array_index][i] != '\0')
                        safe = false ;
                }
                for(int i = row_array_index - op_size ; i <= row_array_index + op_size ; i++)
                {
                    if(grid_max[i][column_array_index] != '\0')
                        safe = false ;
                }
        
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                }
        
    }
    //
    else if(sign_ch == '-')
    {
        int counter = 0 ;
                if((column - op_size < 1) || (column + op_size > column_size  ))
                    {
                        counter++ ;
                        safe = false ;
                        cout<<"BORDER ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    if(grid_max[row_array_index][i] != '\0')
                        safe = false ;
                }
                
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                }
        
    }
    //
    else if(sign_ch == '/')
    {
        int counter = 0 ;
                if((column - op_size < 1 || column + op_size > column_size
                    || row - op_size < 1 || row + op_size > row_size  ))
                    {
                        safe = false ;
                        counter++ ;
                        cout<<"BORDER ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                    
                }
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                }
    }
    //
    else if(sign_ch == 'x')
    {
        int counter = 0 ;
                if((column - op_size < 1 || column + op_size > column_size
                    || row - op_size < 1 || row + op_size > row_size  ))
                    {
                        safe = false ;
                        counter++ ;
                        cout<<"BORDER ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                    }
            
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;

                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                    
                }
                for(int i = column_array_index - op_size, j= row_array_index -op_size ;
                 i <= column_array_index + op_size && j <= row_array_index - op_size ; i++ , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                }
                
                if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: Operator "
                        <<sign<<" with size "<<op_size
                        <<" can not be placed on ("<<row<<","<<column<<")."<<endl;
                }
        
    }

    else 
    {
        cout<<"Not a valid operator"<<endl;
    }
    
    return safe ;
}
void grid::create() // assigns every empty place with null character.
{
    cout<<"A grid is created: "<<row_size<<" "<<column_size<<endl ;
    
    for(int i = 0 ; i < row_size ; i++)
    {
        for(int j = 0 ; j < column_size ; j++)
        {
            grid_max[i][j] = '\0' ;
        }
    }
}

void grid::put() //places wanted  operator on the grid
{
    char sign_ch = sign[0] ;
    if(sign_ch == '+')
    {
                // keeps the record of the center of the operator that is placed.
                center_of[row-1][column-1].op_size_center = op_size ;
                
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    grid_max[row_array_index][i] = '+' ;
                    center_of[row_array_index][i].row_center = row_array_index ;
                    center_of[row_array_index][i].column_center = column_array_index ;
                        
                }
                for(int i = row_array_index - op_size ; i <= row_array_index + op_size ; i++)
                {
                    grid_max[i][column_array_index] = '+' ;
                    center_of[i][column_array_index].row_center = row_array_index ;
                    center_of[i][column_array_index].column_center = column_array_index ;
                }
        
    }
    //
    else if(sign_ch == '-')
    {
        
 
                center_of[row-1][column-1].op_size_center = op_size ;
 
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    grid_max[row_array_index][i] = '-' ;
                    center_of[row_array_index][i].row_center = row_array_index ;
                    center_of[row_array_index][i].column_center = column_array_index ;
                }
                
        
    }
    //
    else if(sign_ch == '/')
    {
        
                center_of[row-1][column-1].op_size_center = op_size ;
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        grid_max[j][i] = '/' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                    
                }
        
    }
    //
    else if(sign_ch == 'x')
    {
        
                center_of[row-1][column-1].op_size_center = op_size ;

                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        grid_max[j][i] = 'x' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                            
                    
                }
                for(int i = column_array_index - op_size, j= row_array_index -op_size ;
                 i <= column_array_index + op_size && j <= row_array_index + op_size ; i++ , j++)
                {
                    
                        grid_max[j][i] = 'x' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                    
                }
        
    }
    
        
    
    else 
    {
        cout<<"Operator is not valid"<<endl;
    }
    
    
}



void grid::erase()
{
    
    char sign_ch = sign[0] ;
    if(sign_ch == '+')
    {
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - center_of[row-1][column-1].op_size_center ; i <= column_array_index + center_of[row-1][column-1].op_size_center ; i++)
                {
                    grid_max[row_array_index][i] = '\0' ;

                        
                }
                for(int i = row_array_index - center_of[row-1][column-1].op_size_center ; i <= row_array_index + center_of[row-1][column-1].op_size_center ; i++)
                {
                    grid_max[i][column_array_index] = '\0' ;
  
                }
        
    }
    //
    else if(sign_ch == '-')
    {
        
 
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - center_of[row-1][column-1].op_size_center ; i <= column_array_index + center_of[row-1][column-1].op_size_center ; i++)
                {
                    grid_max[row_array_index][i] = '\0' ;
  
                
        
                }
    }
    else if(sign_ch == '/')
    {
        
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + center_of[row-1][column-1].op_size_center, j= row_array_index -center_of[row-1][column-1].op_size_center ;
                 i >= column_array_index - center_of[row-1][column-1].op_size_center && j <= row_array_index + center_of[row-1][column-1].op_size_center ; i-- , j++)
                {
                    
                        grid_max[j][i] = '\0' ;
            
                    
                }
        
    }
    //
    else if(sign_ch == 'x')
    {
        

                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + center_of[row-1][column-1].op_size_center, j= row_array_index -center_of[row-1][column-1].op_size_center ;
                 i >= column_array_index - center_of[row-1][column-1].op_size_center && j <= row_array_index + center_of[row-1][column-1].op_size_center ; i-- , j++)
                {
                    
                        grid_max[j][i] = '\0' ;
                       
                            
                    
                }
                for(int i = column_array_index - center_of[row-1][column-1].op_size_center, j= row_array_index -center_of[row-1][column-1].op_size_center ;
                 i <= column_array_index + center_of[row-1][column-1].op_size_center && j <= row_array_index + center_of[row-1][column-1].op_size_center ; i++ , j++)
                {
                    
                        grid_max[j][i] = '\0' ;
                     
                    
                }
        
    
    }
}    

bool grid::check2() // check2 recieves its column and row where the operator wanted to be move to.
{
    
    bool safe = true ;
    char sign_ch = sign[0] ;
    int row_temp = row ;
    int column_temp = column ;
    // to print out the row and column where it is moved from, it assigns temp values for them according to 
    // move instruction. finds the operator size of given row and column by using center_of struct declared above.
    if(inst[2] == 'R')
    {
        column_temp = column - inst_size ;
    }
    if(inst[2] == 'L')
    {
        column_temp = column + inst_size ;
    }
    if(inst[2] == 'U')
    {
        row_temp = row + inst_size ;
    }
    if(inst[2] == 'D')
    {
        row_temp = row - inst_size ;
    }
    
    
    if(sign_ch == '+')
    {
        int counter = 0 ;
        
                if((column - center_of[row_temp-1][column_temp-1].op_size_center < 1 || column + center_of[row_temp-1][column_temp-1].op_size_center > column_size
                    || row - center_of[row_temp-1][column_temp-1].op_size_center < 1 || row + center_of[row_temp-1][column_temp-1].op_size_center > row_size  ))
                    {
                        counter++ ;
                        safe = false ;

                        cout<<"BORDER ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - center_of[row_temp-1][column_temp-1].op_size_center ; i <= column_array_index + center_of[row_temp-1][column_temp-1].op_size_center ; i++)
                {
                    if(grid_max[row_array_index][i] != '\0')
                        safe = false ;
                }
                for(int i = row_array_index - center_of[row_temp-1][column_temp-1].op_size_center ; i <= row_array_index + center_of[row_temp-1][column_temp-1].op_size_center ; i++)
                {
                    if(grid_max[i][column_array_index] != '\0')
                        safe = false ;
                }
        
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                }
        
    }
    //
    else if(sign_ch == '-')
    {
        int counter = 0 ;
                if((column - center_of[row_temp-1][column_temp-1].op_size_center < 1) || (column + center_of[row_temp-1][column_temp-1].op_size_center > column_size  ))
                    {
                        counter++ ;
                        safe = false ;

                        cout<<"BORDER ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - center_of[row_temp-1][column_temp-1].op_size_center ; i <= column_array_index + center_of[row_temp-1][column_temp-1].op_size_center ; i++)
                {
                    if(grid_max[row_array_index][i] != '\0')
                        safe = false ;
                }
                
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                }
        
    }
    //
    else if(sign_ch == '/')
    {
        int counter = 0 ;
                if((column - center_of[row_temp-1][column_temp-1].op_size_center < 1 || column + center_of[row_temp-1][column_temp-1].op_size_center > column_size
                    || row - center_of[row_temp-1][column_temp-1].op_size_center < 1 || row + center_of[row_temp-1][column_temp-1].op_size_center > row_size  ))
                    {
                        safe = false ;
                        counter++ ;
                        cout<<"BORDER ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                    }
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + center_of[row_temp-1][column_temp-1].op_size_center, j= row_array_index -center_of[row_temp-1][column_temp-1].op_size_center ;
                 i >= column_array_index - center_of[row_temp-1][column_temp-1].op_size_center && j <= row_array_index + center_of[row_temp-1][column_temp-1].op_size_center ; i-- , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                    
                }
        if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                }
    }
    //
    else if(sign_ch == 'x')
    {
        int counter = 0 ;
                if((column - center_of[row_temp-1][column_temp-1].op_size_center < 1 || column + center_of[row_temp-1][column_temp-1].op_size_center > column_size
                    || row - center_of[row_temp-1][column_temp-1].op_size_center < 1 || row + center_of[row_temp-1][column_temp-1].op_size_center > row_size  ))
                    {
                        safe = false ;
                        counter++ ;
                        cout<<"BORDER ERROR: "
                        <<sign<<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                    }
            
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;

                for(int i = column_array_index + center_of[row_temp-1][column_temp-1].op_size_center, j= row_array_index -center_of[row_temp-1][column_temp-1].op_size_center ;
                 i >= column_array_index - center_of[row_temp-1][column_temp-1].op_size_center && j <= row_array_index + center_of[row_temp-1][column_temp-1].op_size_center ; i-- , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                    
                }
                for(int i = column_array_index - center_of[row_temp-1][column_temp-1].op_size_center, j= row_array_index -center_of[row_temp-1][column_temp-1].op_size_center ;
                 i <= column_array_index + center_of[row_temp-1][column_temp-1].op_size_center && j <= row_array_index - center_of[row_temp-1][column_temp-1].op_size_center ; i++ , j++)
                {
                    
                        if(grid_max[j][i] != '\0')
                            safe = false ;
                }
                
                if(counter == 0 && safe == false)
                {
                    cout<<"CONFLICT ERROR: "
                        <<sign
                        <<" can not be moved from ("<<row_temp<<","<<column_temp<<") to "
                        <<"("<<row<<","<<column<<")"<<endl;
                }
        
    }

    else 
    {
        cout<<"invalid sign"<<endl;
    }

    return safe ;
}

void grid::put2()
{
	//put assigns a center but put2 used when we cant move the operator so it shouldn't assign anything.
    char sign_ch = sign[0] ;
    if(sign_ch == '+')
    {
                
                //center_of[row-1][column-1].op_size_center = op_size ;
                
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    grid_max[row_array_index][i] = '+' ;
                    center_of[row_array_index][i].row_center = row_array_index ;
                    center_of[row_array_index][i].column_center = column_array_index ;
                        
                }
                for(int i = row_array_index - op_size ; i <= row_array_index + op_size ; i++)
                {
                    grid_max[i][column_array_index] = '+' ;
                    center_of[i][column_array_index].row_center = row_array_index ;
                    center_of[i][column_array_index].column_center = column_array_index ;
                }
        
    }
    //
    else if(sign_ch == '-')
    {
        
 
               // center_of[row-1][column-1].op_size_center = op_size ;
 
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index - op_size ; i <= column_array_index + op_size ; i++)
                {
                    grid_max[row_array_index][i] = '-' ;
                    center_of[row_array_index][i].row_center = row_array_index ;
                    center_of[row_array_index][i].column_center = column_array_index ;
                }
                
        
    }
    //
    else if(sign_ch == '/')
    {
        
                //center_of[row-1][column-1].op_size_center = op_size ;
        
                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        grid_max[j][i] = '/' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                    
                }
        
    }
    //
    else if(sign_ch == 'x')
    {
        
                //center_of[row-1][column-1].op_size_center = op_size ;

                int row_array_index , column_array_index;
                row_array_index = row - 1 ;
                column_array_index = column - 1 ;
                for(int i = column_array_index + op_size, j= row_array_index -op_size ;
                 i >= column_array_index - op_size && j <= row_array_index + op_size ; i-- , j++)
                {
                    
                        grid_max[j][i] = 'x' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                            
                    
                }
                for(int i = column_array_index - op_size, j= row_array_index -op_size ;
                 i <= column_array_index + op_size && j <= row_array_index + op_size ; i++ , j++)
                {
                    
                        grid_max[j][i] = 'x' ;
                        center_of[j][i].row_center = row_array_index ;
                        center_of[j][i].column_center = column_array_index ;
                    
                }
        
    }
    
        
    
    else 
    {
        cout<<"can not place"<<endl;
    }
    
    
}
