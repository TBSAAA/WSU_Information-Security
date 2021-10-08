//
// Created by Jack Huang on 17/8/21.
//

#ifndef CODE_S_DES_H
#define CODE_S_DES_H

#define Cipher_Num 8
#define Plaint_Num 8
#define Key_Num 10

static bool k1[8], k2[8];

enum {
    encrypt, decrypt
};

int IP[]{2,6,3,1,4,8,5,7};

int IP_1[]{4,1,3,5,7,2,8,6};

int P10[]{3,5,2,7,4,10,1,9,8,6};

int P8[]{6,3,7,4,8,5,10,9};

int E_P[]{4,1,2,3,2,3,4,1};

int P4[]{2,4,3,1};

int S0[4][4]{
        {1,0,3,2},
        {3,2,1,0},
        {0,2,1,3},
        {3,1,3,2}
};

int S1[4][4]{
        {0,1,2,3},
        {2,0,1,3},
        {3,0,1,0},
        {2,1,0,3}
};




#endif //CODE_S_DES_H
