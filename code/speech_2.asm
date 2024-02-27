    ORG 0000H

DICT:   DW  (LUTEND/2)-1
        ; INDEX 1 .. 7
        DW  MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY

        ; INDEX 8 .. 19        
        DW  JANUARY,FEBRUARY,MARCH,APRIL,MAY,JUNE,JULY
        DW  AUGUST,SEPTEMBER,OCTOBER,NOVEMBER,DECEMBER
        
        ; INDEX 20
        DW  ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
		
		; INDEX 30
		DW  TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN, SIXTEEN, SEVENTEEN, EIGHTEEN, NINETEEN
		
		; INDEX 40
		DW	TWENTY, THIRTY, FOURTY, FIFTY, SIXTY, SEVENTY, EIGHTY, NINTY, HUNDRED, THOUSAND
		
		; INDEX 50
        DW  MILLION

		; INDEX 51
        DW  ALARM,BATHE,BATHER,BATHING,BEER,BREAD,BY,CALENDAR,CLOCK
		
		; INDEX 60
		DW	CLOWN,CHECK,CHECKED,CHECKER,CHECKERS,CHECKING,CHECKS, COGNITIVE,COLLIDE,COMPUTER
		
		; INDEX 70
		DW	COOKIE,COOP,CORRECT,CORRECTED,CORRECTING,CORRECTS,CROWN,DATE,DAUGHTER,DAY
		
		; INDEX 80
		DW	DIVIDED,EMOTIONAL,ENGAGE,ENGAGEMENT,ENGAGES,ENGAGING,ENRAGE,ENRAGED,ENRAGES,ENRAGING
		
		; INDEX 90
		DW	ESCAPE,ESCAPED,ESCAPES,ESCAPING,EQUAL,EQUALS,ERROR,EXTENT,FIR,FREEZE
		
		; INDEX 100
		DW	FREEZER,FREEZERS,FREEZING,FROZEN,GAUGE,GUAGED,GUAGER,GUAGING,HELLO,HOUR
		
		; INDEX 110
		DW	INFINITIVE,INTRIGUE,INTRIGUED,INTRIGUES,INTRIGUING,INVESTIGATE,INVESTIGATED,INVESTIGATOR,INVESTIGATORS,INVESTIGATES
		
		; INDEX 120
		DW	INVESTIGATING,KEY,LEGISLATE,LEGISLATED,LEGISLATES,LEGISLATING,LEGISLATURE,LETTER,LITTER,LITTLE
		
		; INDEX 130
		DW	MEMORY,MEMORIES,MINUTE,MONTH,NIP,NIPPED,NIPPING,NIPS,NO,PHYSICAL
		
		; INDEX 140
		DW	PIN,PINNED,PINNING,PINS,PLEDGE,PLEDGED,PLEDGES,PLEDGING,PLUS,RAY
		
		; INDEX 150
		DW	RAYS,READY,RED,ROBOT,ROBOLS,SCORE,SECOND,SENSITIVE,SENSITIVITY,SINCERE
		
		; INDEX 160
		DW	SINCERELY,SINCERITY,SISTER,SPEAK,SPELL,SPELLED,SPELLER,SPELLERS,SPELLING,SPELLS
		
		; INDEX 170
		DW	START,STARTED,STARTER,STARTING,STARTS,STOP,STOPPED,STOPPER,STOPPING,STOPS
		
		; INDEX 180
		DW	SUBJECT_N,SUBJECT_V,SWEAT,SWEATED,SWEATER,SWEATERS,SWEATING,SWEATS,SWITCH,SWITCHED
		
		; INDEX 190
		DW	SWITCHES,SWITCHING,SYSTEM,SYSTEMS,TALK,TALKED,TALKER,TALKERS,TALKING,TALKS
		
		; INDEX 200
		DW	THREAD,THREADED,THREADER,THREADERS,THREADING,THREADS,THEN,TIME,TIMES,UNCLE
		
		; INDEX 210
		DW	WHALE,WHALER,WHALERS,WHALES,WHALING,YEAR,YES
		
LUTEND:
;====================================================================
; These are the sequences of allophones needed to create the sound
; of each individual word. Make sure to end each sequence with 0xFF
;====================================================================

