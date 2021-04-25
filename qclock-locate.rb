

# Create the symbols table depending on the matrix
# projet qlocktwo

QClock =   <<~EOF
IL#ESTRUNELDIX 
MINUITDEUXSEPT 
QUATREMIDICINQ 
HUIT-TROISNEUF 
SIXONZE*HEURES 
TRENTEQUARANTE 
VINGTCINQUANTE 
DIXQUATRETCINQ 
UNE-TROISSEIZE 
SIXEPILE!DEUXF 
ONZELNEUFCHUIT 
UEDOUZEASEPTUE 
QUATORZETREIZE 
CQUINZEADEGRES 

EOF


Heures = [
    [ "MINUIT"              ],
    [ "UNE",     "HEURE",   ],
    [ "DEUX",    "HEURES",  ],  
    [ "TROIS",   "HEURES",  ], 
    [ "QUATRE",  "HEURES",  ], 
    [ "CINQ",    "HEURES",  ],  
    [ "SIX",     "HEURES",  ], 
    [ "SEPT",    "HEURES",  ], 
    [ "HUIT",    "HEURES",  ],  
    [ "NEUF",    "HEURES",  ], 
    [ "DIX",     "HEURES",  ], 
    [ "ONZE",    "HEURES",  ],
    [ "MIDI"                ],
    [ "UNE",     "HEURE",   ],
    [ "DEUX",    "HEURES",  ],  
    [ "TROIS",   "HEURES",  ], 
    [ "QUATRE",  "HEURES",  ], 
    [ "CINQ",    "HEURES",  ],  
    [ "SIX",     "HEURES",  ], 
    [ "SEPT",    "HEURES",  ], 
    [ "HUIT",    "HEURES",  ],  
    [ "NEUF",    "HEURES",  ],
    [ "DIX",     "HEURES",  ],  
    [ "ONZE",    "HEURES",  ],
]               
Minutes = [
     [   "PILE",                    ],  
     [   "UNE",                     ],  
     [   "DEUX",                    ],  
     [   "TROIS",                   ],  
     [   "QUATRE",                  ],  
     [   "CINQ",                    ],  
     [   "SIX",                     ],  
     [   "SEPT",                    ],  
     [   "HUIT",                    ],  
     [   "NEUF",                    ],  
     [   "DIX",                     ],  
     [   "ONZE",                    ],  
     [   "DOUZE",                   ],  
     [   "TREIZE",                  ],  
     [   "QUATORZE",                ],  
     [   "QUINZE",                  ],  
     [   "SEIZE",                   ],  
     [   "DIX",     "-",  "SEPT",   ],  
     [   "DIX",     "-",  "HUIT",   ],  
     [   "DIX",     "-",  "NEUF",   ],  
     [   "VINGT",                   ],  
     [   "VINGT",   "ET",   "UN",   ],  
     [   "VINGT",   "DEUX",         ],  
     [   "VINGT",   "TROIS",        ],  
     [   "VINGT",   "QUATRE",       ],  
     [   "VINGT",   "CINQ",         ],  
     [   "VINGT",   "SIX",          ],  
     [   "VINGT",   "SEPT",         ],  
     [   "VINGT",   "HUIT",         ],  
     [   "VINGT",   "NEUF",         ],  
     [   "TRENTE",                  ],          
     [   "TRENTE",  "ET",   "UN",   ],  
     [   "TRENTE",  "DEUX",         ],  
     [   "TRENTE",  "TROIS",        ],  
     [   "TRENTE",  "QUATRE",       ],  
     [   "TRENTE",  "CINQ",         ],  
     [   "TRENTE",  "SIX",          ],  
     [   "TRENTE",  "SEPT",         ],  
     [   "TRENTE",  "HUIT",         ],  
     [   "TRENTE",  "NEUF",         ],  
     [   "QUARANTE",                ],  
     [   "QUARANTE","ET",   "UN",   ],  
     [   "QUARANTE","DEUX",         ],  
     [   "QUARANTE","TROIS",        ],  
     [   "QUARANTE","QUATRE",       ],  
     [   "QUARANTE","CINQ",         ],  
     [   "QUARANTE","SIX",          ],  
     [   "QUARANTE","SEPT",         ],  
     [   "QUARANTE","HUIT",         ],  
     [   "QUARANTE","NEUF",         ],  
     [   "CINQUANTE",               ],          
     [   "CINQUANTE","ET",   "UN",  ],  
     [   "CINQUANTE","DEUX",        ],  
     [   "CINQUANTE","TROIS",       ],  
     [   "CINQUANTE","QUATRE",      ],  
     [   "CINQUANTE","CINQ",        ],  
     [   "CINQUANTE","SIX",         ],  
     [   "CINQUANTE","SEPT",        ],  
     [   "CINQUANTE","HUIT",        ],   
     [   "CINQUANTE","NEUF",        ],  
]

# separate Clock into Hours and Minutes
# Due to the wiring, the even lines should be reversed 
hours =""
minutes = ""
QClock.split.each_slice(2).with_index do | (odd, even), idx |
  if idx<2 then
     hours += odd.chomp
     hours += even.chomp.reverse
  elsif idx==2 then
     hours += odd.chomp
     minutes += even.chomp.reverse
  else
     minutes += odd.chomp
     minutes += even.chomp.reverse
  end
end
HOURS = hours
MINUTES = minutes
puts HOURS
puts MINUTES

# search words in the clock: search beginning by replace
# to find Cinq berfore Cinquante
# and cheat for ET
def Text2Words(txt, len, where, offset)
    txt.each do |words|
        print "     {  { " 
        words.each do |word|
          if word=="ET" then
             pos = where.index("TERTAUQ")
          else
             pos = where.index(word.reverse) || where.index(word) 
          end
          print "  {  %3d,  %2d  }, " % [pos+offset, word.length ]
        end
        (len - words.length).times do
           print "  {  %3d,  %2d  }, " % [0, 0 ]
        end
        puts "  }  },  // " + words.join(" ")
    end
end


puts "struct s_Words tHours2Words[] = { "
Text2Words(Heures, 3, HOURS, 0)
puts "};\n\n"

puts "struct s_Words tMinutes2Words[] = { "
Text2Words(Minutes, 3, MINUTES, 5*14)
puts "};\n\n"
