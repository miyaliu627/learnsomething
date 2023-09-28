//
// Created by Ethan on 9/13/2023.
//

#include <vector>
#include "action.h"

#ifndef LEARNSOMETHING_HACKATHONBOT_H
#define LEARNSOMETHING_HACKATHONBOT_H

class HackathonBot {
public:
    HackathonBot();
    void takeAction(float price);
    double getBalance();
    bool isHolding();
private:
    float purchasePrice;
    double balance;
    bool holding;
    int conseqcycles;
    std::vector<float> priceHistory;
    // std::vector<float> percentChangeHistory;
    bool checkSellConditions(float price);
    bool checkBuyConditions(float price);
};

#endif //LEARNSOMETHING_HACKATHONBOT_H