; DAYS OF THE WEEK
MONDAY:		DB	PA2,MM,AX,NN1,PA2,DD2,EY,PA1,0xFF
TUESDAY:	DB	PA2,TT2,UW2,ZZ,PA2,DD2,EY,PA1,0xFF
WEDNESDAY:	DB	PA2,WW,EH,EH,NN1,ZZ,PA2,DD2,EY,PA1,0xFF
THURSDAY:	DB	PA2,TH,ER2,ZZ,PA2,DD2,EY,PA1,0xFF
FRIDAY:		DB	PA2,FF,RR2,AY,PA3,DD2,EY,PA1,0xFF
SATURDAY:	DB	PA2,SS,SS,AE,PA3,TT2,ER1,PA2,DD2,EY,PA1,0xFF
SUNDAY:		DB	PA2,SS,SS,AX,AX,NN1,PA2,DD2,EY,PA1,0xFF

; MONTHS
JANUARY:    DB  PA2,JH,AE,NN1,YY2,XR,IY,PA1,0xFF
FEBRUARY:   DB  PA2,FF,EH,EH,PA1,BB2,RR2,UW2,XR,IY,PA1,0xFF
MARCH:      DB  PA2,MM,AR,PA3,CH,PA1,0xFF
APRIL:      DB  PA2,EY,PA3,PP,RR2,IH,IH,LL,PA1,0xFF
MAY:        DB  PA2,MM,EY,PA1,0xFF
JUNE:       DB  PA2,JH,UW2,NN1,PA1,0xFF
JULY:       DB  PA2,JH,UW1,LL,AY,PA1,0xFF
AUGUST:     DB  PA2,AO,AO,PA2,GG2,AX,SS,PA3,TT1,PA1,0xFF
SEPTEMBER:  DB  PA2,SS,SS,EH,PA3,PP,PA3,TT2,EH,EH,MM,BB1,ER1,PA1,0xFF
OCTOBER:    DB  PA2,AO,PA2,KK2,PA3,TT2,OW,PA1,BB2,ER1,PA1,0xFF
NOVEMBER:   DB  PA2,NN2,OW,VV,EH,EH,MM,PA1,BB2,ER1,PA1,0xFF
DECEMBER:   DB  PA2,DD2,IH,SS,SS,EH,EH,MM,PA1,BB2,ER1,PA1,0xFF

; NUMBERS
ZERO:		DB	PA2,ZZ,YR,OW,PA1,0xFF
ONE:		DB	PA2,WW,AX,NN1,PA1,0xFF
TWO:		DB	PA2,TT2,UW2,PA1,0xFF
THREE:		DB	PA2,TH,RR1,IY,PA1,0xFF
FOUR:		DB	PA2,FF,FF,OR,PA1,0xFF
FIVE:		DB	PA2,FF,AY,VV,PA1,0xFF
SIX:		DB	PA2,SS,SS,IH,PA3,KK2,SS,PA1,0xFF
SEVEN:		DB	PA2,SS,SS,EH,VV,IH,NN1,PA1,0xFF
EIGHT:		DB	PA2,EY,PA3,TT2,PA1,0xFF
NINE:		DB	PA2,NN2,AY,PA1,NN2,PA1,0xFF
TEN:		DB	PA2,TT2,PA1,EH,EH,NN1,PA1,0xFF
ELEVEN:		DB	PA2,IH,LL,EH,EH,VV,EH,NN1,PA1,0xFF
TWELVE:		DB	PA2,TT2,WH,EH,LL,VV,PA3,0xFF
THIRTEEN:	DB	PA2,TH,ER1,PA2,PA3,TT2,IY,NN1,PA1,0xFF
FOURTEEN:	DB	PA2,FF,OR,PA2,TT2,IY,PA2,NN1,PA1,0xFF
FIFTEEN:	DB	PA2,FF,IH,FF,PA2,PA3,TT2,IY,NN1,PA1,0xFF
SIXTEEN:	DB	PA2,SS,SS,IH,PA3,KK2,SS,PA2,PA3,TT2,IY,NN1,PA1,0xFF
SEVENTEEN:	DB	PA2,SS,SS,EH,VV,IH,NN1,PA2,PA3,TT2,IY,NN1,PA1,0xFF
EIGHTEEN:	DB	PA2,EY,PA2,PA3,TT2,IY,NN1,PA1,0xFF
NINETEEN:	DB	PA2,NN2,AY,NN1,PA3,TT2,IY,NN1,PA1,0xFF
TWENTY:		DB	PA2,TT2,WH,EH,NN1,PA2,PA3,TT2,IY,PA1,0xFF
THIRTY:		DB	PA2,TH,ER2,PA2,PA3,TT2,IY,PA1,0xFF
FOURTY:		DB	PA2,FF,OR,PA3,TT2,IY,PA1,0xFF
FIFTY:		DB	PA2,FF,IH,FF,PA2,PA3,TT2,IY,PA1,0xFF
SIXTY:		DB	PA2,SS,SS,IH,PA3,KK2,SS,PA2,PA3,TT2,IY,PA1,0xFF
SEVENTY:	DB	PA2,SS,SS,EH,VV,IH,NN1,PA2,PA3,TT2,IY,PA1,0xFF
EIGHTY:		DB	PA2,EY,PA3,TT2,IY,PA1,0xFF
NINTY:		DB	PA2,NN2,PA1,AY,NN1,PA3,TT2,IY,PA1,0xFF
HUNDRED:	DB	PA2,HH2,AX,AX,NN1,PA2,DD2,RR2,EH,PA2,DD2,PA1,0xFF
THOUSAND:   DB  PA2,TH,AA,AW,ZZ,AE,PA1,PA1,NN1,DD2,PA1,0xFF
MILLION:    DB  PA2,MM,IH,IH,LL,IH,PA2,YY1,AX,NN1,PA1,0xFF

