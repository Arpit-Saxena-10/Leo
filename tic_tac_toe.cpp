#include <iostream>

using namespace std;
#include <vector>
const int n=3; 
int count= 0;

void show(char board[][n])
{
    for(int i=1;i<=n;i++)
    {
        cout << "|";
        
        for(int j=1;j<=n;j++)
        {
            cout << board[i-1][j-1] << "|";
        }
         
        cout << endl;
    }
}

bool checkx(char board[][n])
{
    for(int i=0;i<n;i++)
    {
        bool checkline=true;
        
        for(int j=0;j<n;j++)
        {
            if(board[i][j]=='O' || board[i][j]==' ')    // checking horizontally
            {
                checkline=false;
                break;
            }
        }
        if(checkline) {return true;}
    }
    
    for(int i=0;i<n;i++)
    {
        bool checkline=true;
        
        for(int j=0;j<n;j++)
        {
            if(board[j][i]=='O' || board[j][i]==' ')     // checking vertically
            {
                checkline=false;
                break;
            }
        }
        if(checkline) {return true;}
    }
    
    bool checkline=true;
    
    for(int i=0;i<n;i++)
    {
        if(board[i][i]=='O' || board[i][i]==' ')
        {
            checkline=false;
            break;
        }
        
    }
    if(checkline) {return true;}
    
    bool checkline2=true;
    for(int i=0;i<n;i++)
    {
        if(board[i][n-1-i]=='O' || board[i][n-1-i]==' ')
        {
            checkline2=false;
            break;
        }
    }
    
    if(checkline2) {return true;}
    
    
    return false ;
    
}

bool checko(char board[][n])
{
    for(int i=0;i<n;i++)
    {
        bool checkline=true;
        
        for(int j=0;j<n;j++)
        {
            if(board[i][j]=='X' || board[i][j]==' ')    // checking horizontally
            {
                checkline=false;
                break;
            }
        }
        if(checkline) {return true;}
    }
    
    for(int i=0;i<n;i++)
    {
        bool checkline=true;
        
        for(int j=0;j<n;j++)
        {
            if(board[j][i]=='X' || board[j][i]==' ')     // checking vertically
            {
                checkline=false;
                break;
            }
        }
        if(checkline) {return true;}
    }
    
    bool checkline=true;
    
    for(int i=0;i<n;i++)
    {
        if(board[i][i]=='X' || board[i][i]==' ')
        {
            checkline=false;
            break;
        }
        
    }
    if(checkline) {return true;}
    
    
    bool checkline2=true;
    
    for(int i=0;i<n;i++)
    {
        if(board[i][n-1-i]=='X' || board[i][n-1-i]==' ')
        {
            checkline2=false;
            break;
        }
    }
    
    if(checkline2) {return true;}
    
    
    return false ; 
    
}

bool check_draw(char board[][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[i][j]==' ')
                return false;
        }
        
    }
    return(!(checkx(board) || checko(board)  ));
}




struct state
{
    char board[n][n];
    bool turn;
    bool possible_move[n][n];
    int no_of_moves;
    vector <state *>next;
    
    state(const char input[][n],const bool turn1)
    {
        turn = turn1;
        no_of_moves=0;
        char temp[n][n];
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                temp[i][j] = input[i][j];
                board[i][j]= input[i][j];
                
                if(input[i][j]==' ')
                {
                    no_of_moves++;
                    possible_move[i][j]=true;
                }
                else
                {
                    possible_move[i][j]=false;
                }
            }
        }
       
        
        for(int i=0;i<n;i++)
        {
          for(int j=0;j<n;j++)
          {
              if(board[i][j]==' ')                     // if square is empty
              {
                  if(turn)
                    temp[i][j] = 'O';
                  else
                    temp[i][j] = 'X';
                    
                  //cout << count++ << "-"<< i<<j << " ";    
                  state *next_move = new state(temp,!turn);
                  //cout << "b";
                  next.push_back(next_move);
                  //cout << "c";
                  temp[i][j]   = ' ';
              }
          }
        }
    }
};

