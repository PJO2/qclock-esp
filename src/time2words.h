// ---------------------------------------------------------
// time2words: 
// translate hour and minutes to a set of position and length
// ---------------------------------------------------------


#define SizeOfTab(x) ( sizeof (x) / sizeof(x[0]) )
typedef unsigned char byte;

// typedef unsigned char byte;

// for each hour return the list of symbols to display 
struct s_Word {
       byte   pos;
       byte   len;
};


struct s_Words {
   struct s_Word  ledword[6];   // mapping for display routines [5 words are enough for time...]
};


struct s_Words * time2words (struct s_Words *pWords, int hours, int minutes);