;DICTIONARY
ALARM:      	DB  AX,LL,AR,MM,PA1,0xFF
BATHE:     		DB  BB2,EY,DH2,PA1,0xFF
BATHER:     	DB  BB2,EY,DH2,ER1,PA1,0xFF
BATHING:    	DB  BB2,EY,DH2,IH,NG,PA1,0xFF
BEER:       	DB  BB2,YR,PA1,0xFF
BREAD:      	DB  BB1,RR2,EH,EH,PA1,DD1,PA1,0xFF
BY:         	DB  BB2,AA,AY,PA1,0xFF
CALENDAR:   	DB  KK1,AE,AE,LL,EH,NN1,PA2,DD2,ER1,PA1,0xFF
CLOCK:      	DB  KK1,LL,AA,AA,PA3,KK2,PA1,0xFF
CLOWN:      	DB  KK1,LL,AW,NN1,PA1,0xFF
CHECK:      	DB  CH,EH,EH,PA3,KK2,PA1,0xFF
CHECKED:    	DB  CH,EH,EH,PA3,KK2,PA2,TT2,PA1,0xFF
CHECKER:    	DB  CH,EH,EH,PA3,KK1,ER1,PA1,0xFF
CHECKERS:   	DB  CH,EH,EH,PA3,KK1,ER1,ZZ,PA1,0xFF
CHECKING:   	DB  CH,EH,EH,PA3,KK1,IH,NG,PA1,0xFF
CHECKS:			DB	CH,EH,EH,PA3,KK1,SS,PA1,0xFF
COGNITIVE:		DB	KK3,AA,AA,GG3,NN1,IH,PA3,TT2,IH,VV,PA1,0xFF
COLLIDE:		DB	KK3,AX,LL,AY,DD1,PA1,0xFF
COMPUTER:		DB	KK1,AX,MM,PP,YY1,UW1,TT2,ER1,PA1,0xFF
COOKIE:			DB	KK3,UH,KK1,IY,PA1,0xFF
COOP:			DB	KK3,UW2,PA3,PP,PA1,0xFF
CORRECT:		DB	KK1,ER2,EH,EH,PA2,KK2,PA2,TT1,PA1,0xFF
CORRECTED:		DB	KK1,ER2,EH,EH,PA2,KK2,PA2,TT2,IH,PA2,DD1,PA1,0xFF
CORRECTING:		DB	KK1,ER2,EH,EH,PA2,KK2,PA2,TT2,IH,NG,PA1,0xFF
CORRECTS:		DB	KK1,ER2,EH,EH,PA2,KK2,PA2,TT1,SS,PA1,0xFF
CROWN:			DB	KK1,RR2,AW,NN1,PA1,0xFF
DATE:			DB	DD2,EY,PA3,TT2,PA1,0xFF
DAUGHTER:		DB	DD2,AO,TT2,ER1,PA1,0xFF
DAY:			DB	DD2,EH,EY,PA1,0xFF
DIVIDED:		DB	DD2,IH,VV,AY,PA2,DD2,IH,PA2,DD1,PA1,0xFF
EMOTIONAL:		DB	IY,MM,OW,SH,AX,NN1,AX,EL,PA1,0xFF
ENGAGE:			DB	EH,EH,PA1,NN1,GG1,EY,PA2,JH,PA1,0xFF
ENGAGEMENT:		DB	EH,EH,PA1,NN1,GG1,EY,PA2,JH,MM,EH,EH,NN1,PA2,PA3,TT2,PA1,0xFF
ENGAGES:		DB	EH,EH,PA1,NN1,GG1,EY,PA2,JH,IH,ZZ,PA1,0xFF
ENGAGING:		DB	EH,EH,PA1,NN1,GG1,EY,PA2,JH,IH,NG,PA1,0xFF
ENRAGE:			DB	EH,NN1,RR1,EY,PA2,JH,PA1,0xFF
ENRAGED:		DB	EH,NN1,RR1,EY,PA2,JH,PA2,DD1,PA1,0xFF
ENRAGES:		DB	EH,NN1,RR1,EY,PA2,JH,IH,ZZ,PA1,0xFF
ENRAGING:		DB	EH,NN1,RR1,EY,PA2,JH,IH,NG,PA1,0xFF
ESCAPE:			DB	EH,SS,SS,PA3,KK1,PA2,PA3,PP,PA1,0xFF
ESCAPED:		DB	EH,SS,SS,PA3,KK1,PA2,PA3,PP,PA2,TT2,PA1,0xFF
ESCAPES:		DB	EH,SS,SS,PA3,KK1,PA2,PA3,PP,SS,PA1,0xFF
ESCAPING:		DB	EH,SS,SS,PA3,KK1,PA2,PA3,PP,IH,NG,PA1,0xFF
EQUAL:			DB	IY,PA2,PA3,KK3,WH,AX,EL,PA1,0xFF
EQUALS:			DB	IY,PA2,PA3,KK3,WH,AX,EL,ZZ,PA1,0xFF
ERROR:			DB	EH,XR,OR,PA1,0xFF
EXTENT:			DB	EH,KK1,SS,TT2,EH,EH,NN1,TT2,PA1,0xFF
FIR:			DB	FF,ER2,PA1,0xFF
FREEZE:			DB	FF,FF,RR1,IY,ZZ,PA1,0xFF
FREEZER:		DB	FF,FF,RR1,IY,ZZ,ER1,PA1,0xFF
FREEZERS:		DB	FF,FF,RR1,IY,ZZ,ER1,ZZ,PA1,0xFF
FREEZING:		DB	FF,FF,RR1,IY,ZZ,IH,NG,PA1,0xFF
FROZEN:			DB	FF,FF,RR1,OW,ZZ,EH,NN1,PA1,0xFF
GAUGE:			DB	GG1,EY,PA2,JH,PA1,0xFF
GUAGED:			DB	GG1,EY,PA2,JH,PA2,DD1,PA1,0xFF
GUAGER:			DB	GG1,EY,PA2,JH,IH,ZZ,PA1,0xFF
GUAGING:		DB	GG1,EY,PA2,JH,IH,NG,PA1,0xFF
HELLO:			DB	AA,EH,LL,AX,OW,PA1,0xFF
HOUR:			DB	AW,ER1,PA1,0xFF
INFINITIVE:		DB	IH,NN1,FF,FF,IH,IH,NN1,IH,PA2,PA3,TT2,IH,VV,PA1,0xFF
INTRIGUE:		DB	IH,NN1,PA3,TT2,RR2,IY,PA1,GG3,PA1,0xFF
INTRIGUED:		DB	IH,NN1,PA3,TT2,RR2,IY,PA1,GG3,PA2,DD1,PA1,0xFF
INTRIGUES:		DB	IH,NN1,PA3,TT2,RR2,IY,PA1,GG3,ZZ,PA1,0xFF
INTRIGUING:		DB	IH,NN1,PA3,TT2,RR2,IY,PA1,GG3,IH,NG,PA1,0xFF
INVESTIGATE:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT2,PA1,0xFF
INVESTIGATED:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT2,IH,PA2,DD1,PA1,0xFF
INVESTIGATOR:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT2,ER1,PA1,0xFF
INVESTIGATORS:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT2,ER1,ZZ,PA1,0xFF
INVESTIGATES:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT1,SS,PA1,0xFF
INVESTIGATING:	DB	IH,IH,NN1,VV,EH,EH,SS,PA2,PA3,TT2,IH,PA1,GG1,EY,PA2,TT2,IH,NG,PA1,0xFF
KEY:			DB	KK1,IY,PA1,0xFF
LEGISLATE:		DB	LL,EH,EH,PA2,JH,JH,SS,SS,LL,EY,PA2,PA3,TT2,PA1,0xFF
LEGISLATED:		DB	LL,EH,EH,PA2,JH,JH,SS,SS,LL,EY,PA2,PA3,TT2,IH,DD1,PA1,0xFF
LEGISLATES:		DB	LL,EH,EH,PA2,JH,JH,SS,SS,LL,EY,PA2,PA3,TT1,SS,PA1,0xFF
LEGISLATING:	DB	LL,EH,EH,PA2,JH,JH,SS,SS,LL,EY,PA2,PA3,TT2,IH,NG,PA1,0xFF
LEGISLATURE:	DB	LL,EH,EH,PA2,JH,JH,SS,SS,LL,EY,PA2,PA3,CH,ER1,PA1,0xFF
LETTER:			DB	LL,EH,EH,PA3,TT2,ER1,PA1,0xFF
LITTER:			DB	LL,IH,IH,PA3,TT2,ER1,PA1,0xFF
LITTLE:			DB	LL,IH,IH,PA3,TT2,EL,PA1,0xFF
MEMORY:			DB	MM,EH,EH,MM,ER2,IY,PA1,0xFF
MEMORIES:		DB	MM,EH,EH,MM,ER2,IY,ZZ,PA1,0xFF
MINUTE:			DB	MM,IH,NN1,IH,PA3,TT2,PA1,0xFF
MONTH:			DB	MM,AX,NN1,TH,PA1,0xFF
NIP:			DB	NN1,IH,IH,PA2,PA3,PP,PA1,0xFF
NIPPED:			DB	NN1,IH,IH,PA2,PA3,PP,PA3,TT2
NIPPING:		DB	NN1,IH,IH,PA2,PA3,PP,IH,NG,PA1,0XFF
NIPS:			DB	NN1,IH,IH,PA2,PA3,PP,SS,PA1,0XFF
NO:				DB	NN2,AX,OW,PA1,0XFF
PHYSICAL:		DB	FF,FF,IH,ZZ,IH,PA3,KK1,AX,EL,PA1,0XFF
PIN:			DB	PP,IH,IH,NN1,PA1,0XFF
PINNED:			DB	PP,IH,IH,NN1,PA2,DD1,PA1,0XFF
PINNING:		DB	PP,IH,IH,NN1,IH,NG,PA1,0XFF
PINS:			DB	PP,IH,IH,NN1,ZZ,PA1,0XFF
PLEDGE:			DB	PP,LL,EH,EH,PA3,JH,PA1,0XFF
PLEDGED:		DB	PP,LL,EH,EH,PA3,JH,PA2,DD1,PA1,0XFF
PLEDGES:		DB	PP,LL,EH,EH,PA3,JH,IH,ZZ,PA1,0XFF
PLEDGING:		DB	PP,LL,EH,EH,PA3,JH,IH,NG,PA1,0XFF
PLUS:			DB	PP,LL,AX,AX,SS,SS,PA1,0XFF
RAY:			DB	RR1,EH,EY,PA1,0XFF
RAYS:			DB	RR1,EH,EY,ZZ,PA1,0XFF
READY:			DB	RR1,EH,EH,PA1,DD2,IY,PA1,0XFF
RED:			DB	RR1,EH,EH,PA1,DD1,PA1,0XFF
ROBOT:			DB	RR1,OW,PA2,BB2,AA,PA3,TT2,PA1,0XFF
ROBOLS:			DB	RR1,OW,PA2,BB2,AA,PA3,TT1,SS,PA1,0XFF
SCORE:			DB	SS,SS,PA3,KK3,OR,PA1,0XFF
SECOND:			DB	SS,SS,EH,PA3,KK1,IH,NN1,PA2,DD1,PA1,0XFF
SENSITIVE:		DB	SS,SS,EH,EH,NN1,SS,SS,IH,PA2,PA3,TT2,IH,VV,PA1,0XFF
SENSITIVITY:	DB	SS,SS,EH,EH,NN1,SS,SS,IH,PA2,PA3,TT2,IH,VV,IH,PA2,PA3,TT2,IY,PA1,0XFF
SINCERE:		DB	SS,SS,IH,IH,NN1,SS,SS,YR,PA1,0XFF
SINCERELY:		DB	SS,SS,IH,IH,NN1,SS,SS,YR,LL,IY,PA1,0XFF
SINCERITY:		DB	SS,SS,IH,IH,NN1,SS,SS,EH,EH,RR1,IH,PA2,PA3,TT2,IY,PA1,0XFF
SISTER:			DB	SS,SS,IH,IH,SS,PA3,TT2,ER1,PA1,0XFF
SPEAK:			DB	SS,SS,PA3,IY,PA3,KK2,PA1,0XFF
SPELL:			DB	SS,SS,PA3,PP,EH,EH,EL,PA1,0XFF
SPELLED:		DB	SS,SS,PA3,PP,EH,EH,EL,PA3,DD1,PA1,0XFF
SPELLER:		DB	SS,SS,PA3,PP,EH,EH,EL,ER2,PA1,0XFF
SPELLERS:		DB	SS,SS,PA3,PP,EH,EH,EL,ER2,ZZ,PA1,0XFF
SPELLING:		DB	SS,SS,PA3,PP,EH,EH,EL,IH,NG,PA1,0XFF
SPELLS:			DB	SS,SS,PA3,PP,EH,EH,EL,ZZ,PA1,0XFF
START:			DB	SS,SS,PA3,TT2,AR,PA3,TT2,PA1,0XFF
STARTED:		DB	SS,SS,PA3,TT2,AR,PA3,TT2,IH,PA1,DD2,PA1,0XFF
STARTER:		DB	SS,SS,PA3,TT2,AR,PA3,TT2,ER1,PA1,0XFF
STARTING:		DB	SS,SS,PA3,TT2,AR,PA3,TT2,IH,NG,PA1,0XFF
STARTS:			DB	SS,SS,PA3,TT2,AR,PA3,TT1,SS,PA1,0XFF
STOP:			DB	SS,SS,PA3,TT1,AA,AA,PA3,PP,PA1,0XFF
STOPPED:		DB	SS,SS,PA3,TT1,AA,AA,PA3,PP,PA3,TT2,PA1,0XFF
STOPPER:		DB	SS,SS,PA3,TT1,AA,AA,PA3,PP,ER1,PA1,0XFF
STOPPING:		DB	SS,SS,PA3,TT1,AA,AA,PA3,PP,IH,NG,PA1,0XFF
STOPS:			DB	SS,SS,PA3,TT1,AA,AA,PA3,PP,SS,PA1,0XFF
SUBJECT_N:		DB	SS,SS,AX,AX,PA2,BB1,PA2,JH,EH,PA3,KK2,PA3,TT2,PA1,0XFF
SUBJECT_V:		DB	SS,SS,AX,PA2,BB1,PA2,JH,EH,EH,PA3,KK2,PA3,TT2,PA1,0XFF
SWEAT:			DB	SS,SS,WW,EH,EH,PA3,TT2,PA1,0XFF
SWEATED:		DB	SS,SS,WW,EH,EH,PA3,TT2,IH,PA3,DD1,PA1,0XFF
SWEATER:		DB	SS,SS,WW,EH,EH,PA3,TT2,ER1,PA1,0XFF
SWEATERS:		DB	SS,SS,WW,EH,EH,PA3,TT2,ER1,ZZ,PA1,0XFF
SWEATING:		DB	SS,SS,WW,EH,EH,PA3,TT2,IH,NG,PA1,0XFF
SWEATS:			DB	SS,SS,WW,EH,EH,PA3,TT2,SS,PA1,0XFF
SWITCH:			DB	SS,SS,WH,IH,IH,PA3,CH,PA1,0XFF
SWITCHED:		DB	SS,SS,WH,IH,IH,PA3,CH,PA3,TT2,PA1,0XFF
SWITCHES:		DB	SS,SS,WH,IH,IH,PA3,CH,IH,ZZ,PA1,0XFF
SWITCHING:		DB	SS,SS,WH,IH,IH,PA3,CH,IH,NG,PA1,0XFF
SYSTEM:			DB	SS,SS,IH,IH,SS,SS,PA3,TT2,EH,MM,PA1,0XFF
SYSTEMS:		DB	SS,SS,IH,IH,SS,SS,PA3,TT2,EH,MM,ZZ,PA1,0XFF
TALK:			DB	TT2,AO,AO,PA2,KK2,PA1,0XFF
TALKED:			DB	TT2,AO,AO,PA3,KK2,PA3,TT2,PA1,0XFF
TALKER:			DB	TT2,AO,AO,PA3,KK1,ER1,PA1,0XFF
TALKERS:		DB	TT2,AO,AO,PA3,KK1,ER1,ZZ,PA1,0XFF
TALKING:		DB	TT2,AO,AO,PA3,KK1,IH,NG,PA1,0XFF
TALKS:			DB	TT2,AO,AO,PA2,KK2,SS,PA1,0XFF
THREAD:			DB	TH,RR1,EH,EH,PA2,DD1,PA1,0XFF
THREADED:		DB	TH,RR1,EH,EH,PA2,DD2,IH,PA2,DD1,PA1,0XFF
THREADER:		DB	TH,RR1,EH,EH,PA2,DD2,ER1,PA1,0XFF
THREADERS:		DB	TH,RR1,EH,EH,PA2,DD2,ER1,ZZ,PA1,0XFF
THREADING:		DB	TH,RR1,EH,EH,PA2,DD2,IH,NG,PA1,0XFF
THREADS:		DB	TH,RR1,EH,EH,PA2,DD2,ZZ,PA1,0XFF
THEN:			DB	DH1,EH,EH,NN2,PA1,0XFF
TIME:			DB	TT2,AA,AY,MM,PA1,0XFF
TIMES:			DB	TT2,AA,AY,MM,ZZ,PA1,0XFF
UNCLE:			DB	AX,NG,PA3,KK3,EL,PA1,0XFF
WHALE:			DB	WW,EY,EL,PA1,0XFF
WHALER:			DB	WW,EY,LL,ER1,PA1,0XFF
WHALERS:		DB	WW,EY,LL,ER1,ZZ,PA1,0XFF
WHALES:			DB	WW,EY,EL,ZZ,PA1,0XFF
WHALING:		DB	WW,EY,LL,TH,NG,PA1,0XFF
YEAR:			DB	YY2,YR,PA1,0XFF
YES:			DB	YY2,EH,EH,SS,SS,PA1,0XFF




