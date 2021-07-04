// --------------------------------------------------------------
// time2words.c
// 
// display the time in a readable form (french) and reasonnable computation
// the output is processed in two steps
//    - hours are translated using tHourCodes data (the hour is the implicit index of the structure)
//    - minutes are translated using tMinutesCodes data (with minutes as index)
// The data have been produced by an external Ruby script
// -------------------------------------------------------------

#include "time2words.h"

struct s_HourWords {
   struct s_Word  ledword[3];   // translate hours to natural language
};
struct s_MinuteWords {
   struct s_Word  ledword[3];   // translate minutes to natural language
};

struct s_Words tHours2Words[] = { 
     {  {   {   22,   6  },   {    0,   0  },   {    0,   0  },   }  },  // MINUIT
     {  {   {    7,   3  },   {   64,   5  },   {    0,   0  },   }  },  // UNE HEURE
     {  {   {   18,   4  },   {   64,   6  },   {    0,   0  },   }  },  // DEUX HEURES
     {  {   {   46,   5  },   {   64,   6  },   {    0,   0  },   }  },  // TROIS HEURES
     {  {   {   28,   6  },   {   64,   6  },   {    0,   0  },   }  },  // QUATRE HEURES
     {  {   {   38,   4  },   {   64,   6  },   {    0,   0  },   }  },  // CINQ HEURES
     {  {   {   56,   3  },   {   64,   6  },   {    0,   0  },   }  },  // SIX HEURES
     {  {   {   14,   4  },   {   64,   6  },   {    0,   0  },   }  },  // SEPT HEURES
     {  {   {   52,   4  },   {   64,   6  },   {    0,   0  },   }  },  // HUIT HEURES
     {  {   {   42,   4  },   {   64,   6  },   {    0,   0  },   }  },  // NEUF HEURES
     {  {   {   11,   3  },   {   64,   6  },   {    0,   0  },   }  },  // DIX HEURES
     {  {   {   59,   4  },   {   64,   6  },   {    0,   0  },   }  },  // ONZE HEURES
     {  {   {   34,   4  },   {    0,   0  },   {    0,   0  },   }  },  // MIDI
     {  {   {    7,   3  },   {   64,   5  },   {    0,   0  },   }  },  // UNE HEURE
     {  {   {   18,   4  },   {   64,   6  },   {    0,   0  },   }  },  // DEUX HEURES
     {  {   {   46,   5  },   {   64,   6  },   {    0,   0  },   }  },  // TROIS HEURES
     {  {   {   28,   6  },   {   64,   6  },   {    0,   0  },   }  },  // QUATRE HEURES
     {  {   {   38,   4  },   {   64,   6  },   {    0,   0  },   }  },  // CINQ HEURES
     {  {   {   56,   3  },   {   64,   6  },   {    0,   0  },   }  },  // SIX HEURES
     {  {   {   14,   4  },   {   64,   6  },   {    0,   0  },   }  },  // SEPT HEURES
     {  {   {   52,   4  },   {   64,   6  },   {    0,   0  },   }  },  // HUIT HEURES
     {  {   {   42,   4  },   {   64,   6  },   {    0,   0  },   }  },  // NEUF HEURES
     {  {   {   11,   3  },   {   64,   6  },   {    0,   0  },   }  },  // DIX HEURES
     {  {   {   59,   4  },   {   64,   6  },   {    0,   0  },   }  },  // ONZE HEURES
};

