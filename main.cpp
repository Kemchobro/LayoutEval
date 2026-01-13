#include <iostream>
#include "wall.h"
using namespace std;

int main() {
    float length = 22; // actual max x
    float width  = 20; // actual max y
    float step   = 80;
    float maxDist = 1;

    vector<wall> walls = {
        wall(make_tuple(0,0), make_tuple(0,20), 20, maxDist),
        wall(make_tuple(0,0), make_tuple(22,0), 22, maxDist),
        wall(make_tuple(0,20), make_tuple(22,20), 22, maxDist),
        wall(make_tuple(22,0), make_tuple(22,20), 20, maxDist),

        wall(make_tuple(5,10), make_tuple(7,20), maxDist),
        wall(make_tuple(0,10), make_tuple(5,10), maxDist),
    };

    tuple<int,int> pCO = {0,20};
    tuple<int,int> pCT = {22,0};

    // include +1 so both 0 and boundary are in range
    vector<vector<int>> iP((width+1) * step, vector<int>((length+1) * step));
    vector<vector<int>> iCO((width+1) * step, vector<int>((length+1) * step));
    vector<vector<int>> iCT((width+1) * step, vector<int>((length+1) * step));
    vector<vector<int>> iC((width+1) * step, vector<int>((length+1) * step));
    vector<vector<int>> iF((width+1) * step, vector<int>((length+1) * step));



    // Fill iP
    for (int i = 0; i < iP.size(); i++) {
        for (int j = 0; j < iP[i].size(); j++) {
            for (wall w : walls) {
                iP[i][j] = w.isNearWall(make_tuple(j / step, i / step))
                           ? 1 + iP[i][j] : iP[i][j];
            }
        }
    }

    // // Print iP (from top row down)
    // for (int i = iP.size()-1; i >= 0; i--) {
    //     for (int j = 0; j < iP[i].size(); j++) {
    //         cout << iP[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //
    // cout << "\n\n\n";

    // Fill iCO
    for (int i = 0; i < iCO.size(); i++) {
        for (int j = 0; j < iCO[i].size(); j++) {
            for (wall w : walls) {
                if (!w.isVisible(pCO, make_tuple(j / step, i / step))) {
                    iCO[i][j] = 0;
                    break;
                }
                iCO[i][j] = 1;
            }
        }
    }

    // Fill iCT
    for (int i = 0; i < iCT.size(); i++) {
        for (int j = 0; j < iCT[i].size(); j++) {
            for (wall w : walls) {
                if (!w.isVisible(pCT, make_tuple(j / step, i / step))) {
                    iCT[i][j] = 0;
                    break;
                }
                iCT[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < iC.size(); i++) {
        for (int j = 0; j < iC[i].size(); j++) {
            iC[i][j] = iCO[i][j] + iCT[i][j];
        }
    }

    for (int i = 0; i < iF.size(); i++) {
        for (int j = 0; j < iF[i].size(); j++) {
            iF[i][j] = iC[i][j] * iP[i][j];
        }
    }

    // // Print iCO
    // for (int i = iC.size()-1; i >= 0; i--) {
    //     for (int j = 0; j < iC[i].size(); j++) {
    //         cout << iC[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;

    // for (int i = iF.size()-1; i >= 0; i--) {
    //     for (int j = 0; j < iF[i].size(); j++) {
    //         cout << iF[i][j] << " ";
    //     }
    //     cout << endl;
    //
    // }
    float wallspace = 0;
    for (int i = 0; i < iP.size(); i++) {
        for (int j = 0; j < iP[i].size(); j++) {
            wallspace += iP[i][j];
        }
    }
    float total =0;
    for (int i = 0; i < iF.size(); i++) {
        for (int j = 0; j < iF[i].size(); j++) {
            total += iF[i][j];
        }
    }

    std::cout << "Total Wall: " << wallspace / step / step << std::endl;


    std::cout << "Final Eval: " << total / step / step << std::endl;

    std::cout << "Ratio of Final Eval to Total Wall: " << total / (wallspace * 2) << std::endl;




    return 0;
}


