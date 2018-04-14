//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Saud Naumani on 2018-02-27.
//  Copyright © 2018 Saud Naumani. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <iostream>

#endif /* FBullCowGame_hpp */

using FString = std::string;
using int32 = int;

//all values initialized to zero
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    Ok,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    
    void PrintGameSummary();
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset(); //TODO make a more rich return back
    //counts bulls & cows, and increases try # assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
private:
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    
    //See constructor for initialization
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool GameIsWon;
};