struct s_Words tMinutes2Words[] = { 
     {  {   {  132,   4  },   {    0,   0  },   {    0,   0  },   }  },  // PILE
     {  {   {  112,   3  },   {    0,   0  },   {    0,   0  },   }  },  // UNE
     {  {   {  127,   4  },   {    0,   0  },   {    0,   0  },   }  },  // DEUX
     {  {   {  116,   5  },   {    0,   0  },   {    0,   0  },   }  },  // TROIS
     {  {   {  103,   6  },   {    0,   0  },   {    0,   0  },   }  },  // QUATRE
     {  {   {   98,   4  },   {    0,   0  },   {    0,   0  },   }  },  // CINQ
     {  {   {  137,   3  },   {    0,   0  },   {    0,   0  },   }  },  // SIX
     {  {   {  156,   4  },   {    0,   0  },   {    0,   0  },   }  },  // SEPT
     {  {   {  150,   4  },   {    0,   0  },   {    0,   0  },   }  },  // HUIT
     {  {   {  145,   4  },   {    0,   0  },   {    0,   0  },   }  },  // NEUF
     {  {   {  109,   3  },   {    0,   0  },   {    0,   0  },   }  },  // DIX
     {  {   {  140,   4  },   {    0,   0  },   {    0,   0  },   }  },  // ONZE
     {  {   {  161,   5  },   {    0,   0  },   {    0,   0  },   }  },  // DOUZE
     {  {   {  176,   6  },   {    0,   0  },   {    0,   0  },   }  },  // TREIZE
     {  {   {  168,   8  },   {    0,   0  },   {    0,   0  },   }  },  // QUATORZE
     {  {   {  189,   6  },   {    0,   0  },   {    0,   0  },   }  },  // QUINZE
     {  {   {  121,   5  },   {    0,   0  },   {    0,   0  },   }  },  // SEIZE
     {  {   {  109,   3  },   {  115,   1  },   {  156,   4  },   }  },  // DIX - SEPT
     {  {   {  109,   3  },   {  115,   1  },   {  150,   4  },   }  },  // DIX - HUIT
     {  {   {  109,   3  },   {  115,   1  },   {  145,   4  },   }  },  // DIX - NEUF
     {  {   {   84,   5  },   {    0,   0  },   {    0,   0  },   }  },  // VINGT
     {  {   {   84,   5  },   {  102,   2  },   {  112,   2  },   }  },  // VINGT ET UN
     {  {   {   84,   5  },   {  127,   4  },   {    0,   0  },   }  },  // VINGT DEUX
     {  {   {   84,   5  },   {  116,   5  },   {    0,   0  },   }  },  // VINGT TROIS
     {  {   {   84,   5  },   {  103,   6  },   {    0,   0  },   }  },  // VINGT QUATRE
     {  {   {   84,   5  },   {   98,   4  },   {    0,   0  },   }  },  // VINGT CINQ
     {  {   {   84,   5  },   {  137,   3  },   {    0,   0  },   }  },  // VINGT SIX
     {  {   {   84,   5  },   {  156,   4  },   {    0,   0  },   }  },  // VINGT SEPT
     {  {   {   84,   5  },   {  150,   4  },   {    0,   0  },   }  },  // VINGT HUIT
     {  {   {   84,   5  },   {  145,   4  },   {    0,   0  },   }  },  // VINGT NEUF
     {  {   {   78,   6  },   {    0,   0  },   {    0,   0  },   }  },  // TRENTE
     {  {   {   78,   6  },   {  102,   2  },   {  112,   2  },   }  },  // TRENTE ET UN
     {  {   {   78,   6  },   {  127,   4  },   {    0,   0  },   }  },  // TRENTE DEUX
     {  {   {   78,   6  },   {  116,   5  },   {    0,   0  },   }  },  // TRENTE TROIS
     {  {   {   78,   6  },   {  103,   6  },   {    0,   0  },   }  },  // TRENTE QUATRE
     {  {   {   78,   6  },   {   98,   4  },   {    0,   0  },   }  },  // TRENTE CINQ
     {  {   {   78,   6  },   {  137,   3  },   {    0,   0  },   }  },  // TRENTE SIX
     {  {   {   78,   6  },   {  156,   4  },   {    0,   0  },   }  },  // TRENTE SEPT
     {  {   {   78,   6  },   {  150,   4  },   {    0,   0  },   }  },  // TRENTE HUIT
     {  {   {   78,   6  },   {  145,   4  },   {    0,   0  },   }  },  // TRENTE NEUF
     {  {   {   70,   8  },   {    0,   0  },   {    0,   0  },   }  },  // QUARANTE
     {  {   {   70,   8  },   {  102,   2  },   {  112,   2  },   }  },  // QUARANTE ET UN
     {  {   {   70,   8  },   {  127,   4  },   {    0,   0  },   }  },  // QUARANTE DEUX
     {  {   {   70,   8  },   {  116,   5  },   {    0,   0  },   }  },  // QUARANTE TROIS
     {  {   {   70,   8  },   {  103,   6  },   {    0,   0  },   }  },  // QUARANTE QUATRE
     {  {   {   70,   8  },   {   98,   4  },   {    0,   0  },   }  },  // QUARANTE CINQ
     {  {   {   70,   8  },   {  137,   3  },   {    0,   0  },   }  },  // QUARANTE SIX
     {  {   {   70,   8  },   {  156,   4  },   {    0,   0  },   }  },  // QUARANTE SEPT
     {  {   {   70,   8  },   {  150,   4  },   {    0,   0  },   }  },  // QUARANTE HUIT
     {  {   {   70,   8  },   {  145,   4  },   {    0,   0  },   }  },  // QUARANTE NEUF
     {  {   {   89,   9  },   {    0,   0  },   {    0,   0  },   }  },  // CINQUANTE
     {  {   {   89,   9  },   {  102,   2  },   {  112,   2  },   }  },  // CINQUANTE ET UN
     {  {   {   89,   9  },   {  127,   4  },   {    0,   0  },   }  },  // CINQUANTE DEUX
     {  {   {   89,   9  },   {  116,   5  },   {    0,   0  },   }  },  // CINQUANTE TROIS
     {  {   {   89,   9  },   {  103,   6  },   {    0,   0  },   }  },  // CINQUANTE QUATRE
     {  {   {   89,   9  },   {   98,   4  },   {    0,   0  },   }  },  // CINQUANTE CINQ
     {  {   {   89,   9  },   {  137,   3  },   {    0,   0  },   }  },  // CINQUANTE SIX
     {  {   {   89,   9  },   {  156,   4  },   {    0,   0  },   }  },  // CINQUANTE SEPT
     {  {   {   89,   9  },   {  150,   4  },   {    0,   0  },   }  },  // CINQUANTE HUIT
     {  {   {   89,   9  },   {  145,   4  },   {    0,   0  },   }  },  // CINQUANTE NEUF
};