;====================================================================
; These are the 64 allophones for the SP0256-AL2
; Leave this at the end of the file
;====================================================================
PA1	EQU	00
PA2	EQU	01
PA3	EQU	02
PA4	EQU	03
PA5	EQU	04
OY	EQU	05
AY	EQU	06
EH	EQU	07
KK3	EQU	08
PP	EQU	09
JH	EQU	10
NN1	EQU	11
IH	EQU	12
TT2	EQU	13
RR1	EQU	14
AX	EQU	15
MM	EQU	16
TT1	EQU	17
DH1	EQU	18
IY	EQU	19
EY	EQU	20
DD1	EQU	21
UW1	EQU	22
AO	EQU	23
AA	EQU	24
YY2	EQU	25
AE	EQU	26
HH1	EQU	27
BB1	EQU	28
TH	EQU	29
UH	EQU	30
UW2	EQU	31
AW	EQU	32
DD2	EQU	33
GG3	EQU	34
VV	EQU	35
GG1	EQU	36
SH	EQU	37
ZH	EQU	38
RR2	EQU	39
FF	EQU	40
KK2	EQU	41
KK1	EQU	42
ZZ	EQU	43
NG	EQU	44
LL	EQU	45
WW	EQU	46
XR	EQU	47
WH	EQU	48
YY1	EQU	49
CH	EQU	50
ER1	EQU	51
ER2	EQU	52
OW	EQU	53
DH2	EQU	54
SS	EQU	55
NN2	EQU	56
HH2	EQU	57
OR	EQU	58
AR	EQU	59
YR	EQU	60
GG2	EQU	61
EL	EQU	62
BB2	EQU	63