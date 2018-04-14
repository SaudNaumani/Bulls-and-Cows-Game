//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Saud Naumani on 2018-02-27.
//  Copyright © 2018 Saud Naumani. All rights reserved.

#include "FBullCowGame.hpp"
#include <map>
//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor; called when the object is created

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return GameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap <int32, int32> WordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,15}, {7,20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "plane"; //MUST be an isogram
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    GameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) //if the guess isn't an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::Ok;
    }
    
    //otherwise
        //return OK
}

//receives a VALID guess, increments turn, and returns coutn
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

    //loop through all letters in the hidden word
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
        //compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++) {
            //if they match then
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                //if they're in the same place
                if (MHWChar == GChar) {  //increment bulls if they're in the same place
                    BullCowCount.Bulls++;
                }
                else {
                    BullCowCount.Cows++; //must be a cow
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        GameIsWon = true;
    }
    else {
        GameIsWon = false;
    }
    return BullCowCount;
}

void FBullCowGame::PrintGameSummary()
{
    if (GameIsWon) {
        std::cout << "WELL DONE - YOU WIN\n";
    }
    else {
        std::cout << "Better Luck Next Time!\n";
    }
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    //treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }
    
    TMap <char, bool> LetterSeen; //setup our map
    for (auto Letter : Word)//Letter is a variable which is used to step through each of the characters in Word
    {
        Letter = tolower(Letter); //store and retrieve only lower cased letters
        
        if (LetterSeen[Letter]) //if the letter is in the map
            return false; //we do NOT have an isogram
        else
            LetterSeen[Letter] = true; //add the letter to the map as seen
    }
    return true; //for example in cases where \0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter)) //if not a lowercase letter
            return false;
    }
    return true;
}
