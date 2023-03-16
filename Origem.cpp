//Tennis tournament random generator

/* EXAMPLE OF INPUT:
4 (number of players participating in the tournament)
(Players and UTRs)
Alex 5
Dan 8
Joe 9
Chris 3*/

/*OR*/

/* EXAMPLE OF INPUT:
8 (number of players participating in the tournament)
(Players and UTRs)
Alex 12
Dan 13
Joe 10
Chris 9
Federer 14
Nadal 16
Ronaldo 12
Messi 13
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>    
#include <time.h>

using namespace std;

struct player {
    string name;
    int utr;

};

//function "func" compares both players UTRs and returns true or false
bool func(player i, player j) {
    return (i.utr > j.utr);
}

bool result(int i, int j) {
    //generates a random number from 1 to 100 and store in "r"
    int r = (rand() % (100) + 1);
    //"j" is the bye variable, so if it is "1" it means that the player automatically goes to the next round
    if (j == 1) {
        return true;
    }
    //if the difference between the players UTRs are bigger or equal than 8, 
    //the player with a smaller UTR has 5 percent change of win
    else if (i >= 8) {
        if (r > 5) {
            return true;
        }
        else {
            return false;
        }
    }
    //but if the difference between the players UTRs are 6 or 7, 
    //than the player with a smaller UTR has 10 percent change of win
    else if ((i == 6) or (i == 7)) {
        if (r > 10) {
            return true;
        }
        else {
            return false;
        }
    }
    //but if the difference between the players UTRs are 4 or 5, 
    //than the player with a smaller UTR has 20 percent change of win
    //same for 2 and 3 with 30 percent chance of win for smaller UTR
    //and if the difference is 0 than it is 50 percent chance of win for each player
    else if ((i == 4) or (i == 5)) {
        if (r > 20) {
            return true;
        }
        else {
            return false;
        }
    }
    else if ((i == 2) or (i == 3)) {
        if (r > 30) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (i == 1) {
        if (r > 40) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (i == 0) {
        if (r > 50) {
            return true;
        }
        else {
            return false;
        }
    }
    return 0;
}

//switch players positions, so the highest UTR alwasys show first
void swi(int& a, int& b, string& c, string& d) {
    int x;
    string y;
    x = b;
    b = a;
    a = x;
    y = d;
    d = c;
    c = y;
}

//this function bassically returns a random score for each game. 
//In tennis the maximum score is 6 but if it is tied in 5, they play until 7
//So if the loser score is equal to 5 or 6, we have to add 1 to the winner
void score(int& x, int& y) {
    x = 6;
    y = (rand() % 7);
    if ((y == 5) or (y == 6)) {
        x++;
    }
}

int main() {
    //Enter number of players, max 16
    int n;

    while(true) {
        cout << "Number of players: [2, 4, 8, 16]\n";
        cin >> n;
        if (n == 2 || n == 4 || n == 8 || n == 16) {
            break;
        }
        cout << "Please enter a valid number";
    }

    //vector players of type player(struct)
    vector <player> players(n);

    for (int i = 0; i < n; i++) {
        cout << "Player name: ";
        cin >> players[i].name;
        cout << "Player UTR: "; // UTR = Universal Tennis Rating
        cin >> players[i].utr;
    }

    //Sort players by their UTRs, using the function "func"
    sort(players.begin(), players.end(), func);

    cout << "Number of players: " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << players[i].name << " " << "(" << players[i].utr << ")" << endl;
    }

    //Create a vector named draw of type player to create the draw to see who is going to play agains who
    vector <player> draw(n);

    //copy one vector to the other, so I can make changes to the second
    for (int i = 0; i < n / 2; i++) {
        draw[i].name = players[i].name;
        draw[i].utr = players[i].utr;
    }

    srand(time(NULL));
    int r = (rand() % (n / 2)) + n / 2;


    int aux[16];
    for (int i = 0; i < n; i++) {
        aux[i] = 0;
    }

    //Generate the draw by sorting all players in the vector draw
    for (int i = n / 2; i < n; i++) {
        while (aux[r] == 1) {
            r = (rand() % (n / 2)) + n / 2;
        }
        draw[i].name = players[r].name;
        draw[i].utr = players[r].utr;
        aux[r] = 1;
    }

    int j = n - 1;
    int bye = 0;
    int z, q, w, dif;
    int l = 0;
    int n1 = n;
    vector <player> update(n);

    cout << "\n";
    //while n!=1 means that there are more than 1 player left, so we don't have a champion yet...
    while (n != 1) {
        z = 0;
        cout << "Matches: \n";
        for (int i = 0; i < n / 2; i++) {
            dif = (draw[i].utr - draw[j].utr);
            if (draw[j].utr == 0) {
                //assign 1 to bye
                bye = 1;
                n1--;
            }
            if (draw[i].utr < draw[j].utr) {
                swi(draw[i].utr, draw[j].utr, draw[i].name, draw[j].name);
            }
            cout << draw[i].name << " " << "(" << draw[i].utr << ")" << " vs " << draw[j].name << " " << "(" << draw[j].utr << ") ->   ";
            if ((result(dif, bye)) == true) {
                score(q, w);
                if (bye == 0) {
                    cout << draw[i].name << "(" << draw[i].utr << ")" << " -> " << q << " x " << w << endl;
                }
                else {
                    cout << draw[i].name << "(" << draw[i].utr << ")" << endl;
                }
                if (dif == 0) {
                    update[l].name = draw[j].name;
                    update[l].utr = draw[j].utr;
                    l++;
                    draw[z].name = draw[i].name;
                    draw[z].utr = draw[i].utr + 1;
                    z++;
                }
                else {
                    update[l].name = draw[j].name;
                    update[l].utr = draw[j].utr;
                    l++;
                    draw[z].name = draw[i].name;
                    draw[z].utr = draw[i].utr;
                    z++;
                }
            }
            else {
                score(q, w);
                if (bye == 0) {
                    cout << draw[j].name << "(" << draw[j].utr << ")" << " -> " << q << " x " << w << endl;
                }
                else {
                    cout << draw[j].name << "(" << draw[j].utr << ")" << endl;
                }
                if (dif == 0) {
                    update[l].name = draw[i].name;
                    update[l].utr = draw[i].utr;
                    l++;
                    draw[z].name = draw[j].name;
                    draw[z].utr = draw[j].utr + 1;
                    z++;
                }
                else {
                    update[l].name = draw[i].name;
                    update[l].utr = draw[i].utr - 1;
                    l++;
                    draw[z].name = draw[j].name;
                    draw[z].utr = draw[j].utr + 1;
                    z++;
                }

            }
            j--;
            bye = 0;
        }
        n = n / 2;
        cout << "\n";
        //Print all winners of each round
        cout << "Winner(s):\n";
        for (int i = 0; i < n; i++) {
            cout << draw[i].name << " " << "(" << draw[i].utr << ")" << endl;
        }

        cout << "\n";
    }

    update[l].name = draw[0].name;
    update[l].utr = draw[0].utr;

    //Print all players new UTRs after the tournament
    cout << "New UTR: \n\n";

    sort(update.begin(), update.end(), func);

    for (int i = 0; i < n1; i++) {
        cout << update[i].name << " " << "(" << update[i].utr << ")" << endl;
    }

    return 0;
}