int score(state position)
{
    if(position.turn)
    {
        if(checkx(position.board))
            return -1;
        else if(check_draw(position.board))
            return 0;
        else
        {
            int max_so_far = -1 ;
            
            for(size_t i=0; i<position.next.size(); i++)
            {
                int t = score(*(position.next[i]));
                max_so_far = max(max_so_far,t);
            }
            
            return max_so_far;
        }
    }
    
    else
    {
        if(checko(position.board))
            return 1;
        else if(check_draw(position.board))
            return 0;
        else
        {
            int min_so_far = 1 ;
            
            for(size_t i=0; i<position.next.size(); i++)
            {
                int t = score(*(position.next[i]));
                min_so_far = min(min_so_far,t);
            }
            
            return min_so_far;
        }
    }
}

void move(state position,state next_position,int &a,int &b)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((position.board[i][j] == ' ') && (next_position.board[i][j] != ' '))
            {
                a = i;
                b = j;
            }
        }
    }
}

void best_move(state position,int &a,int &b)
{
    int max_so_far = -1 ;
    int p = 0,counter = 0 ;
    
            
    for(size_t i=0; i<position.next.size(); i++)
    {
        int t = score(*(position.next[i]));
        max_so_far = max(max_so_far,t);
        if(max_so_far == t)
            p = counter;
        counter++;    
    }
    
    move(position,*position.next[p],a,b);
}

bool compare_board(char board_a[][n],char board_b[][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board_a[i][j] != board_b[i][j] )
                return false;
        }
    }
    return true;
}

void update_state(state &position,char board[][n])           // board represents next move, state is to be updated with next move 
{
    for(size_t i=0; i<position.next.size(); i++)
    {
        if(compare_board(position.next[i]->board,board))
        {
            position = *position.next[i];
            break;
        }
    }
            
}

/*struct node
{
  state position;
  vector <node * >next;
  
  node(state a)
  {
      //this->position = a;
      char temp[n][n];
      
      for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              temp[i][j] = position.board[i][j];
          }
      }
      
      
      
      for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              if(position.board[i][j]=' ')                     // if square is empty
              {
                  if(position.turn)
                    temp[i][j] = 'X';
                  else
                    temp[i][j] = 'O';
                    
                  //node *next_move = new node();
                  //next_move->position = state(temp,!(position.turn));
                  //next.push_back(next_move);    
              }
          }
      }
  }
};*/








int main()
{
    char board[n][n];
    int a = -1,b = -1;
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {                               //initializing board to empty spaces
            board[i][j]=' ';
        }
    }
    //board[0][0] = 'X';
    //board[2][2] = 'O';
    //board[0][2] = 'X';
    //board[1][0] = 'O';
    //board[1][1] = 'X';
    //board[0][2] = 'O';
    //board[1][1] = 'O';
    
    bool turn = false;
    
    //cout << (board[0][0]==' ') << " ";
    
    
    state game(board,turn);
    
    /*int counter = 0 ;
    int max_so_far = -3 ;
    int p = -3;
    for(size_t i=0; i<game.next.size(); i++)
    {
        vector <int> t ;
        t.push_back(score(*(game.next[i])));
        cout << endl;
        show(game.next[i]->board);
        cout << endl << t[counter];
        max_so_far = max(max_so_far,t[counter]);
        if(max_so_far == t[counter])
            p = counter;
        counter++;    
    }
    
    cout << p << " " << counter << endl;
    show(game.next[p]->board);
    */
    
    
    show(game.board);
    
    while( (!(checkx(game.board) || checko(game.board))) && (!check_draw(game.board)) )
    {
        int row,column;
        cout << "choose row and column"<<endl;
        cin >> row >> column;
        
        while(game.board[row][column] != ' ')
        {
            cout << "Square already filled. Choose again"<<endl;
            cin >> row >> column;    
        }
        
        board[row][column]='X';
        turn = !turn;
        update_state(game,board);
        show(game.board);
        
        if(checkx(game.board) || checko(game.board) || check_draw(game.board))
        {
            break;
        }
        
        
        //int row2,column2;cout << "choose row and cloumn"<<endl;cin >> row2 >> column2;
        cout << endl;
        best_move(game,a,b);
        board[a][b]='O';
        turn = !turn;
        update_state(game,board);
        show(game.board);
        
        
    }
    
    
    if(check_draw(game.board))
        cout << "It's a draw" << endl;
    
    else if(turn)
        cout << "You win." << endl;
    else
        cout << "You lose" << endl;
    
       
}   