// retrieve the pos and length of the words to be displayed 
// according to the given time 
// if data are out of bounds, 0,0 is returned
struct s_Words * time2words (struct s_Words *pWords, int hours, int minutes)
{
struct s_Word *pword = pWords->ledword;  // points on the first word
  // translate hours to word
  if (hours>=0 && hours < 24)
      for (int ark=0 ;  
               ark<SizeOfTab(tHours2Words[0].ledword) && tHours2Words[hours].ledword[ark].len>0 ; 
               ark++)      
          *pword++ = tHours2Words[hours].ledword[ark];
  
  // add translated minutes 
  if (minutes>=0 && minutes < 60)
      for (int ark=0 ;  
               ark<SizeOfTab(tMinutes2Words[0].ledword) && tMinutes2Words[minutes].ledword[ark].len>0 ; 
               ark++)      
          *pword++ = tMinutes2Words[minutes].ledword[ark];
  
  // set length to 0 for other words 
  for ( ; pword < (pWords+1)->ledword ; pword++)
     pword->len = 0;
return pWords;
} // time2words


/* ----------------------------
 *  Test
 * ----------------------------
#include <stdio.h>
int main(void) {
struct s_Words W;
  time2words (&W, 13, 51);
  for (int ark=0 ; ark<6 ; ark++)
    printf ("%d %d\n", W.word[ark].pos, W.word[ark].len );
  return 0;
}
 */
 
