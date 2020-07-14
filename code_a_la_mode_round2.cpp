#include<bits/stdc++.h>

using namespace std;
const int H = 7, W = 11;
const string DISH = "DISH", ICE_CREAM = "ICE_CREAM", 
    BLUEBERRIES = "BLUEBERRIES", NONE = "NONE", 
    CHOPPED_STRAWBERRIES = "CHOPPED_STRAWBERRIES", STRAWBERRIES = "STRAWBERRIES";
vector<string> Grid(H);
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
struct Customer{
    string order;
    int award;
    void read(){
        cin >> order >> award; cin.ignore();
    }
};
struct Pos{
    pair<int,int> blue, dish, icecream, cust, crate, board;
    void init(){
        for(int i = 0; i < H; i++){
            for(int j = 0; j < W; j++){
                if(Grid[i][j] == 'B'){
                    blue = make_pair(i,j);
                }
                else if(Grid[i][j] == 'I'){
                    icecream = make_pair(i,j);
                }
                else if(Grid[i][j] == 'W'){
                    cust = make_pair(i,j);
                }
                else if(Grid[i][j] == 'D'){
                    dish = make_pair(i,j);
                }
                else if(Grid[i][j] == 'S'){
                    crate = make_pair(i,j);
                }
                else if(Grid[i][j] == 'C'){
                    board = make_pair(i,j);
                }
            }
        }
    }
};
struct Object{
    int x,y;
    string item;
    void read(){
        cin >> x >> y >> item; cin.ignore();
    }
};
int main()
{
    int numAllCustomers;
    cin >> numAllCustomers; cin.ignore();
    vector<Customer> allCustomers(numAllCustomers);
    for(Customer& customer : allCustomers){
        customer.read();
    }
    for(string& s : Grid){
         cin >> s; cin.ignore();
    }

    // game loop
    while (true) {
        int turnsRemaining;
        cin >> turnsRemaining; cin.ignore();
        Object me, opponent;
        me.read();
        opponent.read();
        int numTablesWithItems; // the number of tables in the kitchen that currently hold an item
        cin >> numTablesWithItems; cin.ignore();
        vector<Object> occupied(numTablesWithItems);
        for(auto& object : occupied){
            object.read();
        }
        //------------------------------------------------IGNORE FOR THIS ROUND
        string ovenContents; // ignore until wood 1 league
        int ovenTimer;
        cin >> ovenContents >> ovenTimer; cin.ignore();
        //-------------------------------------------------------------

        int numCustomers; // the number of customers currently waiting for food
        cin >> numCustomers; cin.ignore();
        vector<Customer> currentCustomers(numCustomers);
        for(auto& customer : currentCustomers){
            customer.read();
        }
        Pos place;
        place.init();
        bool action = false;
        auto wait = [&](){
            cout << "WAIT" << endl;
        };
        auto use = [&](int x, int y){
            cout << "USE " << y << " " << x << endl;
            action = true;
        };
        auto move = [&](int x, int y){
            cout << "MOVE " << y << " " << x << endl;
            action = true;
        };
        //create action for strawberries. first go to crate then board
        //STRATEGY NOW
        /*IMPROVE STRATEGY
         *DETERMINE WHAT TO PICK NEXT SMARTLY BLUEBERRIES OR ICECREAM AFTER PICKING 
         *USE A PATHFINDING ALGORITHM TO DETERMINE THE MOST OPTIMAL ORDER TO PICK THE ITEMS.
        */
        auto strategy2 = [&](){
            if(me.item == NONE){
                pair<int,int> need = place.crate;
                use(need.first, need.second);
            }
            if(me.item == STRAWBERRIES){
                pair<int,int> need = place.board;
                use(need.first, need.second);
            }
            if(me.item == CHOPPED_STRAWBERRIES){
                pair<int,int> need = place.dish;
                use(need.first, need.second);
            }
            if(me.item == DISH+"-"+CHOPPED_STRAWBERRIES){
                pair<int,int> need = place.blue;
                use(need.first, need.second);
            }
            if(me.item == DISH+"-"+CHOPPED_STRAWBERRIES+"-"+BLUEBERRIES){
                pair<int,int> need = place.icecream;
                use(need.first, need.second);
            }  
            if(me.item == DISH+"-"+CHOPPED_STRAWBERRIES+"-"+BLUEBERRIES+"-"+ICE_CREAM){
                pair<int,int> need = place.cust;
                use(need.first, need.second);
            }
        };
        //-------------------------------------
        auto strategy1 = [&](){
            if(me.item == NONE){
                pair<int,int> need = place.dish;
                //assert(need != {-1,-1});
                use(need.first, need.second);
                //cerr << me.item << endl;
            }
            if(me.item == DISH){
                pair<int,int> need = place.blue;
                use(need.first, need.second);
            }
            if(me.item == DISH + "-"+BLUEBERRIES){
                pair<int,int> need = place.icecream;
                use(need.first, need.second);
            }
            if(me.item == DISH + "-" + BLUEBERRIES + "-"+ICE_CREAM){
                pair<int,int> need = place.cust;
                use(need.first, need.second);
            }
        };
        strategy2();
        if(!action) wait();
    }
}
