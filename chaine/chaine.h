//
// Created by michael on 19/03/25.
//
#pragma once
#ifndef CHAINE_H
#define CHAINE_H

#include "../tools/tools.h"
#include <iostream>
#include <vector>

class Chaine {
public:
    Chaine();
    Chaine(std::vector<S2d>);

    ~Chaine();

    void chaine_clear();
    void chaine_pop();
    void chaine_push(S2d);
    void chaine_set(std::vector<S2d>);
    int chaine_size();


private:
    std::vector<S2d> articulations;

};

#endif //CHAINE_H
