#ifndef _NOTE_PLAYER_HPP
#define _NOTE_PLAYER_HPP

#include "note.hpp"

class note_player {
public:   
   virtual void play( const note & n ) = 0;
};

# endif