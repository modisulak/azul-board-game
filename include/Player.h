#ifndef APT_A2_PLAYER_H
#define APT_A2_PLAYER_H

#include "main.h"

class Player { 
    public:
      
      Player(string name, int score);

      Player(const Player &other);

      ~Player();

      /**
      * Get the player name.
      */
      string getName();

      /**
       * Get the player score.
       */
      int getScore(); 
      
      /**
       * Set the player score.
       */
      void setScore(int score); 

    private:
      
      string name;
      int score; 
       
};



#endif //APT_A2_PLAYER_H