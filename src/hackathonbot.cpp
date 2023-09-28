//
// Created by Ethan on 9/13/2023.
//

#include <vector>
#include "hackathonbot.h"

HackathonBot::HackathonBot() :purchasePrice(100.0), balance(0.0), holding(false), conseqcycles(0) {
    priceHistory.reserve(52); // Initialize the price history vector with a capacity of 52
    priceHistory.push_back(100.0); //push back the initial cost of a stock
    // percentChangeHistory.reserve(52);
}


void HackathonBot::takeAction(float price) {
    if (holding) {
        if (checkSellConditions(price)) {
            // Sell the stock
            this->balance += price;
            this->holding = false;
            this->purchasePrice = 0.0;
            this->conseqcycles = 0;
            this->priceHistory.clear(); // Clear price history after selling
            // this->percentChangeHistory.clear(); //clear percent change history after selling
        }
    } else {
        if (checkBuyConditions(price)) {
            // Buy the stock
            this->balance -= price;
            this->holding = true;
            this->purchasePrice = price;
            this->priceHistory.clear(); // Clear price history after buying
            // this->percentChangeHistory.clear(); //clear percent change history after buying
        }
    }

    this->priceHistory.push_back(price);
}

 
double HackathonBot::getBalance() {
    return this->balance;
}

bool HackathonBot::isHolding() {
    return this->holding;
}

bool HackathonBot::checkSellConditions(float price) {
    float pricediff = price - this->priceHistory.back();
    // this->percentChangeHistory.push_back(pricediff/this->priceHistory.back()); //positive if price raised, negative if dropped

    // Check rule: If the stock goes up in price for 52 windows, sell
    if (pricediff == 52) {
        return true;
    }

    // Check rule: If the stock goes down in price for 47 windows, sell
    if (pricediff == -47) {
        return true;
    }


    // check rule: If the stock drops by over 62% from the purchase price, sell
    if ((this->purchasePrice - price) / this->purchasePrice > 0.62) {
        return true;
    }

    // check rule: If the stock raises by over 89% from the purchase price, sell
    if ((price - this->purchasePrice) / this->purchasePrice > 0.89) {
        return true;
    }

    // check rule: pattern 1 (up 20%, drop 15%, up 30% and overall change )
    if (priceHistory.size() >= 3) {
        float lastPrice = priceHistory[priceHistory.size() - 1];
        float secondLastPrice = priceHistory[priceHistory.size() - 2];
        float thirdLastPrice = priceHistory[priceHistory.size() - 3];

        // Calculate percent changes
        float percentChange1 = (price - lastPrice) / lastPrice;
        float percentChange2 = (lastPrice - secondLastPrice) / secondLastPrice;
        float percentChange3 = (secondLastPrice - thirdLastPrice) / thirdLastPrice;

        // Check conditions
        if (percentChange1 >= 0.20 && percentChange2 <= -0.15 && percentChange3 >= 0.30) {
            // Calculate the percent change in the 3-series window
            float percentChangeWindow = (price - thirdLastPrice) / thirdLastPrice;
            
            // Check if the percent change in the 3-series window is up by >= 50%
            if (percentChangeWindow >= 0.50) {
                return true;
            }
        }
        else if (percentChange1 <= -0.15 && percentChange2 >= 0.15 && percentChange3 >= -0.25) {
            // Calculate the percent change in the 3-series window
            float percentChangeWindow = (price - thirdLastPrice) / thirdLastPrice;
            
            // Check if the percent change in the 3-series window is up by >= 50%
            if (percentChangeWindow >= -0.45) {
                return true;
            }
        }

    }

    // add to the consecutive cycles where the percent change is within the 5 percent range
    if (std::abs(pricediff)/this->priceHistory.back() <= 5) {
        this->conseqcycles++;
    }
    else {
        this->conseqcycles = 0;
    }

    // check rule: If stock stays +-5% for 10 cycles (after buying)
    if (this->conseqcycles == 10) {
        //loop through the most recent 10 prices
        //keep a variable on 
        return true;
    }
    

    return false;
}

bool HackathonBot::checkBuyConditions(float price) {
    // check rule: If the stock price is less than 52
    if (price < 52) {
        return true;
    }

    if (this->priceHistory.size() >= 0) { //!!!need to check if the price sold counts too
        // Check rule: If the stock drops in price for 5 windows (after selling)
        if (this->priceHistory.back() - price == 5) {
            return true;
        }
    }

    return false;
}




