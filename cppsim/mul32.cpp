#include "mul32.h"

/* Approximate Reduced Complexity Wallace Multiplier 32x32
*   Calculates the approximate multiplication between two 32-bit unsigned integers,
*   the vars array represents which AFA will be used at each slot of the
*   wallace multiplier.
*/

uint64_t ARCWM_32x32(uint32_t a, uint32_t b, uint8_t* vars){
    // sum names, taken from the beginning of "/code generation tools/axc_wallace_32x32.vhd"
    enum sum {s10060,s10059,s10058,s10057,s10056,s10055,s10054,s10053,s10052,//STAGE1
    s10051,s10050,s10049,s10048,s10047,s10046,s10045,s10044,s10043,s10042,
    s10041,s10040,s10039,s10038,s10037,s10036,s10035,s10034,s10033,s10032,
    s10031,s10030,s10029,s10028,s10027,s10026,s10025,s10024,s10023,s10022,
    s10021,s10020,s10019,s10018,s10017,s10016,s10015,s10014,s10013,s10012,
    s10011,s10010,s10009,s10008,s10007,s10006,s10005,s10004,s10003,s10002,
    s10157,s10156,s10155,s10154,s10153,s10152,s10151,s10150,s10149,s10148,
    s10147,s10146,s10145,s10144,s10143,s10142,s10141,s10140,s10139,s10138,
    s10137,s10136,s10135,s10134,s10133,s10132,s10131,s10130,s10129,s10128,
    s10127,s10126,s10125,s10124,s10123,s10122,s10121,s10120,s10119,s10118,
    s10117,s10116,s10115,s10114,s10113,s10112,s10111,s10110,s10109,s10108,
    s10107,s10106,s10105,s10254,s10253,s10252,s10251,s10250,s10249,s10248,
    s10247,s10246,s10245,s10244,s10243,s10242,s10241,s10240,s10239,s10238,
    s10237,s10236,s10235,s10234,s10233,s10232,s10231,s10230,s10229,s10228,
    s10227,s10226,s10225,s10224,s10223,s10222,s10221,s10220,s10219,s10218,
    s10217,s10216,s10215,s10214,s10213,s10212,s10211,s10210,s10209,s10208,
    s10351,s10350,s10349,s10348,s10347,s10346,s10345,s10344,s10343,s10342,
    s10341,s10340,s10339,s10338,s10337,s10336,s10335,s10334,s10333,s10332,
    s10331,s10330,s10329,s10328,s10327,s10326,s10325,s10324,s10323,s10322,
    s10321,s10320,s10319,s10318,s10317,s10316,s10315,s10314,s10313,s10312,
    s10311,s10448,s10447,s10446,s10445,s10444,s10443,s10442,s10441,s10440,
    s10439,s10438,s10437,s10436,s10435,s10434,s10433,s10432,s10431,s10430,
    s10429,s10428,s10427,s10426,s10425,s10424,s10423,s10422,s10421,s10420,
    s10419,s10418,s10417,s10416,s10415,s10414,s10545,s10544,s10543,s10542,
    s10541,s10540,s10539,s10538,s10537,s10536,s10535,s10534,s10533,s10532,
    s10531,s10530,s10529,s10528,s10527,s10526,s10525,s10524,s10523,s10522,
    s10521,s10520,s10519,s10518,s10517,s10642,s10641,s10640,s10639,s10638,
    s10637,s10636,s10635,s10634,s10633,s10632,s10631,s10630,s10629,s10628,
    s10627,s10626,s10625,s10624,s10623,s10622,s10621,s10620,s10739,s10738,
    s10737,s10736,s10735,s10734,s10733,s10732,s10731,s10730,s10729,s10728,
    s10727,s10726,s10725,s10724,s10723,s10836,s10835,s10834,s10833,s10832,
    s10831,s10830,s10829,s10828,s10827,s10826,s10933,s10932,s10931,s10930,
    s10929,

    s20061,s20059,s20058,s20057,s20056,s20055,s20054,s20053,s20052,s20051,//STAGE2
    s20050,s20049,s20048,s20047,s20046,s20045,s20044,s20043,s20042,s20041,
    s20040,s20039,s20038,s20037,s20036,s20035,s20034,s20033,s20032,s20031,
    s20030,s20029,s20028,s20027,s20026,s20025,s20024,s20023,s20022,s20021,
    s20020,s20019,s20018,s20017,s20016,s20015,s20014,s20013,s20012,s20011,
    s20010,s20009,s20008,s20007,s20006,s20005,s20004,s20003,s20155,s20154,
    s20153,s20152,s20151,s20150,s20149,s20148,s20147,s20146,s20145,s20144,
    s20143,s20142,s20141,s20140,s20139,s20138,s20137,s20136,s20135,s20134,
    s20133,s20132,s20131,s20130,s20129,s20128,s20127,s20126,s20125,s20124,
    s20123,s20122,s20121,s20120,s20119,s20118,s20117,s20116,s20115,s20114,
    s20113,s20112,s20111,s20110,s20109,s20107,s20252,s20250,s20249,s20248,
    s20247,s20246,s20245,s20244,s20243,s20242,s20241,s20240,s20239,s20238,
    s20237,s20236,s20235,s20234,s20233,s20232,s20231,s20230,s20229,s20228,
    s20227,s20226,s20225,s20224,s20223,s20222,s20221,s20220,s20219,s20218,
    s20217,s20216,s20215,s20214,s20213,s20212,s20346,s20345,s20344,s20343,
    s20342,s20341,s20340,s20339,s20338,s20337,s20336,s20335,s20334,s20333,
    s20332,s20331,s20330,s20329,s20328,s20327,s20326,s20325,s20324,s20323,
    s20322,s20321,s20320,s20319,s20318,s20316,s20443,s20441,s20440,s20439,
    s20438,s20437,s20436,s20435,s20434,s20433,s20432,s20431,s20430,s20429,
    s20428,s20427,s20426,s20425,s20424,s20423,s20422,s20421,s20537,s20536,
    s20535,s20534,s20533,s20532,s20531,s20530,s20529,s20528,s20527,s20525,
    s20634,s20632,s20631,s20630,

    s30060,s30059,s30058,s30057,s30056,s30055,s30054,s30053,s30052,s30051,//STAGE3
    s30050,s30049,s30048,s30047,s30046,s30045,s30044,s30043,s30042,s30041,
    s30040,s30039,s30038,s30037,s30036,s30035,s30034,s30033,s30032,s30031,
    s30030,s30029,s30028,s30027,s30026,s30025,s30024,s30023,s30022,s30021,
    s30020,s30019,s30018,s30017,s30016,s30015,s30014,s30013,s30012,s30011,
    s30010,s30009,s30008,s30007,s30006,s30005,s30004,s30156,s30155,s30153,
    s30152,s30151,s30150,s30149,s30148,s30147,s30146,s30145,s30144,s30143,
    s30142,s30141,s30140,s30139,s30138,s30137,s30136,s30135,s30134,s30133,
    s30132,s30131,s30130,s30129,s30128,s30127,s30126,s30125,s30124,s30123,
    s30122,s30121,s30120,s30119,s30118,s30117,s30116,s30115,s30114,s30113,
    s30112,s30111,s30110,s30108,s30249,s30247,s30246,s30245,s30244,s30243,
    s30242,s30241,s30240,s30239,s30238,s30237,s30236,s30235,s30234,s30233,
    s30232,s30231,s30230,s30229,s30228,s30227,s30226,s30225,s30224,s30223,
    s30222,s30221,s30220,s30219,s30218,s30217,s30215,s30342,s30340,s30339,
    s30338,s30337,s30336,s30335,s30334,s30333,s30332,s30331,s30330,s30329,
    s30328,s30327,s30326,s30325,s30324,s30322,s30435,s30433,s30432,s30431,
    s30428,

    s40058,s40057,s40056,s40055,s40054,s40053,s40052,s40051,s40050,s40049,//STAGE4
    s40048,s40047,s40046,s40045,s40044,s40043,s40042,s40041,s40040,s40039,
    s40038,s40037,s40036,s40035,s40034,s40033,s40032,s40031,s40030,s40029,
    s40028,s40027,s40026,s40025,s40024,s40023,s40022,s40021,s40020,s40019,
    s40018,s40017,s40016,s40015,s40014,s40013,s40012,s40011,s40010,s40009,
    s40008,s40006,s40148,s40147,s40146,s40145,s40144,s40143,s40142,s40141,
    s40140,s40139,s40138,s40137,s40136,s40135,s40134,s40133,s40132,s40131,
    s40130,s40129,s40128,s40127,s40126,s40125,s40124,s40123,s40122,s40121,
    s40120,s40119,s40118,s40116,s40238,s40237,s40236,s40235,s40234,s40233,
    s40232,s40231,s40230,s40229,s40228,s40226,

    s50059,s50056,s50054,s50053,s50052,s50051,s50050,s50049,s50048,s50047,//STAGE5
    s50046,s50045,s50044,s50043,s50042,s50041,s50040,s50039,s50038,s50037,
    s50036,s50035,s50034,s50033,s50032,s50031,s50030,s50029,s50028,s50027,
    s50026,s50025,s50024,s50023,s50022,s50021,s50020,s50019,s50018,s50017,
    s50016,s50015,s50014,s50013,s50012,s50011,s50009,s50007,s50141,s50140,
    s50139,s50138,s50137,s50136,s50135,s50134,s50133,s50132,s50131,s50130,
    s50129,s50127,s50125,s50123,

    s60060,s60057,s60055,s60051,s60050,s60049,s60048,s60047,s60046,s60045,//STAGE6
    s60044,s60043,s60042,s60041,s60040,s60039,s60038,s60037,s60036,s60035,
    s60034,s60033,s60032,s60031,s60030,s60029,s60028,s60027,s60026,s60025,
    s60024,s60023,s60022,s60021,s60020,s60019,s60017,s60015,s60013,s60010,

    s70061,s70058,s70052,s70049,s70044,s70043,s70042,s70041,s70040,s70039,//STAGE7
    s70038,s70037,s70036,s70035,s70034,s70033,s70032,s70031,s70030,s70029,
    s70028,s70027,s70026,s70024,s70022,s70018,s70016,s70014,

    s80062,s80054,s80053,s80051,s80050,s80048,s80047,s80046,s80045,s80044,//STAGE8
    s80043,s80042,s80041,s80040,s80039,s80038,s80037,s80036,s80035,s80034,
    s80033,s80032,s80031,s80030,s80029,s80028,s80027,s80026,s80025,s80024,
    s80023,s80021,s80020,s80019,s80017};
    
    int par_num = 32;                                                           // partial products number
    int sum_num = 957;                                                          // sums number

    uint64_t prodA=0, prodB=0;                                                  // outputs

    bitset<32>* partials = (bitset<32>*) malloc(par_num*sizeof(bitset<32>));    // malloc partial products array
    for(int i=0; i<par_num; i++) partials[i] = 0;
    partial_products(a, b, par_num, partials);                                  // generate partial products

    uint8_t* sums = (uint8_t*) malloc(sum_num*sizeof(uint8_t));                 // malloc sums array
    for(int i=0; i<sum_num; i++) sums[i] = 0;

    // do sums, generated by "/code generation tools/cpp_gen.py"
    sums[s10002] = ax_full_adder(partials[0][2], partials[1][1], partials[2][0], vars[0]);
    sums[s10003] = ax_full_adder(partials[0][3], partials[1][2], partials[2][1], vars[1]);
    sums[s10004] = ax_full_adder(partials[0][4], partials[1][3], partials[2][2], vars[2]);
    sums[s10005] = ax_full_adder(partials[0][5], partials[1][4], partials[2][3], vars[3]);
    sums[s10006] = ax_full_adder(partials[0][6], partials[1][5], partials[2][4], vars[4]);
    sums[s10007] = ax_full_adder(partials[0][7], partials[1][6], partials[2][5], vars[5]);
    sums[s10008] = ax_full_adder(partials[0][8], partials[1][7], partials[2][6], vars[6]);
    sums[s10009] = ax_full_adder(partials[0][9], partials[1][8], partials[2][7], vars[7]);
    sums[s10010] = ax_full_adder(partials[0][10], partials[1][9], partials[2][8], vars[8]);
    sums[s10011] = ax_full_adder(partials[0][11], partials[1][10], partials[2][9], vars[9]);
    sums[s10012] = ax_full_adder(partials[0][12], partials[1][11], partials[2][10], vars[10]);
    sums[s10013] = ax_full_adder(partials[0][13], partials[1][12], partials[2][11], vars[11]);
    sums[s10014] = ax_full_adder(partials[0][14], partials[1][13], partials[2][12], vars[12]);
    sums[s10015] = ax_full_adder(partials[0][15], partials[1][14], partials[2][13], vars[13]);
    sums[s10016] = ax_full_adder(partials[0][16], partials[1][15], partials[2][14], vars[14]);
    sums[s10017] = ax_full_adder(partials[0][17], partials[1][16], partials[2][15], vars[15]);
    sums[s10018] = ax_full_adder(partials[0][18], partials[1][17], partials[2][16], vars[16]);
    sums[s10019] = ax_full_adder(partials[0][19], partials[1][18], partials[2][17], vars[17]);
    sums[s10020] = ax_full_adder(partials[0][20], partials[1][19], partials[2][18], vars[18]);
    sums[s10021] = ax_full_adder(partials[0][21], partials[1][20], partials[2][19], vars[19]);
    sums[s10022] = ax_full_adder(partials[0][22], partials[1][21], partials[2][20], vars[20]);
    sums[s10023] = ax_full_adder(partials[0][23], partials[1][22], partials[2][21], vars[21]);
    sums[s10024] = ax_full_adder(partials[0][24], partials[1][23], partials[2][22], vars[22]);
    sums[s10025] = ax_full_adder(partials[0][25], partials[1][24], partials[2][23], vars[23]);
    sums[s10026] = ax_full_adder(partials[0][26], partials[1][25], partials[2][24], vars[24]);
    sums[s10027] = ax_full_adder(partials[0][27], partials[1][26], partials[2][25], vars[25]);
    sums[s10028] = ax_full_adder(partials[0][28], partials[1][27], partials[2][26], vars[26]);
    sums[s10029] = ax_full_adder(partials[0][29], partials[1][28], partials[2][27], vars[27]);
    sums[s10030] = ax_full_adder(partials[0][30], partials[1][29], partials[2][28], vars[28]);
    sums[s10031] = ax_full_adder(partials[0][31], partials[1][30], partials[2][29], vars[29]);
    sums[s10032] = ax_full_adder(partials[1][31], partials[2][30], partials[3][29], vars[30]);
    sums[s10033] = ax_full_adder(partials[2][31], partials[3][30], partials[4][29], vars[31]);
    sums[s10034] = ax_full_adder(partials[3][31], partials[4][30], partials[5][29], vars[32]);
    sums[s10035] = ax_full_adder(partials[4][31], partials[5][30], partials[6][29], vars[33]);
    sums[s10036] = ax_full_adder(partials[5][31], partials[6][30], partials[7][29], vars[34]);
    sums[s10037] = ax_full_adder(partials[6][31], partials[7][30], partials[8][29], vars[35]);
    sums[s10038] = ax_full_adder(partials[7][31], partials[8][30], partials[9][29], vars[36]);
    sums[s10039] = ax_full_adder(partials[8][31], partials[9][30], partials[10][29], vars[37]);
    sums[s10040] = ax_full_adder(partials[9][31], partials[10][30], partials[11][29], vars[38]);
    sums[s10041] = ax_full_adder(partials[10][31], partials[11][30], partials[12][29], vars[39]);
    sums[s10042] = ax_full_adder(partials[11][31], partials[12][30], partials[13][29], vars[40]);
    sums[s10043] = ax_full_adder(partials[12][31], partials[13][30], partials[14][29], vars[41]);
    sums[s10044] = ax_full_adder(partials[13][31], partials[14][30], partials[15][29], vars[42]);
    sums[s10045] = ax_full_adder(partials[14][31], partials[15][30], partials[16][29], vars[43]);
    sums[s10046] = ax_full_adder(partials[15][31], partials[16][30], partials[17][29], vars[44]);
    sums[s10047] = ax_full_adder(partials[16][31], partials[17][30], partials[18][29], vars[45]);
    sums[s10048] = ax_full_adder(partials[17][31], partials[18][30], partials[19][29], vars[46]);
    sums[s10049] = ax_full_adder(partials[18][31], partials[19][30], partials[20][29], vars[47]);
    sums[s10050] = ax_full_adder(partials[19][31], partials[20][30], partials[21][29], vars[48]);
    sums[s10051] = ax_full_adder(partials[20][31], partials[21][30], partials[22][29], vars[49]);
    sums[s10052] = ax_full_adder(partials[21][31], partials[22][30], partials[23][29], vars[50]);
    sums[s10053] = ax_full_adder(partials[22][31], partials[23][30], partials[24][29], vars[51]);
    sums[s10054] = ax_full_adder(partials[23][31], partials[24][30], partials[25][29], vars[52]);
    sums[s10055] = ax_full_adder(partials[24][31], partials[25][30], partials[26][29], vars[53]);
    sums[s10056] = ax_full_adder(partials[25][31], partials[26][30], partials[27][29], vars[54]);
    sums[s10057] = ax_full_adder(partials[26][31], partials[27][30], partials[28][29], vars[55]);
    sums[s10058] = ax_full_adder(partials[27][31], partials[28][30], partials[29][29], vars[56]);
    sums[s10059] = ax_full_adder(partials[28][31], partials[29][30], partials[30][29], vars[57]);
    sums[s10060] = ax_full_adder(partials[29][31], partials[30][30], partials[31][29], vars[58]);
    sums[s10105] = ax_full_adder(partials[3][2], partials[4][1], partials[5][0], vars[59]);
    sums[s10106] = ax_full_adder(partials[3][3], partials[4][2], partials[5][1], vars[60]);
    sums[s10107] = ax_full_adder(partials[3][4], partials[4][3], partials[5][2], vars[61]);
    sums[s10108] = ax_full_adder(partials[3][5], partials[4][4], partials[5][3], vars[62]);
    sums[s10109] = ax_full_adder(partials[3][6], partials[4][5], partials[5][4], vars[63]);
    sums[s10110] = ax_full_adder(partials[3][7], partials[4][6], partials[5][5], vars[64]);
    sums[s10111] = ax_full_adder(partials[3][8], partials[4][7], partials[5][6], vars[65]);
    sums[s10112] = ax_full_adder(partials[3][9], partials[4][8], partials[5][7], vars[66]);
    sums[s10113] = ax_full_adder(partials[3][10], partials[4][9], partials[5][8], vars[67]);
    sums[s10114] = ax_full_adder(partials[3][11], partials[4][10], partials[5][9], vars[68]);
    sums[s10115] = ax_full_adder(partials[3][12], partials[4][11], partials[5][10], vars[69]);
    sums[s10116] = ax_full_adder(partials[3][13], partials[4][12], partials[5][11], vars[70]);
    sums[s10117] = ax_full_adder(partials[3][14], partials[4][13], partials[5][12], vars[71]);
    sums[s10118] = ax_full_adder(partials[3][15], partials[4][14], partials[5][13], vars[72]);
    sums[s10119] = ax_full_adder(partials[3][16], partials[4][15], partials[5][14], vars[73]);
    sums[s10120] = ax_full_adder(partials[3][17], partials[4][16], partials[5][15], vars[74]);
    sums[s10121] = ax_full_adder(partials[3][18], partials[4][17], partials[5][16], vars[75]);
    sums[s10122] = ax_full_adder(partials[3][19], partials[4][18], partials[5][17], vars[76]);
    sums[s10123] = ax_full_adder(partials[3][20], partials[4][19], partials[5][18], vars[77]);
    sums[s10124] = ax_full_adder(partials[3][21], partials[4][20], partials[5][19], vars[78]);
    sums[s10125] = ax_full_adder(partials[3][22], partials[4][21], partials[5][20], vars[79]);
    sums[s10126] = ax_full_adder(partials[3][23], partials[4][22], partials[5][21], vars[80]);
    sums[s10127] = ax_full_adder(partials[3][24], partials[4][23], partials[5][22], vars[81]);
    sums[s10128] = ax_full_adder(partials[3][25], partials[4][24], partials[5][23], vars[82]);
    sums[s10129] = ax_full_adder(partials[3][26], partials[4][25], partials[5][24], vars[83]);
    sums[s10130] = ax_full_adder(partials[3][27], partials[4][26], partials[5][25], vars[84]);
    sums[s10131] = ax_full_adder(partials[3][28], partials[4][27], partials[5][26], vars[85]);
    sums[s10132] = ax_full_adder(partials[4][28], partials[5][27], partials[6][26], vars[86]);
    sums[s10133] = ax_full_adder(partials[5][28], partials[6][27], partials[7][26], vars[87]);
    sums[s10134] = ax_full_adder(partials[6][28], partials[7][27], partials[8][26], vars[88]);
    sums[s10135] = ax_full_adder(partials[7][28], partials[8][27], partials[9][26], vars[89]);
    sums[s10136] = ax_full_adder(partials[8][28], partials[9][27], partials[10][26], vars[90]);
    sums[s10137] = ax_full_adder(partials[9][28], partials[10][27], partials[11][26], vars[91]);
    sums[s10138] = ax_full_adder(partials[10][28], partials[11][27], partials[12][26], vars[92]);
    sums[s10139] = ax_full_adder(partials[11][28], partials[12][27], partials[13][26], vars[93]);
    sums[s10140] = ax_full_adder(partials[12][28], partials[13][27], partials[14][26], vars[94]);
    sums[s10141] = ax_full_adder(partials[13][28], partials[14][27], partials[15][26], vars[95]);
    sums[s10142] = ax_full_adder(partials[14][28], partials[15][27], partials[16][26], vars[96]);
    sums[s10143] = ax_full_adder(partials[15][28], partials[16][27], partials[17][26], vars[97]);
    sums[s10144] = ax_full_adder(partials[16][28], partials[17][27], partials[18][26], vars[98]);
    sums[s10145] = ax_full_adder(partials[17][28], partials[18][27], partials[19][26], vars[99]);
    sums[s10146] = ax_full_adder(partials[18][28], partials[19][27], partials[20][26], vars[100]);
    sums[s10147] = ax_full_adder(partials[19][28], partials[20][27], partials[21][26], vars[101]);
    sums[s10148] = ax_full_adder(partials[20][28], partials[21][27], partials[22][26], vars[102]);
    sums[s10149] = ax_full_adder(partials[21][28], partials[22][27], partials[23][26], vars[103]);
    sums[s10150] = ax_full_adder(partials[22][28], partials[23][27], partials[24][26], vars[104]);
    sums[s10151] = ax_full_adder(partials[23][28], partials[24][27], partials[25][26], vars[105]);
    sums[s10152] = ax_full_adder(partials[24][28], partials[25][27], partials[26][26], vars[106]);
    sums[s10153] = ax_full_adder(partials[25][28], partials[26][27], partials[27][26], vars[107]);
    sums[s10154] = ax_full_adder(partials[26][28], partials[27][27], partials[28][26], vars[108]);
    sums[s10155] = ax_full_adder(partials[27][28], partials[28][27], partials[29][26], vars[109]);
    sums[s10156] = ax_full_adder(partials[28][28], partials[29][27], partials[30][26], vars[110]);
    sums[s10157] = ax_full_adder(partials[29][28], partials[30][27], partials[31][26], vars[111]);
    sums[s10208] = ax_full_adder(partials[6][2], partials[7][1], partials[8][0], vars[112]);
    sums[s10209] = ax_full_adder(partials[6][3], partials[7][2], partials[8][1], vars[113]);
    sums[s10210] = ax_full_adder(partials[6][4], partials[7][3], partials[8][2], vars[114]);
    sums[s10211] = ax_full_adder(partials[6][5], partials[7][4], partials[8][3], vars[115]);
    sums[s10212] = ax_full_adder(partials[6][6], partials[7][5], partials[8][4], vars[116]);
    sums[s10213] = ax_full_adder(partials[6][7], partials[7][6], partials[8][5], vars[117]);
    sums[s10214] = ax_full_adder(partials[6][8], partials[7][7], partials[8][6], vars[118]);
    sums[s10215] = ax_full_adder(partials[6][9], partials[7][8], partials[8][7], vars[119]);
    sums[s10216] = ax_full_adder(partials[6][10], partials[7][9], partials[8][8], vars[120]);
    sums[s10217] = ax_full_adder(partials[6][11], partials[7][10], partials[8][9], vars[121]);
    sums[s10218] = ax_full_adder(partials[6][12], partials[7][11], partials[8][10], vars[122]);
    sums[s10219] = ax_full_adder(partials[6][13], partials[7][12], partials[8][11], vars[123]);
    sums[s10220] = ax_full_adder(partials[6][14], partials[7][13], partials[8][12], vars[124]);
    sums[s10221] = ax_full_adder(partials[6][15], partials[7][14], partials[8][13], vars[125]);
    sums[s10222] = ax_full_adder(partials[6][16], partials[7][15], partials[8][14], vars[126]);
    sums[s10223] = ax_full_adder(partials[6][17], partials[7][16], partials[8][15], vars[127]);
    sums[s10224] = ax_full_adder(partials[6][18], partials[7][17], partials[8][16], vars[128]);
    sums[s10225] = ax_full_adder(partials[6][19], partials[7][18], partials[8][17], vars[129]);
    sums[s10226] = ax_full_adder(partials[6][20], partials[7][19], partials[8][18], vars[130]);
    sums[s10227] = ax_full_adder(partials[6][21], partials[7][20], partials[8][19], vars[131]);
    sums[s10228] = ax_full_adder(partials[6][22], partials[7][21], partials[8][20], vars[132]);
    sums[s10229] = ax_full_adder(partials[6][23], partials[7][22], partials[8][21], vars[133]);
    sums[s10230] = ax_full_adder(partials[6][24], partials[7][23], partials[8][22], vars[134]);
    sums[s10231] = ax_full_adder(partials[6][25], partials[7][24], partials[8][23], vars[135]);
    sums[s10232] = ax_full_adder(partials[7][25], partials[8][24], partials[9][23], vars[136]);
    sums[s10233] = ax_full_adder(partials[8][25], partials[9][24], partials[10][23], vars[137]);
    sums[s10234] = ax_full_adder(partials[9][25], partials[10][24], partials[11][23], vars[138]);
    sums[s10235] = ax_full_adder(partials[10][25], partials[11][24], partials[12][23], vars[139]);
    sums[s10236] = ax_full_adder(partials[11][25], partials[12][24], partials[13][23], vars[140]);
    sums[s10237] = ax_full_adder(partials[12][25], partials[13][24], partials[14][23], vars[141]);
    sums[s10238] = ax_full_adder(partials[13][25], partials[14][24], partials[15][23], vars[142]);
    sums[s10239] = ax_full_adder(partials[14][25], partials[15][24], partials[16][23], vars[143]);
    sums[s10240] = ax_full_adder(partials[15][25], partials[16][24], partials[17][23], vars[144]);
    sums[s10241] = ax_full_adder(partials[16][25], partials[17][24], partials[18][23], vars[145]);
    sums[s10242] = ax_full_adder(partials[17][25], partials[18][24], partials[19][23], vars[146]);
    sums[s10243] = ax_full_adder(partials[18][25], partials[19][24], partials[20][23], vars[147]);
    sums[s10244] = ax_full_adder(partials[19][25], partials[20][24], partials[21][23], vars[148]);
    sums[s10245] = ax_full_adder(partials[20][25], partials[21][24], partials[22][23], vars[149]);
    sums[s10246] = ax_full_adder(partials[21][25], partials[22][24], partials[23][23], vars[150]);
    sums[s10247] = ax_full_adder(partials[22][25], partials[23][24], partials[24][23], vars[151]);
    sums[s10248] = ax_full_adder(partials[23][25], partials[24][24], partials[25][23], vars[152]);
    sums[s10249] = ax_full_adder(partials[24][25], partials[25][24], partials[26][23], vars[153]);
    sums[s10250] = ax_full_adder(partials[25][25], partials[26][24], partials[27][23], vars[154]);
    sums[s10251] = ax_full_adder(partials[26][25], partials[27][24], partials[28][23], vars[155]);
    sums[s10252] = ax_full_adder(partials[27][25], partials[28][24], partials[29][23], vars[156]);
    sums[s10253] = ax_full_adder(partials[28][25], partials[29][24], partials[30][23], vars[157]);
    sums[s10254] = ax_full_adder(partials[29][25], partials[30][24], partials[31][23], vars[158]);
    sums[s10311] = ax_full_adder(partials[9][2], partials[10][1], partials[11][0], vars[159]);
    sums[s10312] = ax_full_adder(partials[9][3], partials[10][2], partials[11][1], vars[160]);
    sums[s10313] = ax_full_adder(partials[9][4], partials[10][3], partials[11][2], vars[161]);
    sums[s10314] = ax_full_adder(partials[9][5], partials[10][4], partials[11][3], vars[162]);
    sums[s10315] = ax_full_adder(partials[9][6], partials[10][5], partials[11][4], vars[163]);
    sums[s10316] = ax_full_adder(partials[9][7], partials[10][6], partials[11][5], vars[164]);
    sums[s10317] = ax_full_adder(partials[9][8], partials[10][7], partials[11][6], vars[165]);
    sums[s10318] = ax_full_adder(partials[9][9], partials[10][8], partials[11][7], vars[166]);
    sums[s10319] = ax_full_adder(partials[9][10], partials[10][9], partials[11][8], vars[167]);
    sums[s10320] = ax_full_adder(partials[9][11], partials[10][10], partials[11][9], vars[168]);
    sums[s10321] = ax_full_adder(partials[9][12], partials[10][11], partials[11][10], vars[169]);
    sums[s10322] = ax_full_adder(partials[9][13], partials[10][12], partials[11][11], vars[170]);
    sums[s10323] = ax_full_adder(partials[9][14], partials[10][13], partials[11][12], vars[171]);
    sums[s10324] = ax_full_adder(partials[9][15], partials[10][14], partials[11][13], vars[172]);
    sums[s10325] = ax_full_adder(partials[9][16], partials[10][15], partials[11][14], vars[173]);
    sums[s10326] = ax_full_adder(partials[9][17], partials[10][16], partials[11][15], vars[174]);
    sums[s10327] = ax_full_adder(partials[9][18], partials[10][17], partials[11][16], vars[175]);
    sums[s10328] = ax_full_adder(partials[9][19], partials[10][18], partials[11][17], vars[176]);
    sums[s10329] = ax_full_adder(partials[9][20], partials[10][19], partials[11][18], vars[177]);
    sums[s10330] = ax_full_adder(partials[9][21], partials[10][20], partials[11][19], vars[178]);
    sums[s10331] = ax_full_adder(partials[9][22], partials[10][21], partials[11][20], vars[179]);
    sums[s10332] = ax_full_adder(partials[10][22], partials[11][21], partials[12][20], vars[180]);
    sums[s10333] = ax_full_adder(partials[11][22], partials[12][21], partials[13][20], vars[181]);
    sums[s10334] = ax_full_adder(partials[12][22], partials[13][21], partials[14][20], vars[182]);
    sums[s10335] = ax_full_adder(partials[13][22], partials[14][21], partials[15][20], vars[183]);
    sums[s10336] = ax_full_adder(partials[14][22], partials[15][21], partials[16][20], vars[184]);
    sums[s10337] = ax_full_adder(partials[15][22], partials[16][21], partials[17][20], vars[185]);
    sums[s10338] = ax_full_adder(partials[16][22], partials[17][21], partials[18][20], vars[186]);
    sums[s10339] = ax_full_adder(partials[17][22], partials[18][21], partials[19][20], vars[187]);
    sums[s10340] = ax_full_adder(partials[18][22], partials[19][21], partials[20][20], vars[188]);
    sums[s10341] = ax_full_adder(partials[19][22], partials[20][21], partials[21][20], vars[189]);
    sums[s10342] = ax_full_adder(partials[20][22], partials[21][21], partials[22][20], vars[190]);
    sums[s10343] = ax_full_adder(partials[21][22], partials[22][21], partials[23][20], vars[191]);
    sums[s10344] = ax_full_adder(partials[22][22], partials[23][21], partials[24][20], vars[192]);
    sums[s10345] = ax_full_adder(partials[23][22], partials[24][21], partials[25][20], vars[193]);
    sums[s10346] = ax_full_adder(partials[24][22], partials[25][21], partials[26][20], vars[194]);
    sums[s10347] = ax_full_adder(partials[25][22], partials[26][21], partials[27][20], vars[195]);
    sums[s10348] = ax_full_adder(partials[26][22], partials[27][21], partials[28][20], vars[196]);
    sums[s10349] = ax_full_adder(partials[27][22], partials[28][21], partials[29][20], vars[197]);
    sums[s10350] = ax_full_adder(partials[28][22], partials[29][21], partials[30][20], vars[198]);
    sums[s10351] = ax_full_adder(partials[29][22], partials[30][21], partials[31][20], vars[199]);
    sums[s10414] = ax_full_adder(partials[12][2], partials[13][1], partials[14][0], vars[200]);
    sums[s10415] = ax_full_adder(partials[12][3], partials[13][2], partials[14][1], vars[201]);
    sums[s10416] = ax_full_adder(partials[12][4], partials[13][3], partials[14][2], vars[202]);
    sums[s10417] = ax_full_adder(partials[12][5], partials[13][4], partials[14][3], vars[203]);
    sums[s10418] = ax_full_adder(partials[12][6], partials[13][5], partials[14][4], vars[204]);
    sums[s10419] = ax_full_adder(partials[12][7], partials[13][6], partials[14][5], vars[205]);
    sums[s10420] = ax_full_adder(partials[12][8], partials[13][7], partials[14][6], vars[206]);
    sums[s10421] = ax_full_adder(partials[12][9], partials[13][8], partials[14][7], vars[207]);
    sums[s10422] = ax_full_adder(partials[12][10], partials[13][9], partials[14][8], vars[208]);
    sums[s10423] = ax_full_adder(partials[12][11], partials[13][10], partials[14][9], vars[209]);
    sums[s10424] = ax_full_adder(partials[12][12], partials[13][11], partials[14][10], vars[210]);
    sums[s10425] = ax_full_adder(partials[12][13], partials[13][12], partials[14][11], vars[211]);
    sums[s10426] = ax_full_adder(partials[12][14], partials[13][13], partials[14][12], vars[212]);
    sums[s10427] = ax_full_adder(partials[12][15], partials[13][14], partials[14][13], vars[213]);
    sums[s10428] = ax_full_adder(partials[12][16], partials[13][15], partials[14][14], vars[214]);
    sums[s10429] = ax_full_adder(partials[12][17], partials[13][16], partials[14][15], vars[215]);
    sums[s10430] = ax_full_adder(partials[12][18], partials[13][17], partials[14][16], vars[216]);
    sums[s10431] = ax_full_adder(partials[12][19], partials[13][18], partials[14][17], vars[217]);
    sums[s10432] = ax_full_adder(partials[13][19], partials[14][18], partials[15][17], vars[218]);
    sums[s10433] = ax_full_adder(partials[14][19], partials[15][18], partials[16][17], vars[219]);
    sums[s10434] = ax_full_adder(partials[15][19], partials[16][18], partials[17][17], vars[220]);
    sums[s10435] = ax_full_adder(partials[16][19], partials[17][18], partials[18][17], vars[221]);
    sums[s10436] = ax_full_adder(partials[17][19], partials[18][18], partials[19][17], vars[222]);
    sums[s10437] = ax_full_adder(partials[18][19], partials[19][18], partials[20][17], vars[223]);
    sums[s10438] = ax_full_adder(partials[19][19], partials[20][18], partials[21][17], vars[224]);
    sums[s10439] = ax_full_adder(partials[20][19], partials[21][18], partials[22][17], vars[225]);
    sums[s10440] = ax_full_adder(partials[21][19], partials[22][18], partials[23][17], vars[226]);
    sums[s10441] = ax_full_adder(partials[22][19], partials[23][18], partials[24][17], vars[227]);
    sums[s10442] = ax_full_adder(partials[23][19], partials[24][18], partials[25][17], vars[228]);
    sums[s10443] = ax_full_adder(partials[24][19], partials[25][18], partials[26][17], vars[229]);
    sums[s10444] = ax_full_adder(partials[25][19], partials[26][18], partials[27][17], vars[230]);
    sums[s10445] = ax_full_adder(partials[26][19], partials[27][18], partials[28][17], vars[231]);
    sums[s10446] = ax_full_adder(partials[27][19], partials[28][18], partials[29][17], vars[232]);
    sums[s10447] = ax_full_adder(partials[28][19], partials[29][18], partials[30][17], vars[233]);
    sums[s10448] = ax_full_adder(partials[29][19], partials[30][18], partials[31][17], vars[234]);
    sums[s10517] = ax_full_adder(partials[15][2], partials[16][1], partials[17][0], vars[235]);
    sums[s10518] = ax_full_adder(partials[15][3], partials[16][2], partials[17][1], vars[236]);
    sums[s10519] = ax_full_adder(partials[15][4], partials[16][3], partials[17][2], vars[237]);
    sums[s10520] = ax_full_adder(partials[15][5], partials[16][4], partials[17][3], vars[238]);
    sums[s10521] = ax_full_adder(partials[15][6], partials[16][5], partials[17][4], vars[239]);
    sums[s10522] = ax_full_adder(partials[15][7], partials[16][6], partials[17][5], vars[240]);
    sums[s10523] = ax_full_adder(partials[15][8], partials[16][7], partials[17][6], vars[241]);
    sums[s10524] = ax_full_adder(partials[15][9], partials[16][8], partials[17][7], vars[242]);
    sums[s10525] = ax_full_adder(partials[15][10], partials[16][9], partials[17][8], vars[243]);
    sums[s10526] = ax_full_adder(partials[15][11], partials[16][10], partials[17][9], vars[244]);
    sums[s10527] = ax_full_adder(partials[15][12], partials[16][11], partials[17][10], vars[245]);
    sums[s10528] = ax_full_adder(partials[15][13], partials[16][12], partials[17][11], vars[246]);
    sums[s10529] = ax_full_adder(partials[15][14], partials[16][13], partials[17][12], vars[247]);
    sums[s10530] = ax_full_adder(partials[15][15], partials[16][14], partials[17][13], vars[248]);
    sums[s10531] = ax_full_adder(partials[15][16], partials[16][15], partials[17][14], vars[249]);
    sums[s10532] = ax_full_adder(partials[16][16], partials[17][15], partials[18][14], vars[250]);
    sums[s10533] = ax_full_adder(partials[17][16], partials[18][15], partials[19][14], vars[251]);
    sums[s10534] = ax_full_adder(partials[18][16], partials[19][15], partials[20][14], vars[252]);
    sums[s10535] = ax_full_adder(partials[19][16], partials[20][15], partials[21][14], vars[253]);
    sums[s10536] = ax_full_adder(partials[20][16], partials[21][15], partials[22][14], vars[254]);
    sums[s10537] = ax_full_adder(partials[21][16], partials[22][15], partials[23][14], vars[255]);
    sums[s10538] = ax_full_adder(partials[22][16], partials[23][15], partials[24][14], vars[256]);
    sums[s10539] = ax_full_adder(partials[23][16], partials[24][15], partials[25][14], vars[257]);
    sums[s10540] = ax_full_adder(partials[24][16], partials[25][15], partials[26][14], vars[258]);
    sums[s10541] = ax_full_adder(partials[25][16], partials[26][15], partials[27][14], vars[259]);
    sums[s10542] = ax_full_adder(partials[26][16], partials[27][15], partials[28][14], vars[260]);
    sums[s10543] = ax_full_adder(partials[27][16], partials[28][15], partials[29][14], vars[261]);
    sums[s10544] = ax_full_adder(partials[28][16], partials[29][15], partials[30][14], vars[262]);
    sums[s10545] = ax_full_adder(partials[29][16], partials[30][15], partials[31][14], vars[263]);
    sums[s10620] = ax_full_adder(partials[18][2], partials[19][1], partials[20][0], vars[264]);
    sums[s10621] = ax_full_adder(partials[18][3], partials[19][2], partials[20][1], vars[265]);
    sums[s10622] = ax_full_adder(partials[18][4], partials[19][3], partials[20][2], vars[266]);
    sums[s10623] = ax_full_adder(partials[18][5], partials[19][4], partials[20][3], vars[267]);
    sums[s10624] = ax_full_adder(partials[18][6], partials[19][5], partials[20][4], vars[268]);
    sums[s10625] = ax_full_adder(partials[18][7], partials[19][6], partials[20][5], vars[269]);
    sums[s10626] = ax_full_adder(partials[18][8], partials[19][7], partials[20][6], vars[270]);
    sums[s10627] = ax_full_adder(partials[18][9], partials[19][8], partials[20][7], vars[271]);
    sums[s10628] = ax_full_adder(partials[18][10], partials[19][9], partials[20][8], vars[272]);
    sums[s10629] = ax_full_adder(partials[18][11], partials[19][10], partials[20][9], vars[273]);
    sums[s10630] = ax_full_adder(partials[18][12], partials[19][11], partials[20][10], vars[274]);
    sums[s10631] = ax_full_adder(partials[18][13], partials[19][12], partials[20][11], vars[275]);
    sums[s10632] = ax_full_adder(partials[19][13], partials[20][12], partials[21][11], vars[276]);
    sums[s10633] = ax_full_adder(partials[20][13], partials[21][12], partials[22][11], vars[277]);
    sums[s10634] = ax_full_adder(partials[21][13], partials[22][12], partials[23][11], vars[278]);
    sums[s10635] = ax_full_adder(partials[22][13], partials[23][12], partials[24][11], vars[279]);
    sums[s10636] = ax_full_adder(partials[23][13], partials[24][12], partials[25][11], vars[280]);
    sums[s10637] = ax_full_adder(partials[24][13], partials[25][12], partials[26][11], vars[281]);
    sums[s10638] = ax_full_adder(partials[25][13], partials[26][12], partials[27][11], vars[282]);
    sums[s10639] = ax_full_adder(partials[26][13], partials[27][12], partials[28][11], vars[283]);
    sums[s10640] = ax_full_adder(partials[27][13], partials[28][12], partials[29][11], vars[284]);
    sums[s10641] = ax_full_adder(partials[28][13], partials[29][12], partials[30][11], vars[285]);
    sums[s10642] = ax_full_adder(partials[29][13], partials[30][12], partials[31][11], vars[286]);
    sums[s10723] = ax_full_adder(partials[21][2], partials[22][1], partials[23][0], vars[287]);
    sums[s10724] = ax_full_adder(partials[21][3], partials[22][2], partials[23][1], vars[288]);
    sums[s10725] = ax_full_adder(partials[21][4], partials[22][3], partials[23][2], vars[289]);
    sums[s10726] = ax_full_adder(partials[21][5], partials[22][4], partials[23][3], vars[290]);
    sums[s10727] = ax_full_adder(partials[21][6], partials[22][5], partials[23][4], vars[291]);
    sums[s10728] = ax_full_adder(partials[21][7], partials[22][6], partials[23][5], vars[292]);
    sums[s10729] = ax_full_adder(partials[21][8], partials[22][7], partials[23][6], vars[293]);
    sums[s10730] = ax_full_adder(partials[21][9], partials[22][8], partials[23][7], vars[294]);
    sums[s10731] = ax_full_adder(partials[21][10], partials[22][9], partials[23][8], vars[295]);
    sums[s10732] = ax_full_adder(partials[22][10], partials[23][9], partials[24][8], vars[296]);
    sums[s10733] = ax_full_adder(partials[23][10], partials[24][9], partials[25][8], vars[297]);
    sums[s10734] = ax_full_adder(partials[24][10], partials[25][9], partials[26][8], vars[298]);
    sums[s10735] = ax_full_adder(partials[25][10], partials[26][9], partials[27][8], vars[299]);
    sums[s10736] = ax_full_adder(partials[26][10], partials[27][9], partials[28][8], vars[300]);
    sums[s10737] = ax_full_adder(partials[27][10], partials[28][9], partials[29][8], vars[301]);
    sums[s10738] = ax_full_adder(partials[28][10], partials[29][9], partials[30][8], vars[302]);
    sums[s10739] = ax_full_adder(partials[29][10], partials[30][9], partials[31][8], vars[303]);
    sums[s10826] = ax_full_adder(partials[24][2], partials[25][1], partials[26][0], vars[304]);
    sums[s10827] = ax_full_adder(partials[24][3], partials[25][2], partials[26][1], vars[305]);
    sums[s10828] = ax_full_adder(partials[24][4], partials[25][3], partials[26][2], vars[306]);
    sums[s10829] = ax_full_adder(partials[24][5], partials[25][4], partials[26][3], vars[307]);
    sums[s10830] = ax_full_adder(partials[24][6], partials[25][5], partials[26][4], vars[308]);
    sums[s10831] = ax_full_adder(partials[24][7], partials[25][6], partials[26][5], vars[309]);
    sums[s10832] = ax_full_adder(partials[25][7], partials[26][6], partials[27][5], vars[310]);
    sums[s10833] = ax_full_adder(partials[26][7], partials[27][6], partials[28][5], vars[311]);
    sums[s10834] = ax_full_adder(partials[27][7], partials[28][6], partials[29][5], vars[312]);
    sums[s10835] = ax_full_adder(partials[28][7], partials[29][6], partials[30][5], vars[313]);
    sums[s10836] = ax_full_adder(partials[29][7], partials[30][6], partials[31][5], vars[314]);
    sums[s10929] = ax_full_adder(partials[27][2], partials[28][1], partials[29][0], vars[315]);
    sums[s10930] = ax_full_adder(partials[27][3], partials[28][2], partials[29][1], vars[316]);
    sums[s10931] = ax_full_adder(partials[27][4], partials[28][3], partials[29][2], vars[317]);
    sums[s10932] = ax_full_adder(partials[28][4], partials[29][3], partials[30][2], vars[318]);
    sums[s10933] = ax_full_adder(partials[29][4], partials[30][3], partials[31][2], vars[319]);
    sums[s20003] = ax_full_adder(sums[s10003]&1, (sums[s10002]&2)>>1, partials[3][0], vars[320]);
    sums[s20004] = ax_full_adder(sums[s10004]&1, (sums[s10003]&2)>>1, partials[3][1], vars[321]);
    sums[s20005] = ax_full_adder(sums[s10005]&1, (sums[s10004]&2)>>1, sums[s10105]&1, vars[322]);
    sums[s20006] = ax_full_adder(sums[s10006]&1, (sums[s10005]&2)>>1, sums[s10106]&1, vars[323]);
    sums[s20007] = ax_full_adder(sums[s10007]&1, (sums[s10006]&2)>>1, sums[s10107]&1, vars[324]);
    sums[s20008] = ax_full_adder(sums[s10008]&1, (sums[s10007]&2)>>1, sums[s10108]&1, vars[325]);
    sums[s20009] = ax_full_adder(sums[s10009]&1, (sums[s10008]&2)>>1, sums[s10109]&1, vars[326]);
    sums[s20010] = ax_full_adder(sums[s10010]&1, (sums[s10009]&2)>>1, sums[s10110]&1, vars[327]);
    sums[s20011] = ax_full_adder(sums[s10011]&1, (sums[s10010]&2)>>1, sums[s10111]&1, vars[328]);
    sums[s20012] = ax_full_adder(sums[s10012]&1, (sums[s10011]&2)>>1, sums[s10112]&1, vars[329]);
    sums[s20013] = ax_full_adder(sums[s10013]&1, (sums[s10012]&2)>>1, sums[s10113]&1, vars[330]);
    sums[s20014] = ax_full_adder(sums[s10014]&1, (sums[s10013]&2)>>1, sums[s10114]&1, vars[331]);
    sums[s20015] = ax_full_adder(sums[s10015]&1, (sums[s10014]&2)>>1, sums[s10115]&1, vars[332]);
    sums[s20016] = ax_full_adder(sums[s10016]&1, (sums[s10015]&2)>>1, sums[s10116]&1, vars[333]);
    sums[s20017] = ax_full_adder(sums[s10017]&1, (sums[s10016]&2)>>1, sums[s10117]&1, vars[334]);
    sums[s20018] = ax_full_adder(sums[s10018]&1, (sums[s10017]&2)>>1, sums[s10118]&1, vars[335]);
    sums[s20019] = ax_full_adder(sums[s10019]&1, (sums[s10018]&2)>>1, sums[s10119]&1, vars[336]);
    sums[s20020] = ax_full_adder(sums[s10020]&1, (sums[s10019]&2)>>1, sums[s10120]&1, vars[337]);
    sums[s20021] = ax_full_adder(sums[s10021]&1, (sums[s10020]&2)>>1, sums[s10121]&1, vars[338]);
    sums[s20022] = ax_full_adder(sums[s10022]&1, (sums[s10021]&2)>>1, sums[s10122]&1, vars[339]);
    sums[s20023] = ax_full_adder(sums[s10023]&1, (sums[s10022]&2)>>1, sums[s10123]&1, vars[340]);
    sums[s20024] = ax_full_adder(sums[s10024]&1, (sums[s10023]&2)>>1, sums[s10124]&1, vars[341]);
    sums[s20025] = ax_full_adder(sums[s10025]&1, (sums[s10024]&2)>>1, sums[s10125]&1, vars[342]);
    sums[s20026] = ax_full_adder(sums[s10026]&1, (sums[s10025]&2)>>1, sums[s10126]&1, vars[343]);
    sums[s20027] = ax_full_adder(sums[s10027]&1, (sums[s10026]&2)>>1, sums[s10127]&1, vars[344]);
    sums[s20028] = ax_full_adder(sums[s10028]&1, (sums[s10027]&2)>>1, sums[s10128]&1, vars[345]);
    sums[s20029] = ax_full_adder(sums[s10029]&1, (sums[s10028]&2)>>1, sums[s10129]&1, vars[346]);
    sums[s20030] = ax_full_adder(sums[s10030]&1, (sums[s10029]&2)>>1, sums[s10130]&1, vars[347]);
    sums[s20031] = ax_full_adder(sums[s10031]&1, (sums[s10030]&2)>>1, sums[s10131]&1, vars[348]);
    sums[s20032] = ax_full_adder(sums[s10032]&1, (sums[s10031]&2)>>1, sums[s10132]&1, vars[349]);
    sums[s20033] = ax_full_adder(sums[s10033]&1, (sums[s10032]&2)>>1, sums[s10133]&1, vars[350]);
    sums[s20034] = ax_full_adder(sums[s10034]&1, (sums[s10033]&2)>>1, sums[s10134]&1, vars[351]);
    sums[s20035] = ax_full_adder(sums[s10035]&1, (sums[s10034]&2)>>1, sums[s10135]&1, vars[352]);
    sums[s20036] = ax_full_adder(sums[s10036]&1, (sums[s10035]&2)>>1, sums[s10136]&1, vars[353]);
    sums[s20037] = ax_full_adder(sums[s10037]&1, (sums[s10036]&2)>>1, sums[s10137]&1, vars[354]);
    sums[s20038] = ax_full_adder(sums[s10038]&1, (sums[s10037]&2)>>1, sums[s10138]&1, vars[355]);
    sums[s20039] = ax_full_adder(sums[s10039]&1, (sums[s10038]&2)>>1, sums[s10139]&1, vars[356]);
    sums[s20040] = ax_full_adder(sums[s10040]&1, (sums[s10039]&2)>>1, sums[s10140]&1, vars[357]);
    sums[s20041] = ax_full_adder(sums[s10041]&1, (sums[s10040]&2)>>1, sums[s10141]&1, vars[358]);
    sums[s20042] = ax_full_adder(sums[s10042]&1, (sums[s10041]&2)>>1, sums[s10142]&1, vars[359]);
    sums[s20043] = ax_full_adder(sums[s10043]&1, (sums[s10042]&2)>>1, sums[s10143]&1, vars[360]);
    sums[s20044] = ax_full_adder(sums[s10044]&1, (sums[s10043]&2)>>1, sums[s10144]&1, vars[361]);
    sums[s20045] = ax_full_adder(sums[s10045]&1, (sums[s10044]&2)>>1, sums[s10145]&1, vars[362]);
    sums[s20046] = ax_full_adder(sums[s10046]&1, (sums[s10045]&2)>>1, sums[s10146]&1, vars[363]);
    sums[s20047] = ax_full_adder(sums[s10047]&1, (sums[s10046]&2)>>1, sums[s10147]&1, vars[364]);
    sums[s20048] = ax_full_adder(sums[s10048]&1, (sums[s10047]&2)>>1, sums[s10148]&1, vars[365]);
    sums[s20049] = ax_full_adder(sums[s10049]&1, (sums[s10048]&2)>>1, sums[s10149]&1, vars[366]);
    sums[s20050] = ax_full_adder(sums[s10050]&1, (sums[s10049]&2)>>1, sums[s10150]&1, vars[367]);
    sums[s20051] = ax_full_adder(sums[s10051]&1, (sums[s10050]&2)>>1, sums[s10151]&1, vars[368]);
    sums[s20052] = ax_full_adder(sums[s10052]&1, (sums[s10051]&2)>>1, sums[s10152]&1, vars[369]);
    sums[s20053] = ax_full_adder(sums[s10053]&1, (sums[s10052]&2)>>1, sums[s10153]&1, vars[370]);
    sums[s20054] = ax_full_adder(sums[s10054]&1, (sums[s10053]&2)>>1, sums[s10154]&1, vars[371]);
    sums[s20055] = ax_full_adder(sums[s10055]&1, (sums[s10054]&2)>>1, sums[s10155]&1, vars[372]);
    sums[s20056] = ax_full_adder(sums[s10056]&1, (sums[s10055]&2)>>1, sums[s10156]&1, vars[373]);
    sums[s20057] = ax_full_adder(sums[s10057]&1, (sums[s10056]&2)>>1, sums[s10157]&1, vars[374]);
    sums[s20058] = ax_full_adder(sums[s10058]&1, (sums[s10057]&2)>>1, partials[30][28], vars[375]);
    sums[s20059] = ax_full_adder(sums[s10059]&1, (sums[s10058]&2)>>1, partials[31][28], vars[376]);
    sums[s20061] = ax_full_adder(partials[30][31], partials[31][30], (sums[s10060]&2)>>1, vars[377]);
    sums[s20107] = ax_full_adder((sums[s10106]&2)>>1, partials[6][1], partials[7][0], vars[378]);
    sums[s20109] = ax_full_adder((sums[s10108]&2)>>1, sums[s10209]&1, (sums[s10208]&2)>>1, vars[379]);
    sums[s20110] = ax_full_adder((sums[s10109]&2)>>1, sums[s10210]&1, (sums[s10209]&2)>>1, vars[380]);
    sums[s20111] = ax_full_adder((sums[s10110]&2)>>1, sums[s10211]&1, (sums[s10210]&2)>>1, vars[381]);
    sums[s20112] = ax_full_adder((sums[s10111]&2)>>1, sums[s10212]&1, (sums[s10211]&2)>>1, vars[382]);
    sums[s20113] = ax_full_adder((sums[s10112]&2)>>1, sums[s10213]&1, (sums[s10212]&2)>>1, vars[383]);
    sums[s20114] = ax_full_adder((sums[s10113]&2)>>1, sums[s10214]&1, (sums[s10213]&2)>>1, vars[384]);
    sums[s20115] = ax_full_adder((sums[s10114]&2)>>1, sums[s10215]&1, (sums[s10214]&2)>>1, vars[385]);
    sums[s20116] = ax_full_adder((sums[s10115]&2)>>1, sums[s10216]&1, (sums[s10215]&2)>>1, vars[386]);
    sums[s20117] = ax_full_adder((sums[s10116]&2)>>1, sums[s10217]&1, (sums[s10216]&2)>>1, vars[387]);
    sums[s20118] = ax_full_adder((sums[s10117]&2)>>1, sums[s10218]&1, (sums[s10217]&2)>>1, vars[388]);
    sums[s20119] = ax_full_adder((sums[s10118]&2)>>1, sums[s10219]&1, (sums[s10218]&2)>>1, vars[389]);
    sums[s20120] = ax_full_adder((sums[s10119]&2)>>1, sums[s10220]&1, (sums[s10219]&2)>>1, vars[390]);
    sums[s20121] = ax_full_adder((sums[s10120]&2)>>1, sums[s10221]&1, (sums[s10220]&2)>>1, vars[391]);
    sums[s20122] = ax_full_adder((sums[s10121]&2)>>1, sums[s10222]&1, (sums[s10221]&2)>>1, vars[392]);
    sums[s20123] = ax_full_adder((sums[s10122]&2)>>1, sums[s10223]&1, (sums[s10222]&2)>>1, vars[393]);
    sums[s20124] = ax_full_adder((sums[s10123]&2)>>1, sums[s10224]&1, (sums[s10223]&2)>>1, vars[394]);
    sums[s20125] = ax_full_adder((sums[s10124]&2)>>1, sums[s10225]&1, (sums[s10224]&2)>>1, vars[395]);
    sums[s20126] = ax_full_adder((sums[s10125]&2)>>1, sums[s10226]&1, (sums[s10225]&2)>>1, vars[396]);
    sums[s20127] = ax_full_adder((sums[s10126]&2)>>1, sums[s10227]&1, (sums[s10226]&2)>>1, vars[397]);
    sums[s20128] = ax_full_adder((sums[s10127]&2)>>1, sums[s10228]&1, (sums[s10227]&2)>>1, vars[398]);
    sums[s20129] = ax_full_adder((sums[s10128]&2)>>1, sums[s10229]&1, (sums[s10228]&2)>>1, vars[399]);
    sums[s20130] = ax_full_adder((sums[s10129]&2)>>1, sums[s10230]&1, (sums[s10229]&2)>>1, vars[400]);
    sums[s20131] = ax_full_adder((sums[s10130]&2)>>1, sums[s10231]&1, (sums[s10230]&2)>>1, vars[401]);
    sums[s20132] = ax_full_adder((sums[s10131]&2)>>1, sums[s10232]&1, (sums[s10231]&2)>>1, vars[402]);
    sums[s20133] = ax_full_adder((sums[s10132]&2)>>1, sums[s10233]&1, (sums[s10232]&2)>>1, vars[403]);
    sums[s20134] = ax_full_adder((sums[s10133]&2)>>1, sums[s10234]&1, (sums[s10233]&2)>>1, vars[404]);
    sums[s20135] = ax_full_adder((sums[s10134]&2)>>1, sums[s10235]&1, (sums[s10234]&2)>>1, vars[405]);
    sums[s20136] = ax_full_adder((sums[s10135]&2)>>1, sums[s10236]&1, (sums[s10235]&2)>>1, vars[406]);
    sums[s20137] = ax_full_adder((sums[s10136]&2)>>1, sums[s10237]&1, (sums[s10236]&2)>>1, vars[407]);
    sums[s20138] = ax_full_adder((sums[s10137]&2)>>1, sums[s10238]&1, (sums[s10237]&2)>>1, vars[408]);
    sums[s20139] = ax_full_adder((sums[s10138]&2)>>1, sums[s10239]&1, (sums[s10238]&2)>>1, vars[409]);
    sums[s20140] = ax_full_adder((sums[s10139]&2)>>1, sums[s10240]&1, (sums[s10239]&2)>>1, vars[410]);
    sums[s20141] = ax_full_adder((sums[s10140]&2)>>1, sums[s10241]&1, (sums[s10240]&2)>>1, vars[411]);
    sums[s20142] = ax_full_adder((sums[s10141]&2)>>1, sums[s10242]&1, (sums[s10241]&2)>>1, vars[412]);
    sums[s20143] = ax_full_adder((sums[s10142]&2)>>1, sums[s10243]&1, (sums[s10242]&2)>>1, vars[413]);
    sums[s20144] = ax_full_adder((sums[s10143]&2)>>1, sums[s10244]&1, (sums[s10243]&2)>>1, vars[414]);
    sums[s20145] = ax_full_adder((sums[s10144]&2)>>1, sums[s10245]&1, (sums[s10244]&2)>>1, vars[415]);
    sums[s20146] = ax_full_adder((sums[s10145]&2)>>1, sums[s10246]&1, (sums[s10245]&2)>>1, vars[416]);
    sums[s20147] = ax_full_adder((sums[s10146]&2)>>1, sums[s10247]&1, (sums[s10246]&2)>>1, vars[417]);
    sums[s20148] = ax_full_adder((sums[s10147]&2)>>1, sums[s10248]&1, (sums[s10247]&2)>>1, vars[418]);
    sums[s20149] = ax_full_adder((sums[s10148]&2)>>1, sums[s10249]&1, (sums[s10248]&2)>>1, vars[419]);
    sums[s20150] = ax_full_adder((sums[s10149]&2)>>1, sums[s10250]&1, (sums[s10249]&2)>>1, vars[420]);
    sums[s20151] = ax_full_adder((sums[s10150]&2)>>1, sums[s10251]&1, (sums[s10250]&2)>>1, vars[421]);
    sums[s20152] = ax_full_adder((sums[s10151]&2)>>1, sums[s10252]&1, (sums[s10251]&2)>>1, vars[422]);
    sums[s20153] = ax_full_adder((sums[s10152]&2)>>1, sums[s10253]&1, (sums[s10252]&2)>>1, vars[423]);
    sums[s20154] = ax_full_adder((sums[s10153]&2)>>1, sums[s10254]&1, (sums[s10253]&2)>>1, vars[424]);
    sums[s20155] = ax_full_adder((sums[s10154]&2)>>1, partials[30][25], partials[31][24], vars[425]);
    sums[s20212] = ax_full_adder(sums[s10312]&1, (sums[s10311]&2)>>1, partials[12][0], vars[426]);
    sums[s20213] = ax_full_adder(sums[s10313]&1, (sums[s10312]&2)>>1, partials[12][1], vars[427]);
    sums[s20214] = ax_full_adder(sums[s10314]&1, (sums[s10313]&2)>>1, sums[s10414]&1, vars[428]);
    sums[s20215] = ax_full_adder(sums[s10315]&1, (sums[s10314]&2)>>1, sums[s10415]&1, vars[429]);
    sums[s20216] = ax_full_adder(sums[s10316]&1, (sums[s10315]&2)>>1, sums[s10416]&1, vars[430]);
    sums[s20217] = ax_full_adder(sums[s10317]&1, (sums[s10316]&2)>>1, sums[s10417]&1, vars[431]);
    sums[s20218] = ax_full_adder(sums[s10318]&1, (sums[s10317]&2)>>1, sums[s10418]&1, vars[432]);
    sums[s20219] = ax_full_adder(sums[s10319]&1, (sums[s10318]&2)>>1, sums[s10419]&1, vars[433]);
    sums[s20220] = ax_full_adder(sums[s10320]&1, (sums[s10319]&2)>>1, sums[s10420]&1, vars[434]);
    sums[s20221] = ax_full_adder(sums[s10321]&1, (sums[s10320]&2)>>1, sums[s10421]&1, vars[435]);
    sums[s20222] = ax_full_adder(sums[s10322]&1, (sums[s10321]&2)>>1, sums[s10422]&1, vars[436]);
    sums[s20223] = ax_full_adder(sums[s10323]&1, (sums[s10322]&2)>>1, sums[s10423]&1, vars[437]);
    sums[s20224] = ax_full_adder(sums[s10324]&1, (sums[s10323]&2)>>1, sums[s10424]&1, vars[438]);
    sums[s20225] = ax_full_adder(sums[s10325]&1, (sums[s10324]&2)>>1, sums[s10425]&1, vars[439]);
    sums[s20226] = ax_full_adder(sums[s10326]&1, (sums[s10325]&2)>>1, sums[s10426]&1, vars[440]);
    sums[s20227] = ax_full_adder(sums[s10327]&1, (sums[s10326]&2)>>1, sums[s10427]&1, vars[441]);
    sums[s20228] = ax_full_adder(sums[s10328]&1, (sums[s10327]&2)>>1, sums[s10428]&1, vars[442]);
    sums[s20229] = ax_full_adder(sums[s10329]&1, (sums[s10328]&2)>>1, sums[s10429]&1, vars[443]);
    sums[s20230] = ax_full_adder(sums[s10330]&1, (sums[s10329]&2)>>1, sums[s10430]&1, vars[444]);
    sums[s20231] = ax_full_adder(sums[s10331]&1, (sums[s10330]&2)>>1, sums[s10431]&1, vars[445]);
    sums[s20232] = ax_full_adder(sums[s10332]&1, (sums[s10331]&2)>>1, sums[s10432]&1, vars[446]);
    sums[s20233] = ax_full_adder(sums[s10333]&1, (sums[s10332]&2)>>1, sums[s10433]&1, vars[447]);
    sums[s20234] = ax_full_adder(sums[s10334]&1, (sums[s10333]&2)>>1, sums[s10434]&1, vars[448]);
    sums[s20235] = ax_full_adder(sums[s10335]&1, (sums[s10334]&2)>>1, sums[s10435]&1, vars[449]);
    sums[s20236] = ax_full_adder(sums[s10336]&1, (sums[s10335]&2)>>1, sums[s10436]&1, vars[450]);
    sums[s20237] = ax_full_adder(sums[s10337]&1, (sums[s10336]&2)>>1, sums[s10437]&1, vars[451]);
    sums[s20238] = ax_full_adder(sums[s10338]&1, (sums[s10337]&2)>>1, sums[s10438]&1, vars[452]);
    sums[s20239] = ax_full_adder(sums[s10339]&1, (sums[s10338]&2)>>1, sums[s10439]&1, vars[453]);
    sums[s20240] = ax_full_adder(sums[s10340]&1, (sums[s10339]&2)>>1, sums[s10440]&1, vars[454]);
    sums[s20241] = ax_full_adder(sums[s10341]&1, (sums[s10340]&2)>>1, sums[s10441]&1, vars[455]);
    sums[s20242] = ax_full_adder(sums[s10342]&1, (sums[s10341]&2)>>1, sums[s10442]&1, vars[456]);
    sums[s20243] = ax_full_adder(sums[s10343]&1, (sums[s10342]&2)>>1, sums[s10443]&1, vars[457]);
    sums[s20244] = ax_full_adder(sums[s10344]&1, (sums[s10343]&2)>>1, sums[s10444]&1, vars[458]);
    sums[s20245] = ax_full_adder(sums[s10345]&1, (sums[s10344]&2)>>1, sums[s10445]&1, vars[459]);
    sums[s20246] = ax_full_adder(sums[s10346]&1, (sums[s10345]&2)>>1, sums[s10446]&1, vars[460]);
    sums[s20247] = ax_full_adder(sums[s10347]&1, (sums[s10346]&2)>>1, sums[s10447]&1, vars[461]);
    sums[s20248] = ax_full_adder(sums[s10348]&1, (sums[s10347]&2)>>1, sums[s10448]&1, vars[462]);
    sums[s20249] = ax_full_adder(sums[s10349]&1, (sums[s10348]&2)>>1, partials[30][19], vars[463]);
    sums[s20250] = ax_full_adder(sums[s10350]&1, (sums[s10349]&2)>>1, partials[31][19], vars[464]);
    sums[s20252] = ax_full_adder(partials[30][22], partials[31][21], (sums[s10351]&2)>>1, vars[465]);
    sums[s20316] = ax_full_adder((sums[s10415]&2)>>1, partials[15][1], partials[16][0], vars[466]);
    sums[s20318] = ax_full_adder((sums[s10417]&2)>>1, sums[s10518]&1, (sums[s10517]&2)>>1, vars[467]);
    sums[s20319] = ax_full_adder((sums[s10418]&2)>>1, sums[s10519]&1, (sums[s10518]&2)>>1, vars[468]);
    sums[s20320] = ax_full_adder((sums[s10419]&2)>>1, sums[s10520]&1, (sums[s10519]&2)>>1, vars[469]);
    sums[s20321] = ax_full_adder((sums[s10420]&2)>>1, sums[s10521]&1, (sums[s10520]&2)>>1, vars[470]);
    sums[s20322] = ax_full_adder((sums[s10421]&2)>>1, sums[s10522]&1, (sums[s10521]&2)>>1, vars[471]);
    sums[s20323] = ax_full_adder((sums[s10422]&2)>>1, sums[s10523]&1, (sums[s10522]&2)>>1, vars[472]);
    sums[s20324] = ax_full_adder((sums[s10423]&2)>>1, sums[s10524]&1, (sums[s10523]&2)>>1, vars[473]);
    sums[s20325] = ax_full_adder((sums[s10424]&2)>>1, sums[s10525]&1, (sums[s10524]&2)>>1, vars[474]);
    sums[s20326] = ax_full_adder((sums[s10425]&2)>>1, sums[s10526]&1, (sums[s10525]&2)>>1, vars[475]);
    sums[s20327] = ax_full_adder((sums[s10426]&2)>>1, sums[s10527]&1, (sums[s10526]&2)>>1, vars[476]);
    sums[s20328] = ax_full_adder((sums[s10427]&2)>>1, sums[s10528]&1, (sums[s10527]&2)>>1, vars[477]);
    sums[s20329] = ax_full_adder((sums[s10428]&2)>>1, sums[s10529]&1, (sums[s10528]&2)>>1, vars[478]);
    sums[s20330] = ax_full_adder((sums[s10429]&2)>>1, sums[s10530]&1, (sums[s10529]&2)>>1, vars[479]);
    sums[s20331] = ax_full_adder((sums[s10430]&2)>>1, sums[s10531]&1, (sums[s10530]&2)>>1, vars[480]);
    sums[s20332] = ax_full_adder((sums[s10431]&2)>>1, sums[s10532]&1, (sums[s10531]&2)>>1, vars[481]);
    sums[s20333] = ax_full_adder((sums[s10432]&2)>>1, sums[s10533]&1, (sums[s10532]&2)>>1, vars[482]);
    sums[s20334] = ax_full_adder((sums[s10433]&2)>>1, sums[s10534]&1, (sums[s10533]&2)>>1, vars[483]);
    sums[s20335] = ax_full_adder((sums[s10434]&2)>>1, sums[s10535]&1, (sums[s10534]&2)>>1, vars[484]);
    sums[s20336] = ax_full_adder((sums[s10435]&2)>>1, sums[s10536]&1, (sums[s10535]&2)>>1, vars[485]);
    sums[s20337] = ax_full_adder((sums[s10436]&2)>>1, sums[s10537]&1, (sums[s10536]&2)>>1, vars[486]);
    sums[s20338] = ax_full_adder((sums[s10437]&2)>>1, sums[s10538]&1, (sums[s10537]&2)>>1, vars[487]);
    sums[s20339] = ax_full_adder((sums[s10438]&2)>>1, sums[s10539]&1, (sums[s10538]&2)>>1, vars[488]);
    sums[s20340] = ax_full_adder((sums[s10439]&2)>>1, sums[s10540]&1, (sums[s10539]&2)>>1, vars[489]);
    sums[s20341] = ax_full_adder((sums[s10440]&2)>>1, sums[s10541]&1, (sums[s10540]&2)>>1, vars[490]);
    sums[s20342] = ax_full_adder((sums[s10441]&2)>>1, sums[s10542]&1, (sums[s10541]&2)>>1, vars[491]);
    sums[s20343] = ax_full_adder((sums[s10442]&2)>>1, sums[s10543]&1, (sums[s10542]&2)>>1, vars[492]);
    sums[s20344] = ax_full_adder((sums[s10443]&2)>>1, sums[s10544]&1, (sums[s10543]&2)>>1, vars[493]);
    sums[s20345] = ax_full_adder((sums[s10444]&2)>>1, sums[s10545]&1, (sums[s10544]&2)>>1, vars[494]);
    sums[s20346] = ax_full_adder((sums[s10445]&2)>>1, partials[30][16], partials[31][15], vars[495]);
    sums[s20421] = ax_full_adder(sums[s10621]&1, (sums[s10620]&2)>>1, partials[21][0], vars[496]);
    sums[s20422] = ax_full_adder(sums[s10622]&1, (sums[s10621]&2)>>1, partials[21][1], vars[497]);
    sums[s20423] = ax_full_adder(sums[s10623]&1, (sums[s10622]&2)>>1, sums[s10723]&1, vars[498]);
    sums[s20424] = ax_full_adder(sums[s10624]&1, (sums[s10623]&2)>>1, sums[s10724]&1, vars[499]);
    sums[s20425] = ax_full_adder(sums[s10625]&1, (sums[s10624]&2)>>1, sums[s10725]&1, vars[500]);
    sums[s20426] = ax_full_adder(sums[s10626]&1, (sums[s10625]&2)>>1, sums[s10726]&1, vars[501]);
    sums[s20427] = ax_full_adder(sums[s10627]&1, (sums[s10626]&2)>>1, sums[s10727]&1, vars[502]);
    sums[s20428] = ax_full_adder(sums[s10628]&1, (sums[s10627]&2)>>1, sums[s10728]&1, vars[503]);
    sums[s20429] = ax_full_adder(sums[s10629]&1, (sums[s10628]&2)>>1, sums[s10729]&1, vars[504]);
    sums[s20430] = ax_full_adder(sums[s10630]&1, (sums[s10629]&2)>>1, sums[s10730]&1, vars[505]);
    sums[s20431] = ax_full_adder(sums[s10631]&1, (sums[s10630]&2)>>1, sums[s10731]&1, vars[506]);
    sums[s20432] = ax_full_adder(sums[s10632]&1, (sums[s10631]&2)>>1, sums[s10732]&1, vars[507]);
    sums[s20433] = ax_full_adder(sums[s10633]&1, (sums[s10632]&2)>>1, sums[s10733]&1, vars[508]);
    sums[s20434] = ax_full_adder(sums[s10634]&1, (sums[s10633]&2)>>1, sums[s10734]&1, vars[509]);
    sums[s20435] = ax_full_adder(sums[s10635]&1, (sums[s10634]&2)>>1, sums[s10735]&1, vars[510]);
    sums[s20436] = ax_full_adder(sums[s10636]&1, (sums[s10635]&2)>>1, sums[s10736]&1, vars[511]);
    sums[s20437] = ax_full_adder(sums[s10637]&1, (sums[s10636]&2)>>1, sums[s10737]&1, vars[512]);
    sums[s20438] = ax_full_adder(sums[s10638]&1, (sums[s10637]&2)>>1, sums[s10738]&1, vars[513]);
    sums[s20439] = ax_full_adder(sums[s10639]&1, (sums[s10638]&2)>>1, sums[s10739]&1, vars[514]);
    sums[s20440] = ax_full_adder(sums[s10640]&1, (sums[s10639]&2)>>1, partials[30][10], vars[515]);
    sums[s20441] = ax_full_adder(sums[s10641]&1, (sums[s10640]&2)>>1, partials[31][10], vars[516]);
    sums[s20443] = ax_full_adder(partials[30][13], partials[31][12], (sums[s10642]&2)>>1, vars[517]);
    sums[s20525] = ax_full_adder((sums[s10724]&2)>>1, partials[24][1], partials[25][0], vars[518]);
    sums[s20527] = ax_full_adder((sums[s10726]&2)>>1, sums[s10827]&1, (sums[s10826]&2)>>1, vars[519]);
    sums[s20528] = ax_full_adder((sums[s10727]&2)>>1, sums[s10828]&1, (sums[s10827]&2)>>1, vars[520]);
    sums[s20529] = ax_full_adder((sums[s10728]&2)>>1, sums[s10829]&1, (sums[s10828]&2)>>1, vars[521]);
    sums[s20530] = ax_full_adder((sums[s10729]&2)>>1, sums[s10830]&1, (sums[s10829]&2)>>1, vars[522]);
    sums[s20531] = ax_full_adder((sums[s10730]&2)>>1, sums[s10831]&1, (sums[s10830]&2)>>1, vars[523]);
    sums[s20532] = ax_full_adder((sums[s10731]&2)>>1, sums[s10832]&1, (sums[s10831]&2)>>1, vars[524]);
    sums[s20533] = ax_full_adder((sums[s10732]&2)>>1, sums[s10833]&1, (sums[s10832]&2)>>1, vars[525]);
    sums[s20534] = ax_full_adder((sums[s10733]&2)>>1, sums[s10834]&1, (sums[s10833]&2)>>1, vars[526]);
    sums[s20535] = ax_full_adder((sums[s10734]&2)>>1, sums[s10835]&1, (sums[s10834]&2)>>1, vars[527]);
    sums[s20536] = ax_full_adder((sums[s10735]&2)>>1, sums[s10836]&1, (sums[s10835]&2)>>1, vars[528]);
    sums[s20537] = ax_full_adder((sums[s10736]&2)>>1, partials[30][7], partials[31][6], vars[529]);
    sums[s20630] = ax_full_adder(sums[s10930]&1, (sums[s10929]&2)>>1, partials[30][0], vars[530]);
    sums[s20631] = ax_full_adder(sums[s10931]&1, (sums[s10930]&2)>>1, partials[30][1], vars[531]);
    sums[s20632] = ax_full_adder(sums[s10932]&1, (sums[s10931]&2)>>1, partials[31][1], vars[532]);
    sums[s20634] = ax_full_adder(partials[30][4], partials[31][3], (sums[s10933]&2)>>1, vars[533]);
    sums[s30004] = ax_full_adder(sums[s20004]&1, (sums[s20003]&2)>>1, partials[4][0], vars[534]);
    sums[s30005] = half_adder(sums[s20005]&1, (sums[s20004]&2)>>1);
    sums[s30006] = ax_full_adder(sums[s20006]&1, (sums[s20005]&2)>>1, (sums[s10105]&2)>>1, vars[535]);
    sums[s30007] = ax_full_adder(sums[s20007]&1, (sums[s20006]&2)>>1, sums[s20107]&1, vars[536]);
    sums[s30008] = ax_full_adder(sums[s20008]&1, (sums[s20007]&2)>>1, (sums[s10107]&2)>>1, vars[537]);
    sums[s30009] = ax_full_adder(sums[s20009]&1, (sums[s20008]&2)>>1, sums[s20109]&1, vars[538]);
    sums[s30010] = ax_full_adder(sums[s20010]&1, (sums[s20009]&2)>>1, sums[s20110]&1, vars[539]);
    sums[s30011] = ax_full_adder(sums[s20011]&1, (sums[s20010]&2)>>1, sums[s20111]&1, vars[540]);
    sums[s30012] = ax_full_adder(sums[s20012]&1, (sums[s20011]&2)>>1, sums[s20112]&1, vars[541]);
    sums[s30013] = ax_full_adder(sums[s20013]&1, (sums[s20012]&2)>>1, sums[s20113]&1, vars[542]);
    sums[s30014] = ax_full_adder(sums[s20014]&1, (sums[s20013]&2)>>1, sums[s20114]&1, vars[543]);
    sums[s30015] = ax_full_adder(sums[s20015]&1, (sums[s20014]&2)>>1, sums[s20115]&1, vars[544]);
    sums[s30016] = ax_full_adder(sums[s20016]&1, (sums[s20015]&2)>>1, sums[s20116]&1, vars[545]);
    sums[s30017] = ax_full_adder(sums[s20017]&1, (sums[s20016]&2)>>1, sums[s20117]&1, vars[546]);
    sums[s30018] = ax_full_adder(sums[s20018]&1, (sums[s20017]&2)>>1, sums[s20118]&1, vars[547]);
    sums[s30019] = ax_full_adder(sums[s20019]&1, (sums[s20018]&2)>>1, sums[s20119]&1, vars[548]);
    sums[s30020] = ax_full_adder(sums[s20020]&1, (sums[s20019]&2)>>1, sums[s20120]&1, vars[549]);
    sums[s30021] = ax_full_adder(sums[s20021]&1, (sums[s20020]&2)>>1, sums[s20121]&1, vars[550]);
    sums[s30022] = ax_full_adder(sums[s20022]&1, (sums[s20021]&2)>>1, sums[s20122]&1, vars[551]);
    sums[s30023] = ax_full_adder(sums[s20023]&1, (sums[s20022]&2)>>1, sums[s20123]&1, vars[552]);
    sums[s30024] = ax_full_adder(sums[s20024]&1, (sums[s20023]&2)>>1, sums[s20124]&1, vars[553]);
    sums[s30025] = ax_full_adder(sums[s20025]&1, (sums[s20024]&2)>>1, sums[s20125]&1, vars[554]);
    sums[s30026] = ax_full_adder(sums[s20026]&1, (sums[s20025]&2)>>1, sums[s20126]&1, vars[555]);
    sums[s30027] = ax_full_adder(sums[s20027]&1, (sums[s20026]&2)>>1, sums[s20127]&1, vars[556]);
    sums[s30028] = ax_full_adder(sums[s20028]&1, (sums[s20027]&2)>>1, sums[s20128]&1, vars[557]);
    sums[s30029] = ax_full_adder(sums[s20029]&1, (sums[s20028]&2)>>1, sums[s20129]&1, vars[558]);
    sums[s30030] = ax_full_adder(sums[s20030]&1, (sums[s20029]&2)>>1, sums[s20130]&1, vars[559]);
    sums[s30031] = ax_full_adder(sums[s20031]&1, (sums[s20030]&2)>>1, sums[s20131]&1, vars[560]);
    sums[s30032] = ax_full_adder(sums[s20032]&1, (sums[s20031]&2)>>1, sums[s20132]&1, vars[561]);
    sums[s30033] = ax_full_adder(sums[s20033]&1, (sums[s20032]&2)>>1, sums[s20133]&1, vars[562]);
    sums[s30034] = ax_full_adder(sums[s20034]&1, (sums[s20033]&2)>>1, sums[s20134]&1, vars[563]);
    sums[s30035] = ax_full_adder(sums[s20035]&1, (sums[s20034]&2)>>1, sums[s20135]&1, vars[564]);
    sums[s30036] = ax_full_adder(sums[s20036]&1, (sums[s20035]&2)>>1, sums[s20136]&1, vars[565]);
    sums[s30037] = ax_full_adder(sums[s20037]&1, (sums[s20036]&2)>>1, sums[s20137]&1, vars[566]);
    sums[s30038] = ax_full_adder(sums[s20038]&1, (sums[s20037]&2)>>1, sums[s20138]&1, vars[567]);
    sums[s30039] = ax_full_adder(sums[s20039]&1, (sums[s20038]&2)>>1, sums[s20139]&1, vars[568]);
    sums[s30040] = ax_full_adder(sums[s20040]&1, (sums[s20039]&2)>>1, sums[s20140]&1, vars[569]);
    sums[s30041] = ax_full_adder(sums[s20041]&1, (sums[s20040]&2)>>1, sums[s20141]&1, vars[570]);
    sums[s30042] = ax_full_adder(sums[s20042]&1, (sums[s20041]&2)>>1, sums[s20142]&1, vars[571]);
    sums[s30043] = ax_full_adder(sums[s20043]&1, (sums[s20042]&2)>>1, sums[s20143]&1, vars[572]);
    sums[s30044] = ax_full_adder(sums[s20044]&1, (sums[s20043]&2)>>1, sums[s20144]&1, vars[573]);
    sums[s30045] = ax_full_adder(sums[s20045]&1, (sums[s20044]&2)>>1, sums[s20145]&1, vars[574]);
    sums[s30046] = ax_full_adder(sums[s20046]&1, (sums[s20045]&2)>>1, sums[s20146]&1, vars[575]);
    sums[s30047] = ax_full_adder(sums[s20047]&1, (sums[s20046]&2)>>1, sums[s20147]&1, vars[576]);
    sums[s30048] = ax_full_adder(sums[s20048]&1, (sums[s20047]&2)>>1, sums[s20148]&1, vars[577]);
    sums[s30049] = ax_full_adder(sums[s20049]&1, (sums[s20048]&2)>>1, sums[s20149]&1, vars[578]);
    sums[s30050] = ax_full_adder(sums[s20050]&1, (sums[s20049]&2)>>1, sums[s20150]&1, vars[579]);
    sums[s30051] = ax_full_adder(sums[s20051]&1, (sums[s20050]&2)>>1, sums[s20151]&1, vars[580]);
    sums[s30052] = ax_full_adder(sums[s20052]&1, (sums[s20051]&2)>>1, sums[s20152]&1, vars[581]);
    sums[s30053] = ax_full_adder(sums[s20053]&1, (sums[s20052]&2)>>1, sums[s20153]&1, vars[582]);
    sums[s30054] = ax_full_adder(sums[s20054]&1, (sums[s20053]&2)>>1, sums[s20154]&1, vars[583]);
    sums[s30055] = ax_full_adder(sums[s20055]&1, (sums[s20054]&2)>>1, sums[s20155]&1, vars[584]);
    sums[s30056] = ax_full_adder(sums[s20056]&1, (sums[s20055]&2)>>1, (sums[s10155]&2)>>1, vars[585]);
    sums[s30057] = ax_full_adder(sums[s20057]&1, (sums[s20056]&2)>>1, (sums[s10156]&2)>>1, vars[586]);
    sums[s30058] = ax_full_adder(sums[s20058]&1, (sums[s20057]&2)>>1, partials[31][27], vars[587]);
    sums[s30059] = half_adder(sums[s20059]&1, (sums[s20058]&2)>>1);
    sums[s30060] = ax_full_adder(sums[s10060]&1, (sums[s10059]&2)>>1, (sums[s20059]&2)>>1, vars[588]);
    sums[s30108] = half_adder(sums[s10208]&1, (sums[s20107]&2)>>1);
    sums[s30110] = ax_full_adder((sums[s20109]&2)>>1, partials[9][1], partials[10][0], vars[589]);
    sums[s30111] = half_adder((sums[s20110]&2)>>1, sums[s10311]&1);
    sums[s30112] = half_adder((sums[s20111]&2)>>1, sums[s20212]&1);
    sums[s30113] = ax_full_adder((sums[s20112]&2)>>1, sums[s20213]&1, (sums[s20212]&2)>>1, vars[590]);
    sums[s30114] = ax_full_adder((sums[s20113]&2)>>1, sums[s20214]&1, (sums[s20213]&2)>>1, vars[591]);
    sums[s30115] = ax_full_adder((sums[s20114]&2)>>1, sums[s20215]&1, (sums[s20214]&2)>>1, vars[592]);
    sums[s30116] = ax_full_adder((sums[s20115]&2)>>1, sums[s20216]&1, (sums[s20215]&2)>>1, vars[593]);
    sums[s30117] = ax_full_adder((sums[s20116]&2)>>1, sums[s20217]&1, (sums[s20216]&2)>>1, vars[594]);
    sums[s30118] = ax_full_adder((sums[s20117]&2)>>1, sums[s20218]&1, (sums[s20217]&2)>>1, vars[595]);
    sums[s30119] = ax_full_adder((sums[s20118]&2)>>1, sums[s20219]&1, (sums[s20218]&2)>>1, vars[596]);
    sums[s30120] = ax_full_adder((sums[s20119]&2)>>1, sums[s20220]&1, (sums[s20219]&2)>>1, vars[597]);
    sums[s30121] = ax_full_adder((sums[s20120]&2)>>1, sums[s20221]&1, (sums[s20220]&2)>>1, vars[598]);
    sums[s30122] = ax_full_adder((sums[s20121]&2)>>1, sums[s20222]&1, (sums[s20221]&2)>>1, vars[599]);
    sums[s30123] = ax_full_adder((sums[s20122]&2)>>1, sums[s20223]&1, (sums[s20222]&2)>>1, vars[600]);
    sums[s30124] = ax_full_adder((sums[s20123]&2)>>1, sums[s20224]&1, (sums[s20223]&2)>>1, vars[601]);
    sums[s30125] = ax_full_adder((sums[s20124]&2)>>1, sums[s20225]&1, (sums[s20224]&2)>>1, vars[602]);
    sums[s30126] = ax_full_adder((sums[s20125]&2)>>1, sums[s20226]&1, (sums[s20225]&2)>>1, vars[603]);
    sums[s30127] = ax_full_adder((sums[s20126]&2)>>1, sums[s20227]&1, (sums[s20226]&2)>>1, vars[604]);
    sums[s30128] = ax_full_adder((sums[s20127]&2)>>1, sums[s20228]&1, (sums[s20227]&2)>>1, vars[605]);
    sums[s30129] = ax_full_adder((sums[s20128]&2)>>1, sums[s20229]&1, (sums[s20228]&2)>>1, vars[606]);
    sums[s30130] = ax_full_adder((sums[s20129]&2)>>1, sums[s20230]&1, (sums[s20229]&2)>>1, vars[607]);
    sums[s30131] = ax_full_adder((sums[s20130]&2)>>1, sums[s20231]&1, (sums[s20230]&2)>>1, vars[608]);
    sums[s30132] = ax_full_adder((sums[s20131]&2)>>1, sums[s20232]&1, (sums[s20231]&2)>>1, vars[609]);
    sums[s30133] = ax_full_adder((sums[s20132]&2)>>1, sums[s20233]&1, (sums[s20232]&2)>>1, vars[610]);
    sums[s30134] = ax_full_adder((sums[s20133]&2)>>1, sums[s20234]&1, (sums[s20233]&2)>>1, vars[611]);
    sums[s30135] = ax_full_adder((sums[s20134]&2)>>1, sums[s20235]&1, (sums[s20234]&2)>>1, vars[612]);
    sums[s30136] = ax_full_adder((sums[s20135]&2)>>1, sums[s20236]&1, (sums[s20235]&2)>>1, vars[613]);
    sums[s30137] = ax_full_adder((sums[s20136]&2)>>1, sums[s20237]&1, (sums[s20236]&2)>>1, vars[614]);
    sums[s30138] = ax_full_adder((sums[s20137]&2)>>1, sums[s20238]&1, (sums[s20237]&2)>>1, vars[615]);
    sums[s30139] = ax_full_adder((sums[s20138]&2)>>1, sums[s20239]&1, (sums[s20238]&2)>>1, vars[616]);
    sums[s30140] = ax_full_adder((sums[s20139]&2)>>1, sums[s20240]&1, (sums[s20239]&2)>>1, vars[617]);
    sums[s30141] = ax_full_adder((sums[s20140]&2)>>1, sums[s20241]&1, (sums[s20240]&2)>>1, vars[618]);
    sums[s30142] = ax_full_adder((sums[s20141]&2)>>1, sums[s20242]&1, (sums[s20241]&2)>>1, vars[619]);
    sums[s30143] = ax_full_adder((sums[s20142]&2)>>1, sums[s20243]&1, (sums[s20242]&2)>>1, vars[620]);
    sums[s30144] = ax_full_adder((sums[s20143]&2)>>1, sums[s20244]&1, (sums[s20243]&2)>>1, vars[621]);
    sums[s30145] = ax_full_adder((sums[s20144]&2)>>1, sums[s20245]&1, (sums[s20244]&2)>>1, vars[622]);
    sums[s30146] = ax_full_adder((sums[s20145]&2)>>1, sums[s20246]&1, (sums[s20245]&2)>>1, vars[623]);
    sums[s30147] = ax_full_adder((sums[s20146]&2)>>1, sums[s20247]&1, (sums[s20246]&2)>>1, vars[624]);
    sums[s30148] = ax_full_adder((sums[s20147]&2)>>1, sums[s20248]&1, (sums[s20247]&2)>>1, vars[625]);
    sums[s30149] = ax_full_adder((sums[s20148]&2)>>1, sums[s20249]&1, (sums[s20248]&2)>>1, vars[626]);
    sums[s30150] = ax_full_adder((sums[s20149]&2)>>1, sums[s20250]&1, (sums[s20249]&2)>>1, vars[627]);
    sums[s30151] = ax_full_adder((sums[s20150]&2)>>1, sums[s10351]&1, (sums[s10350]&2)>>1, vars[628]);
    sums[s30152] = half_adder((sums[s20151]&2)>>1, sums[s20252]&1);
    sums[s30153] = ax_full_adder((sums[s20152]&2)>>1, partials[31][22], (sums[s20252]&2)>>1, vars[629]);
    sums[s30155] = half_adder((sums[s20154]&2)>>1, (sums[s10254]&2)>>1);
    sums[s30156] = half_adder(partials[31][25], (sums[s20155]&2)>>1);
    sums[s30215] = half_adder((sums[s10414]&2)>>1, partials[15][0]);
    sums[s30217] = ax_full_adder((sums[s10416]&2)>>1, sums[s10517]&1, (sums[s20316]&2)>>1, vars[630]);
    sums[s30218] = half_adder(sums[s20318]&1, partials[18][0]);
    sums[s30219] = ax_full_adder(sums[s20319]&1, (sums[s20318]&2)>>1, partials[18][1], vars[631]);
    sums[s30220] = ax_full_adder(sums[s20320]&1, (sums[s20319]&2)>>1, sums[s10620]&1, vars[632]);
    sums[s30221] = ax_full_adder(sums[s20321]&1, (sums[s20320]&2)>>1, sums[s20421]&1, vars[633]);
    sums[s30222] = ax_full_adder(sums[s20322]&1, (sums[s20321]&2)>>1, sums[s20422]&1, vars[634]);
    sums[s30223] = ax_full_adder(sums[s20323]&1, (sums[s20322]&2)>>1, sums[s20423]&1, vars[635]);
    sums[s30224] = ax_full_adder(sums[s20324]&1, (sums[s20323]&2)>>1, sums[s20424]&1, vars[636]);
    sums[s30225] = ax_full_adder(sums[s20325]&1, (sums[s20324]&2)>>1, sums[s20425]&1, vars[637]);
    sums[s30226] = ax_full_adder(sums[s20326]&1, (sums[s20325]&2)>>1, sums[s20426]&1, vars[638]);
    sums[s30227] = ax_full_adder(sums[s20327]&1, (sums[s20326]&2)>>1, sums[s20427]&1, vars[639]);
    sums[s30228] = ax_full_adder(sums[s20328]&1, (sums[s20327]&2)>>1, sums[s20428]&1, vars[640]);
    sums[s30229] = ax_full_adder(sums[s20329]&1, (sums[s20328]&2)>>1, sums[s20429]&1, vars[641]);
    sums[s30230] = ax_full_adder(sums[s20330]&1, (sums[s20329]&2)>>1, sums[s20430]&1, vars[642]);
    sums[s30231] = ax_full_adder(sums[s20331]&1, (sums[s20330]&2)>>1, sums[s20431]&1, vars[643]);
    sums[s30232] = ax_full_adder(sums[s20332]&1, (sums[s20331]&2)>>1, sums[s20432]&1, vars[644]);
    sums[s30233] = ax_full_adder(sums[s20333]&1, (sums[s20332]&2)>>1, sums[s20433]&1, vars[645]);
    sums[s30234] = ax_full_adder(sums[s20334]&1, (sums[s20333]&2)>>1, sums[s20434]&1, vars[646]);
    sums[s30235] = ax_full_adder(sums[s20335]&1, (sums[s20334]&2)>>1, sums[s20435]&1, vars[647]);
    sums[s30236] = ax_full_adder(sums[s20336]&1, (sums[s20335]&2)>>1, sums[s20436]&1, vars[648]);
    sums[s30237] = ax_full_adder(sums[s20337]&1, (sums[s20336]&2)>>1, sums[s20437]&1, vars[649]);
    sums[s30238] = ax_full_adder(sums[s20338]&1, (sums[s20337]&2)>>1, sums[s20438]&1, vars[650]);
    sums[s30239] = ax_full_adder(sums[s20339]&1, (sums[s20338]&2)>>1, sums[s20439]&1, vars[651]);
    sums[s30240] = ax_full_adder(sums[s20340]&1, (sums[s20339]&2)>>1, sums[s20440]&1, vars[652]);
    sums[s30241] = ax_full_adder(sums[s20341]&1, (sums[s20340]&2)>>1, sums[s20441]&1, vars[653]);
    sums[s30242] = ax_full_adder(sums[s20342]&1, (sums[s20341]&2)>>1, sums[s10642]&1, vars[654]);
    sums[s30243] = ax_full_adder(sums[s20343]&1, (sums[s20342]&2)>>1, sums[s20443]&1, vars[655]);
    sums[s30244] = ax_full_adder(sums[s20344]&1, (sums[s20343]&2)>>1, partials[31][13], vars[656]);
    sums[s30245] = half_adder(sums[s20345]&1, (sums[s20344]&2)>>1);
    sums[s30246] = ax_full_adder(sums[s20346]&1, (sums[s20345]&2)>>1, (sums[s10545]&2)>>1, vars[657]);
    sums[s30247] = ax_full_adder((sums[s10446]&2)>>1, partials[31][16], (sums[s20346]&2)>>1, vars[658]);
    sums[s30249] = half_adder(partials[31][18], (sums[s10448]&2)>>1);
    sums[s30322] = half_adder((sums[s20421]&2)>>1, partials[22][0]);
    sums[s30324] = ax_full_adder((sums[s20423]&2)>>1, (sums[s10723]&2)>>1, partials[24][0], vars[659]);
    sums[s30325] = half_adder((sums[s20424]&2)>>1, sums[s20525]&1);
    sums[s30326] = ax_full_adder((sums[s20425]&2)>>1, (sums[s10725]&2)>>1, sums[s10826]&1, vars[660]);
    sums[s30327] = ax_full_adder((sums[s20426]&2)>>1, sums[s20527]&1, partials[27][0], vars[661]);
    sums[s30328] = ax_full_adder((sums[s20427]&2)>>1, sums[s20528]&1, (sums[s20527]&2)>>1, vars[662]);
    sums[s30329] = ax_full_adder((sums[s20428]&2)>>1, sums[s20529]&1, (sums[s20528]&2)>>1, vars[663]);
    sums[s30330] = ax_full_adder((sums[s20429]&2)>>1, sums[s20530]&1, (sums[s20529]&2)>>1, vars[664]);
    sums[s30331] = ax_full_adder((sums[s20430]&2)>>1, sums[s20531]&1, (sums[s20530]&2)>>1, vars[665]);
    sums[s30332] = ax_full_adder((sums[s20431]&2)>>1, sums[s20532]&1, (sums[s20531]&2)>>1, vars[666]);
    sums[s30333] = ax_full_adder((sums[s20432]&2)>>1, sums[s20533]&1, (sums[s20532]&2)>>1, vars[667]);
    sums[s30334] = ax_full_adder((sums[s20433]&2)>>1, sums[s20534]&1, (sums[s20533]&2)>>1, vars[668]);
    sums[s30335] = ax_full_adder((sums[s20434]&2)>>1, sums[s20535]&1, (sums[s20534]&2)>>1, vars[669]);
    sums[s30336] = ax_full_adder((sums[s20435]&2)>>1, sums[s20536]&1, (sums[s20535]&2)>>1, vars[670]);
    sums[s30337] = ax_full_adder((sums[s20436]&2)>>1, sums[s20537]&1, (sums[s20536]&2)>>1, vars[671]);
    sums[s30338] = ax_full_adder((sums[s20437]&2)>>1, (sums[s10737]&2)>>1, partials[31][7], vars[672]);
    sums[s30339] = half_adder((sums[s20438]&2)>>1, (sums[s10738]&2)>>1);
    sums[s30340] = ax_full_adder((sums[s20439]&2)>>1, partials[31][9], (sums[s10739]&2)>>1, vars[673]);
    sums[s30342] = half_adder((sums[s10641]&2)>>1, (sums[s20441]&2)>>1);
    sums[s30428] = half_adder(partials[27][1], partials[28][0]);
    sums[s30431] = ax_full_adder(sums[s20631]&1, (sums[s20630]&2)>>1, partials[31][0], vars[674]);
    sums[s30432] = half_adder(sums[s20632]&1, (sums[s20631]&2)>>1);
    sums[s30433] = ax_full_adder(sums[s10933]&1, (sums[s10932]&2)>>1, (sums[s20632]&2)>>1, vars[675]);
    sums[s30435] = half_adder(partials[31][4], (sums[s20634]&2)>>1);
    sums[s40006] = ax_full_adder(sums[s30006]&1, (sums[s30005]&2)>>1, partials[6][0], vars[676]);
    sums[s40008] = ax_full_adder(sums[s30008]&1, (sums[s30007]&2)>>1, sums[s30108]&1, vars[677]);
    sums[s40009] = ax_full_adder(sums[s30009]&1, (sums[s30008]&2)>>1, partials[9][0], vars[678]);
    sums[s40010] = ax_full_adder(sums[s30010]&1, (sums[s30009]&2)>>1, sums[s30110]&1, vars[679]);
    sums[s40011] = ax_full_adder(sums[s30011]&1, (sums[s30010]&2)>>1, sums[s30111]&1, vars[680]);
    sums[s40012] = ax_full_adder(sums[s30012]&1, (sums[s30011]&2)>>1, sums[s30112]&1, vars[681]);
    sums[s40013] = ax_full_adder(sums[s30013]&1, (sums[s30012]&2)>>1, sums[s30113]&1, vars[682]);
    sums[s40014] = ax_full_adder(sums[s30014]&1, (sums[s30013]&2)>>1, sums[s30114]&1, vars[683]);
    sums[s40015] = ax_full_adder(sums[s30015]&1, (sums[s30014]&2)>>1, sums[s30115]&1, vars[684]);
    sums[s40016] = ax_full_adder(sums[s30016]&1, (sums[s30015]&2)>>1, sums[s30116]&1, vars[685]);
    sums[s40017] = ax_full_adder(sums[s30017]&1, (sums[s30016]&2)>>1, sums[s30117]&1, vars[686]);
    sums[s40018] = ax_full_adder(sums[s30018]&1, (sums[s30017]&2)>>1, sums[s30118]&1, vars[687]);
    sums[s40019] = ax_full_adder(sums[s30019]&1, (sums[s30018]&2)>>1, sums[s30119]&1, vars[688]);
    sums[s40020] = ax_full_adder(sums[s30020]&1, (sums[s30019]&2)>>1, sums[s30120]&1, vars[689]);
    sums[s40021] = ax_full_adder(sums[s30021]&1, (sums[s30020]&2)>>1, sums[s30121]&1, vars[690]);
    sums[s40022] = ax_full_adder(sums[s30022]&1, (sums[s30021]&2)>>1, sums[s30122]&1, vars[691]);
    sums[s40023] = ax_full_adder(sums[s30023]&1, (sums[s30022]&2)>>1, sums[s30123]&1, vars[692]);
    sums[s40024] = ax_full_adder(sums[s30024]&1, (sums[s30023]&2)>>1, sums[s30124]&1, vars[693]);
    sums[s40025] = ax_full_adder(sums[s30025]&1, (sums[s30024]&2)>>1, sums[s30125]&1, vars[694]);
    sums[s40026] = ax_full_adder(sums[s30026]&1, (sums[s30025]&2)>>1, sums[s30126]&1, vars[695]);
    sums[s40027] = ax_full_adder(sums[s30027]&1, (sums[s30026]&2)>>1, sums[s30127]&1, vars[696]);
    sums[s40028] = ax_full_adder(sums[s30028]&1, (sums[s30027]&2)>>1, sums[s30128]&1, vars[697]);
    sums[s40029] = ax_full_adder(sums[s30029]&1, (sums[s30028]&2)>>1, sums[s30129]&1, vars[698]);
    sums[s40030] = ax_full_adder(sums[s30030]&1, (sums[s30029]&2)>>1, sums[s30130]&1, vars[699]);
    sums[s40031] = ax_full_adder(sums[s30031]&1, (sums[s30030]&2)>>1, sums[s30131]&1, vars[700]);
    sums[s40032] = ax_full_adder(sums[s30032]&1, (sums[s30031]&2)>>1, sums[s30132]&1, vars[701]);
    sums[s40033] = ax_full_adder(sums[s30033]&1, (sums[s30032]&2)>>1, sums[s30133]&1, vars[702]);
    sums[s40034] = ax_full_adder(sums[s30034]&1, (sums[s30033]&2)>>1, sums[s30134]&1, vars[703]);
    sums[s40035] = ax_full_adder(sums[s30035]&1, (sums[s30034]&2)>>1, sums[s30135]&1, vars[704]);
    sums[s40036] = ax_full_adder(sums[s30036]&1, (sums[s30035]&2)>>1, sums[s30136]&1, vars[705]);
    sums[s40037] = ax_full_adder(sums[s30037]&1, (sums[s30036]&2)>>1, sums[s30137]&1, vars[706]);
    sums[s40038] = ax_full_adder(sums[s30038]&1, (sums[s30037]&2)>>1, sums[s30138]&1, vars[707]);
    sums[s40039] = ax_full_adder(sums[s30039]&1, (sums[s30038]&2)>>1, sums[s30139]&1, vars[708]);
    sums[s40040] = ax_full_adder(sums[s30040]&1, (sums[s30039]&2)>>1, sums[s30140]&1, vars[709]);
    sums[s40041] = ax_full_adder(sums[s30041]&1, (sums[s30040]&2)>>1, sums[s30141]&1, vars[710]);
    sums[s40042] = ax_full_adder(sums[s30042]&1, (sums[s30041]&2)>>1, sums[s30142]&1, vars[711]);
    sums[s40043] = ax_full_adder(sums[s30043]&1, (sums[s30042]&2)>>1, sums[s30143]&1, vars[712]);
    sums[s40044] = ax_full_adder(sums[s30044]&1, (sums[s30043]&2)>>1, sums[s30144]&1, vars[713]);
    sums[s40045] = ax_full_adder(sums[s30045]&1, (sums[s30044]&2)>>1, sums[s30145]&1, vars[714]);
    sums[s40046] = ax_full_adder(sums[s30046]&1, (sums[s30045]&2)>>1, sums[s30146]&1, vars[715]);
    sums[s40047] = ax_full_adder(sums[s30047]&1, (sums[s30046]&2)>>1, sums[s30147]&1, vars[716]);
    sums[s40048] = ax_full_adder(sums[s30048]&1, (sums[s30047]&2)>>1, sums[s30148]&1, vars[717]);
    sums[s40049] = ax_full_adder(sums[s30049]&1, (sums[s30048]&2)>>1, sums[s30149]&1, vars[718]);
    sums[s40050] = ax_full_adder(sums[s30050]&1, (sums[s30049]&2)>>1, sums[s30150]&1, vars[719]);
    sums[s40051] = ax_full_adder(sums[s30051]&1, (sums[s30050]&2)>>1, sums[s30151]&1, vars[720]);
    sums[s40052] = ax_full_adder(sums[s30052]&1, (sums[s30051]&2)>>1, sums[s30152]&1, vars[721]);
    sums[s40053] = ax_full_adder(sums[s30053]&1, (sums[s30052]&2)>>1, sums[s30153]&1, vars[722]);
    sums[s40054] = ax_full_adder(sums[s30054]&1, (sums[s30053]&2)>>1, (sums[s20153]&2)>>1, vars[723]);
    sums[s40055] = ax_full_adder(sums[s30055]&1, (sums[s30054]&2)>>1, sums[s30155]&1, vars[724]);
    sums[s40056] = ax_full_adder(sums[s30056]&1, (sums[s30055]&2)>>1, sums[s30156]&1, vars[725]);
    sums[s40057] = ax_full_adder(sums[s30057]&1, (sums[s30056]&2)>>1, (sums[s30156]&2)>>1, vars[726]);
    sums[s40058] = ax_full_adder(sums[s30058]&1, (sums[s30057]&2)>>1, (sums[s10157]&2)>>1, vars[727]);
    sums[s40116] = ax_full_adder((sums[s30115]&2)>>1, sums[s20316]&1, (sums[s30215]&2)>>1, vars[728]);
    sums[s40118] = ax_full_adder((sums[s30117]&2)>>1, sums[s30218]&1, (sums[s30217]&2)>>1, vars[729]);
    sums[s40119] = ax_full_adder((sums[s30118]&2)>>1, sums[s30219]&1, (sums[s30218]&2)>>1, vars[730]);
    sums[s40120] = ax_full_adder((sums[s30119]&2)>>1, sums[s30220]&1, (sums[s30219]&2)>>1, vars[731]);
    sums[s40121] = ax_full_adder((sums[s30120]&2)>>1, sums[s30221]&1, (sums[s30220]&2)>>1, vars[732]);
    sums[s40122] = ax_full_adder((sums[s30121]&2)>>1, sums[s30222]&1, (sums[s30221]&2)>>1, vars[733]);
    sums[s40123] = ax_full_adder((sums[s30122]&2)>>1, sums[s30223]&1, (sums[s30222]&2)>>1, vars[734]);
    sums[s40124] = ax_full_adder((sums[s30123]&2)>>1, sums[s30224]&1, (sums[s30223]&2)>>1, vars[735]);
    sums[s40125] = ax_full_adder((sums[s30124]&2)>>1, sums[s30225]&1, (sums[s30224]&2)>>1, vars[736]);
    sums[s40126] = ax_full_adder((sums[s30125]&2)>>1, sums[s30226]&1, (sums[s30225]&2)>>1, vars[737]);
    sums[s40127] = ax_full_adder((sums[s30126]&2)>>1, sums[s30227]&1, (sums[s30226]&2)>>1, vars[738]);
    sums[s40128] = ax_full_adder((sums[s30127]&2)>>1, sums[s30228]&1, (sums[s30227]&2)>>1, vars[739]);
    sums[s40129] = ax_full_adder((sums[s30128]&2)>>1, sums[s30229]&1, (sums[s30228]&2)>>1, vars[740]);
    sums[s40130] = ax_full_adder((sums[s30129]&2)>>1, sums[s30230]&1, (sums[s30229]&2)>>1, vars[741]);
    sums[s40131] = ax_full_adder((sums[s30130]&2)>>1, sums[s30231]&1, (sums[s30230]&2)>>1, vars[742]);
    sums[s40132] = ax_full_adder((sums[s30131]&2)>>1, sums[s30232]&1, (sums[s30231]&2)>>1, vars[743]);
    sums[s40133] = ax_full_adder((sums[s30132]&2)>>1, sums[s30233]&1, (sums[s30232]&2)>>1, vars[744]);
    sums[s40134] = ax_full_adder((sums[s30133]&2)>>1, sums[s30234]&1, (sums[s30233]&2)>>1, vars[745]);
    sums[s40135] = ax_full_adder((sums[s30134]&2)>>1, sums[s30235]&1, (sums[s30234]&2)>>1, vars[746]);
    sums[s40136] = ax_full_adder((sums[s30135]&2)>>1, sums[s30236]&1, (sums[s30235]&2)>>1, vars[747]);
    sums[s40137] = ax_full_adder((sums[s30136]&2)>>1, sums[s30237]&1, (sums[s30236]&2)>>1, vars[748]);
    sums[s40138] = ax_full_adder((sums[s30137]&2)>>1, sums[s30238]&1, (sums[s30237]&2)>>1, vars[749]);
    sums[s40139] = ax_full_adder((sums[s30138]&2)>>1, sums[s30239]&1, (sums[s30238]&2)>>1, vars[750]);
    sums[s40140] = ax_full_adder((sums[s30139]&2)>>1, sums[s30240]&1, (sums[s30239]&2)>>1, vars[751]);
    sums[s40141] = ax_full_adder((sums[s30140]&2)>>1, sums[s30241]&1, (sums[s30240]&2)>>1, vars[752]);
    sums[s40142] = ax_full_adder((sums[s30141]&2)>>1, sums[s30242]&1, (sums[s30241]&2)>>1, vars[753]);
    sums[s40143] = ax_full_adder((sums[s30142]&2)>>1, sums[s30243]&1, (sums[s30242]&2)>>1, vars[754]);
    sums[s40144] = ax_full_adder((sums[s30143]&2)>>1, sums[s30244]&1, (sums[s30243]&2)>>1, vars[755]);
    sums[s40145] = ax_full_adder((sums[s30144]&2)>>1, sums[s30245]&1, (sums[s30244]&2)>>1, vars[756]);
    sums[s40146] = ax_full_adder((sums[s30145]&2)>>1, sums[s30246]&1, (sums[s30245]&2)>>1, vars[757]);
    sums[s40147] = ax_full_adder((sums[s30146]&2)>>1, sums[s30247]&1, (sums[s30246]&2)>>1, vars[758]);
    sums[s40148] = ax_full_adder((sums[s30147]&2)>>1, (sums[s10447]&2)>>1, (sums[s30247]&2)>>1, vars[759]);
    sums[s40226] = ax_full_adder(sums[s30326]&1, (sums[s30325]&2)>>1, (sums[s20525]&2)>>1, vars[760]);
    sums[s40228] = ax_full_adder(sums[s30328]&1, (sums[s30327]&2)>>1, sums[s30428]&1, vars[761]);
    sums[s40229] = ax_full_adder(sums[s30329]&1, (sums[s30328]&2)>>1, sums[s10929]&1, vars[762]);
    sums[s40230] = ax_full_adder(sums[s30330]&1, (sums[s30329]&2)>>1, sums[s20630]&1, vars[763]);
    sums[s40231] = ax_full_adder(sums[s30331]&1, (sums[s30330]&2)>>1, sums[s30431]&1, vars[764]);
    sums[s40232] = ax_full_adder(sums[s30332]&1, (sums[s30331]&2)>>1, sums[s30432]&1, vars[765]);
    sums[s40233] = ax_full_adder(sums[s30333]&1, (sums[s30332]&2)>>1, sums[s30433]&1, vars[766]);
    sums[s40234] = ax_full_adder(sums[s30334]&1, (sums[s30333]&2)>>1, sums[s20634]&1, vars[767]);
    sums[s40235] = ax_full_adder(sums[s30335]&1, (sums[s30334]&2)>>1, sums[s30435]&1, vars[768]);
    sums[s40236] = ax_full_adder(sums[s30336]&1, (sums[s30335]&2)>>1, (sums[s30435]&2)>>1, vars[769]);
    sums[s40237] = ax_full_adder(sums[s30337]&1, (sums[s30336]&2)>>1, (sums[s10836]&2)>>1, vars[770]);
    sums[s40238] = ax_full_adder(sums[s30338]&1, (sums[s30337]&2)>>1, (sums[s20537]&2)>>1, vars[771]);
    sums[s50007] = ax_full_adder(sums[s30007]&1, (sums[s30006]&2)>>1, (sums[s40006]&2)>>1, vars[772]);
    sums[s50009] = ax_full_adder(sums[s40009]&1, (sums[s40008]&2)>>1, (sums[s30108]&2)>>1, vars[773]);
    sums[s50011] = ax_full_adder(sums[s40011]&1, (sums[s40010]&2)>>1, (sums[s30110]&2)>>1, vars[774]);
    sums[s50012] = ax_full_adder(sums[s40012]&1, (sums[s40011]&2)>>1, (sums[s30111]&2)>>1, vars[775]);
    sums[s50013] = ax_full_adder(sums[s40013]&1, (sums[s40012]&2)>>1, (sums[s30112]&2)>>1, vars[776]);
    sums[s50014] = ax_full_adder(sums[s40014]&1, (sums[s40013]&2)>>1, (sums[s30113]&2)>>1, vars[777]);
    sums[s50015] = ax_full_adder(sums[s40015]&1, (sums[s40014]&2)>>1, (sums[s30114]&2)>>1, vars[778]);
    sums[s50016] = ax_full_adder(sums[s40016]&1, (sums[s40015]&2)>>1, sums[s40116]&1, vars[779]);
    sums[s50017] = ax_full_adder(sums[s40017]&1, (sums[s40016]&2)>>1, (sums[s30116]&2)>>1, vars[780]);
    sums[s50018] = ax_full_adder(sums[s40018]&1, (sums[s40017]&2)>>1, sums[s40118]&1, vars[781]);
    sums[s50019] = ax_full_adder(sums[s40019]&1, (sums[s40018]&2)>>1, sums[s40119]&1, vars[782]);
    sums[s50020] = ax_full_adder(sums[s40020]&1, (sums[s40019]&2)>>1, sums[s40120]&1, vars[783]);
    sums[s50021] = ax_full_adder(sums[s40021]&1, (sums[s40020]&2)>>1, sums[s40121]&1, vars[784]);
    sums[s50022] = ax_full_adder(sums[s40022]&1, (sums[s40021]&2)>>1, sums[s40122]&1, vars[785]);
    sums[s50023] = ax_full_adder(sums[s40023]&1, (sums[s40022]&2)>>1, sums[s40123]&1, vars[786]);
    sums[s50024] = ax_full_adder(sums[s40024]&1, (sums[s40023]&2)>>1, sums[s40124]&1, vars[787]);
    sums[s50025] = ax_full_adder(sums[s40025]&1, (sums[s40024]&2)>>1, sums[s40125]&1, vars[788]);
    sums[s50026] = ax_full_adder(sums[s40026]&1, (sums[s40025]&2)>>1, sums[s40126]&1, vars[789]);
    sums[s50027] = ax_full_adder(sums[s40027]&1, (sums[s40026]&2)>>1, sums[s40127]&1, vars[790]);
    sums[s50028] = ax_full_adder(sums[s40028]&1, (sums[s40027]&2)>>1, sums[s40128]&1, vars[791]);
    sums[s50029] = ax_full_adder(sums[s40029]&1, (sums[s40028]&2)>>1, sums[s40129]&1, vars[792]);
    sums[s50030] = ax_full_adder(sums[s40030]&1, (sums[s40029]&2)>>1, sums[s40130]&1, vars[793]);
    sums[s50031] = ax_full_adder(sums[s40031]&1, (sums[s40030]&2)>>1, sums[s40131]&1, vars[794]);
    sums[s50032] = ax_full_adder(sums[s40032]&1, (sums[s40031]&2)>>1, sums[s40132]&1, vars[795]);
    sums[s50033] = ax_full_adder(sums[s40033]&1, (sums[s40032]&2)>>1, sums[s40133]&1, vars[796]);
    sums[s50034] = ax_full_adder(sums[s40034]&1, (sums[s40033]&2)>>1, sums[s40134]&1, vars[797]);
    sums[s50035] = ax_full_adder(sums[s40035]&1, (sums[s40034]&2)>>1, sums[s40135]&1, vars[798]);
    sums[s50036] = ax_full_adder(sums[s40036]&1, (sums[s40035]&2)>>1, sums[s40136]&1, vars[799]);
    sums[s50037] = ax_full_adder(sums[s40037]&1, (sums[s40036]&2)>>1, sums[s40137]&1, vars[800]);
    sums[s50038] = ax_full_adder(sums[s40038]&1, (sums[s40037]&2)>>1, sums[s40138]&1, vars[801]);
    sums[s50039] = ax_full_adder(sums[s40039]&1, (sums[s40038]&2)>>1, sums[s40139]&1, vars[802]);
    sums[s50040] = ax_full_adder(sums[s40040]&1, (sums[s40039]&2)>>1, sums[s40140]&1, vars[803]);
    sums[s50041] = ax_full_adder(sums[s40041]&1, (sums[s40040]&2)>>1, sums[s40141]&1, vars[804]);
    sums[s50042] = ax_full_adder(sums[s40042]&1, (sums[s40041]&2)>>1, sums[s40142]&1, vars[805]);
    sums[s50043] = ax_full_adder(sums[s40043]&1, (sums[s40042]&2)>>1, sums[s40143]&1, vars[806]);
    sums[s50044] = ax_full_adder(sums[s40044]&1, (sums[s40043]&2)>>1, sums[s40144]&1, vars[807]);
    sums[s50045] = ax_full_adder(sums[s40045]&1, (sums[s40044]&2)>>1, sums[s40145]&1, vars[808]);
    sums[s50046] = ax_full_adder(sums[s40046]&1, (sums[s40045]&2)>>1, sums[s40146]&1, vars[809]);
    sums[s50047] = ax_full_adder(sums[s40047]&1, (sums[s40046]&2)>>1, sums[s40147]&1, vars[810]);
    sums[s50048] = ax_full_adder(sums[s40048]&1, (sums[s40047]&2)>>1, sums[s40148]&1, vars[811]);
    sums[s50049] = ax_full_adder(sums[s40049]&1, (sums[s40048]&2)>>1, (sums[s30148]&2)>>1, vars[812]);
    sums[s50050] = ax_full_adder(sums[s40050]&1, (sums[s40049]&2)>>1, (sums[s30149]&2)>>1, vars[813]);
    sums[s50051] = ax_full_adder(sums[s40051]&1, (sums[s40050]&2)>>1, (sums[s30150]&2)>>1, vars[814]);
    sums[s50052] = ax_full_adder(sums[s40052]&1, (sums[s40051]&2)>>1, (sums[s30151]&2)>>1, vars[815]);
    sums[s50053] = ax_full_adder(sums[s40053]&1, (sums[s40052]&2)>>1, (sums[s30152]&2)>>1, vars[816]);
    sums[s50054] = ax_full_adder(sums[s40054]&1, (sums[s40053]&2)>>1, (sums[s30153]&2)>>1, vars[817]);
    sums[s50056] = ax_full_adder(sums[s40056]&1, (sums[s40055]&2)>>1, (sums[s30155]&2)>>1, vars[818]);
    sums[s50059] = ax_full_adder(sums[s30059]&1, (sums[s30058]&2)>>1, (sums[s40058]&2)>>1, vars[819]);
    sums[s50123] = ax_full_adder((sums[s40122]&2)>>1, (sums[s20422]&2)>>1, (sums[s30322]&2)>>1, vars[820]);
    sums[s50125] = ax_full_adder((sums[s40124]&2)>>1, sums[s30325]&1, (sums[s30324]&2)>>1, vars[821]);
    sums[s50127] = ax_full_adder((sums[s40126]&2)>>1, sums[s30327]&1, (sums[s30326]&2)>>1, vars[822]);
    sums[s50129] = ax_full_adder((sums[s40128]&2)>>1, sums[s40229]&1, (sums[s40228]&2)>>1, vars[823]);
    sums[s50130] = ax_full_adder((sums[s40129]&2)>>1, sums[s40230]&1, (sums[s40229]&2)>>1, vars[824]);
    sums[s50131] = ax_full_adder((sums[s40130]&2)>>1, sums[s40231]&1, (sums[s40230]&2)>>1, vars[825]);
    sums[s50132] = ax_full_adder((sums[s40131]&2)>>1, sums[s40232]&1, (sums[s40231]&2)>>1, vars[826]);
    sums[s50133] = ax_full_adder((sums[s40132]&2)>>1, sums[s40233]&1, (sums[s40232]&2)>>1, vars[827]);
    sums[s50134] = ax_full_adder((sums[s40133]&2)>>1, sums[s40234]&1, (sums[s40233]&2)>>1, vars[828]);
    sums[s50135] = ax_full_adder((sums[s40134]&2)>>1, sums[s40235]&1, (sums[s40234]&2)>>1, vars[829]);
    sums[s50136] = ax_full_adder((sums[s40135]&2)>>1, sums[s40236]&1, (sums[s40235]&2)>>1, vars[830]);
    sums[s50137] = ax_full_adder((sums[s40136]&2)>>1, sums[s40237]&1, (sums[s40236]&2)>>1, vars[831]);
    sums[s50138] = ax_full_adder((sums[s40137]&2)>>1, sums[s40238]&1, (sums[s40237]&2)>>1, vars[832]);
    sums[s50139] = ax_full_adder((sums[s40138]&2)>>1, sums[s30339]&1, (sums[s30338]&2)>>1, vars[833]);
    sums[s50140] = ax_full_adder((sums[s40139]&2)>>1, sums[s30340]&1, (sums[s30339]&2)>>1, vars[834]);
    sums[s50141] = ax_full_adder((sums[s40140]&2)>>1, (sums[s20440]&2)>>1, (sums[s30340]&2)>>1, vars[835]);
    sums[s60010] = ax_full_adder(sums[s40010]&1, (sums[s40009]&2)>>1, (sums[s50009]&2)>>1, vars[836]);
    sums[s60013] = ax_full_adder(sums[s50013]&1, (sums[s50012]&2)>>1, partials[13][0], vars[837]);
    sums[s60015] = ax_full_adder(sums[s50015]&1, (sums[s50014]&2)>>1, sums[s30215]&1, vars[838]);
    sums[s60017] = ax_full_adder(sums[s50017]&1, (sums[s50016]&2)>>1, sums[s30217]&1, vars[839]);
    sums[s60019] = ax_full_adder(sums[s50019]&1, (sums[s50018]&2)>>1, (sums[s40118]&2)>>1, vars[840]);
    sums[s60020] = ax_full_adder(sums[s50020]&1, (sums[s50019]&2)>>1, (sums[s40119]&2)>>1, vars[841]);
    sums[s60021] = ax_full_adder(sums[s50021]&1, (sums[s50020]&2)>>1, (sums[s40120]&2)>>1, vars[842]);
    sums[s60022] = ax_full_adder(sums[s50022]&1, (sums[s50021]&2)>>1, (sums[s40121]&2)>>1, vars[843]);
    sums[s60023] = ax_full_adder(sums[s50023]&1, (sums[s50022]&2)>>1, sums[s50123]&1, vars[844]);
    sums[s60024] = ax_full_adder(sums[s50024]&1, (sums[s50023]&2)>>1, (sums[s40123]&2)>>1, vars[845]);
    sums[s60025] = ax_full_adder(sums[s50025]&1, (sums[s50024]&2)>>1, sums[s50125]&1, vars[846]);
    sums[s60026] = ax_full_adder(sums[s50026]&1, (sums[s50025]&2)>>1, (sums[s40125]&2)>>1, vars[847]);
    sums[s60027] = ax_full_adder(sums[s50027]&1, (sums[s50026]&2)>>1, sums[s50127]&1, vars[848]);
    sums[s60028] = ax_full_adder(sums[s50028]&1, (sums[s50027]&2)>>1, (sums[s40127]&2)>>1, vars[849]);
    sums[s60029] = ax_full_adder(sums[s50029]&1, (sums[s50028]&2)>>1, sums[s50129]&1, vars[850]);
    sums[s60030] = ax_full_adder(sums[s50030]&1, (sums[s50029]&2)>>1, sums[s50130]&1, vars[851]);
    sums[s60031] = ax_full_adder(sums[s50031]&1, (sums[s50030]&2)>>1, sums[s50131]&1, vars[852]);
    sums[s60032] = ax_full_adder(sums[s50032]&1, (sums[s50031]&2)>>1, sums[s50132]&1, vars[853]);
    sums[s60033] = ax_full_adder(sums[s50033]&1, (sums[s50032]&2)>>1, sums[s50133]&1, vars[854]);
    sums[s60034] = ax_full_adder(sums[s50034]&1, (sums[s50033]&2)>>1, sums[s50134]&1, vars[855]);
    sums[s60035] = ax_full_adder(sums[s50035]&1, (sums[s50034]&2)>>1, sums[s50135]&1, vars[856]);
    sums[s60036] = ax_full_adder(sums[s50036]&1, (sums[s50035]&2)>>1, sums[s50136]&1, vars[857]);
    sums[s60037] = ax_full_adder(sums[s50037]&1, (sums[s50036]&2)>>1, sums[s50137]&1, vars[858]);
    sums[s60038] = ax_full_adder(sums[s50038]&1, (sums[s50037]&2)>>1, sums[s50138]&1, vars[859]);
    sums[s60039] = ax_full_adder(sums[s50039]&1, (sums[s50038]&2)>>1, sums[s50139]&1, vars[860]);
    sums[s60040] = ax_full_adder(sums[s50040]&1, (sums[s50039]&2)>>1, sums[s50140]&1, vars[861]);
    sums[s60041] = ax_full_adder(sums[s50041]&1, (sums[s50040]&2)>>1, sums[s50141]&1, vars[862]);
    sums[s60042] = ax_full_adder(sums[s50042]&1, (sums[s50041]&2)>>1, (sums[s40141]&2)>>1, vars[863]);
    sums[s60043] = ax_full_adder(sums[s50043]&1, (sums[s50042]&2)>>1, (sums[s40142]&2)>>1, vars[864]);
    sums[s60044] = ax_full_adder(sums[s50044]&1, (sums[s50043]&2)>>1, (sums[s40143]&2)>>1, vars[865]);
    sums[s60045] = ax_full_adder(sums[s50045]&1, (sums[s50044]&2)>>1, (sums[s40144]&2)>>1, vars[866]);
    sums[s60046] = ax_full_adder(sums[s50046]&1, (sums[s50045]&2)>>1, (sums[s40145]&2)>>1, vars[867]);
    sums[s60047] = ax_full_adder(sums[s50047]&1, (sums[s50046]&2)>>1, (sums[s40146]&2)>>1, vars[868]);
    sums[s60048] = ax_full_adder(sums[s50048]&1, (sums[s50047]&2)>>1, (sums[s40147]&2)>>1, vars[869]);
    sums[s60049] = ax_full_adder(sums[s50049]&1, (sums[s50048]&2)>>1, sums[s30249]&1, vars[870]);
    sums[s60050] = ax_full_adder(sums[s50050]&1, (sums[s50049]&2)>>1, (sums[s30249]&2)>>1, vars[871]);
    sums[s60051] = ax_full_adder(sums[s50051]&1, (sums[s50050]&2)>>1, (sums[s20250]&2)>>1, vars[872]);
    sums[s60055] = ax_full_adder(sums[s40055]&1, (sums[s40054]&2)>>1, (sums[s50054]&2)>>1, vars[873]);
    sums[s60057] = ax_full_adder(sums[s40057]&1, (sums[s40056]&2)>>1, (sums[s50056]&2)>>1, vars[874]);
    sums[s60060] = ax_full_adder(sums[s30060]&1, (sums[s30059]&2)>>1, (sums[s50059]&2)>>1, vars[875]);
    sums[s70014] = ax_full_adder(sums[s50014]&1, (sums[s50013]&2)>>1, (sums[s60013]&2)>>1, vars[876]);
    sums[s70016] = ax_full_adder(sums[s50016]&1, (sums[s50015]&2)>>1, (sums[s60015]&2)>>1, vars[877]);
    sums[s70018] = ax_full_adder(sums[s50018]&1, (sums[s50017]&2)>>1, (sums[s60017]&2)>>1, vars[878]);
    sums[s70022] = ax_full_adder(sums[s60022]&1, (sums[s60021]&2)>>1, sums[s30322]&1, vars[879]);
    sums[s70024] = ax_full_adder(sums[s60024]&1, (sums[s60023]&2)>>1, sums[s30324]&1, vars[880]);
    sums[s70026] = ax_full_adder(sums[s60026]&1, (sums[s60025]&2)>>1, sums[s40226]&1, vars[881]);
    sums[s70027] = ax_full_adder(sums[s60027]&1, (sums[s60026]&2)>>1, (sums[s40226]&2)>>1, vars[882]);
    sums[s70028] = ax_full_adder(sums[s60028]&1, (sums[s60027]&2)>>1, sums[s40228]&1, vars[883]);
    sums[s70029] = ax_full_adder(sums[s60029]&1, (sums[s60028]&2)>>1, (sums[s30428]&2)>>1, vars[884]);
    sums[s70030] = ax_full_adder(sums[s60030]&1, (sums[s60029]&2)>>1, (sums[s50129]&2)>>1, vars[885]);
    sums[s70031] = ax_full_adder(sums[s60031]&1, (sums[s60030]&2)>>1, (sums[s50130]&2)>>1, vars[886]);
    sums[s70032] = ax_full_adder(sums[s60032]&1, (sums[s60031]&2)>>1, (sums[s50131]&2)>>1, vars[887]);
    sums[s70033] = ax_full_adder(sums[s60033]&1, (sums[s60032]&2)>>1, (sums[s50132]&2)>>1, vars[888]);
    sums[s70034] = ax_full_adder(sums[s60034]&1, (sums[s60033]&2)>>1, (sums[s50133]&2)>>1, vars[889]);
    sums[s70035] = ax_full_adder(sums[s60035]&1, (sums[s60034]&2)>>1, (sums[s50134]&2)>>1, vars[890]);
    sums[s70036] = ax_full_adder(sums[s60036]&1, (sums[s60035]&2)>>1, (sums[s50135]&2)>>1, vars[891]);
    sums[s70037] = ax_full_adder(sums[s60037]&1, (sums[s60036]&2)>>1, (sums[s50136]&2)>>1, vars[892]);
    sums[s70038] = ax_full_adder(sums[s60038]&1, (sums[s60037]&2)>>1, (sums[s50137]&2)>>1, vars[893]);
    sums[s70039] = ax_full_adder(sums[s60039]&1, (sums[s60038]&2)>>1, (sums[s50138]&2)>>1, vars[894]);
    sums[s70040] = ax_full_adder(sums[s60040]&1, (sums[s60039]&2)>>1, (sums[s50139]&2)>>1, vars[895]);
    sums[s70041] = ax_full_adder(sums[s60041]&1, (sums[s60040]&2)>>1, (sums[s50140]&2)>>1, vars[896]);
    sums[s70042] = ax_full_adder(sums[s60042]&1, (sums[s60041]&2)>>1, sums[s30342]&1, vars[897]);
    sums[s70043] = ax_full_adder(sums[s60043]&1, (sums[s60042]&2)>>1, (sums[s30342]&2)>>1, vars[898]);
    sums[s70044] = ax_full_adder(sums[s60044]&1, (sums[s60043]&2)>>1, (sums[s20443]&2)>>1, vars[899]);
    sums[s70049] = ax_full_adder(sums[s60049]&1, (sums[s60048]&2)>>1, (sums[s40148]&2)>>1, vars[900]);
    sums[s70052] = ax_full_adder(sums[s50052]&1, (sums[s50051]&2)>>1, (sums[s60051]&2)>>1, vars[901]);
    sums[s70058] = ax_full_adder(sums[s40058]&1, (sums[s40057]&2)>>1, (sums[s60057]&2)>>1, vars[902]);
    sums[s70061] = ax_full_adder(sums[s20061]&1, (sums[s30060]&2)>>1, (sums[s60060]&2)>>1, vars[903]);
    sums[s80017] = ax_full_adder(sums[s60017]&1, (sums[s40116]&2)>>1, (sums[s70016]&2)>>1, vars[904]);
    sums[s80019] = ax_full_adder(sums[s60019]&1, partials[19][0], (sums[s70018]&2)>>1, vars[905]);
    sums[s80020] = half_adder(sums[s60020]&1, (sums[s60019]&2)>>1);
    sums[s80021] = half_adder(sums[s60021]&1, (sums[s60020]&2)>>1);
    sums[s80023] = ax_full_adder(sums[s60023]&1, (sums[s60022]&2)>>1, (sums[s70022]&2)>>1, vars[906]);
    sums[s80024] = half_adder(sums[s70024]&1, (sums[s50123]&2)>>1);
    sums[s80025] = ax_full_adder(sums[s60025]&1, (sums[s60024]&2)>>1, (sums[s70024]&2)>>1, vars[907]);
    sums[s80026] = half_adder(sums[s70026]&1, (sums[s50125]&2)>>1);
    sums[s80027] = half_adder(sums[s70027]&1, (sums[s70026]&2)>>1);
    sums[s80028] = ax_full_adder(sums[s70028]&1, (sums[s70027]&2)>>1, (sums[s50127]&2)>>1, vars[908]);
    sums[s80029] = half_adder(sums[s70029]&1, (sums[s70028]&2)>>1);
    sums[s80030] = half_adder(sums[s70030]&1, (sums[s70029]&2)>>1);
    sums[s80031] = half_adder(sums[s70031]&1, (sums[s70030]&2)>>1);
    sums[s80032] = ax_full_adder(sums[s70032]&1, (sums[s70031]&2)>>1, (sums[s30431]&2)>>1, vars[909]);
    sums[s80033] = ax_full_adder(sums[s70033]&1, (sums[s70032]&2)>>1, (sums[s30432]&2)>>1, vars[910]);
    sums[s80034] = ax_full_adder(sums[s70034]&1, (sums[s70033]&2)>>1, (sums[s30433]&2)>>1, vars[911]);
    sums[s80035] = half_adder(sums[s70035]&1, (sums[s70034]&2)>>1);
    sums[s80036] = half_adder(sums[s70036]&1, (sums[s70035]&2)>>1);
    sums[s80037] = half_adder(sums[s70037]&1, (sums[s70036]&2)>>1);
    sums[s80038] = half_adder(sums[s70038]&1, (sums[s70037]&2)>>1);
    sums[s80039] = ax_full_adder(sums[s70039]&1, (sums[s70038]&2)>>1, (sums[s40238]&2)>>1, vars[912]);
    sums[s80040] = half_adder(sums[s70040]&1, (sums[s70039]&2)>>1);
    sums[s80041] = half_adder(sums[s70041]&1, (sums[s70040]&2)>>1);
    sums[s80042] = ax_full_adder(sums[s70042]&1, (sums[s70041]&2)>>1, (sums[s50141]&2)>>1, vars[913]);
    sums[s80043] = half_adder(sums[s70043]&1, (sums[s70042]&2)>>1);
    sums[s80044] = half_adder(sums[s70044]&1, (sums[s70043]&2)>>1);
    sums[s80045] = ax_full_adder(sums[s60045]&1, (sums[s60044]&2)>>1, (sums[s70044]&2)>>1, vars[914]);
    sums[s80046] = half_adder(sums[s60046]&1, (sums[s60045]&2)>>1);
    sums[s80047] = half_adder(sums[s60047]&1, (sums[s60046]&2)>>1);
    sums[s80048] = half_adder(sums[s60048]&1, (sums[s60047]&2)>>1);
    sums[s80050] = ax_full_adder(sums[s60050]&1, (sums[s60049]&2)>>1, (sums[s70049]&2)>>1, vars[915]);
    sums[s80051] = half_adder(sums[s60051]&1, (sums[s60050]&2)>>1);
    sums[s80053] = ax_full_adder(sums[s50053]&1, (sums[s50052]&2)>>1, (sums[s70052]&2)>>1, vars[916]);
    sums[s80054] = half_adder(sums[s50054]&1, (sums[s50053]&2)>>1);
    sums[s80062] = ax_full_adder(partials[31][31], (sums[s20061]&2)>>1, (sums[s70061]&2)>>1, vars[917]);

    // place final sums in outputs, generated by "/code generation tools/cpp_gen.py"
    prodA |= ((int)partials[0][0]);
    prodA |= ((int)partials[0][1]) << 1;
    prodA |= (sums[s10002]&1) << 2;
    prodA |= (sums[s20003]&1) << 3;
    prodA |= (sums[s30004]&1) << 4;
    prodA |= (sums[s30005]&1) << 5;
    prodA |= (sums[s40006]&1) << 6;
    prodA |= (sums[s50007]&1) << 7;
    prodA |= (sums[s40008]&1) << 8;
    prodA |= (sums[s50009]&1) << 9;
    prodA |= (sums[s60010]&1) << 10;
    prodA |= (sums[s50011]&1) << 11;
    prodA |= (sums[s50012]&1) << 12;
    prodA |= (sums[s60013]&1) << 13;
    prodA |= (sums[s70014]&1) << 14;
    prodA |= (sums[s60015]&1) << 15;
    prodA |= (sums[s70016]&1) << 16;
    prodA |= (sums[s80017]&1) << 17;
    prodA |= (sums[s70018]&1) << 18;
    prodA |= (sums[s80019]&1) << 19;
    prodA |= (sums[s80020]&1) << 20;
    prodA |= (sums[s80021]&1) << 21;
    prodA |= (sums[s70022]&1) << 22;
    prodA |= (sums[s80023]&1) << 23;
    prodA |= (sums[s80024]&1) << 24;
    prodA |= (sums[s80025]&1) << 25;
    prodA |= (sums[s80026]&1) << 26;
    prodA |= (sums[s80027]&1) << 27;
    prodA |= (sums[s80028]&1) << 28;
    prodA |= (sums[s80029]&1) << 29;
    prodA |= (sums[s80030]&1) << 30; 
    prodA |= ((uint64_t)sums[s80031]&1) << 31;
    prodA |= ((uint64_t)sums[s80032]&1) << 32;
    prodA |= ((uint64_t)sums[s80033]&1) << 33;
    prodA |= ((uint64_t)sums[s80034]&1) << 34;
    prodA |= ((uint64_t)sums[s80035]&1) << 35;
    prodA |= ((uint64_t)sums[s80036]&1) << 36;
    prodA |= ((uint64_t)sums[s80037]&1) << 37;
    prodA |= ((uint64_t)sums[s80038]&1) << 38;
    prodA |= ((uint64_t)sums[s80039]&1) << 39;
    prodA |= ((uint64_t)sums[s80040]&1) << 40;
    prodA |= ((uint64_t)sums[s80041]&1) << 41;
    prodA |= ((uint64_t)sums[s80042]&1) << 42;
    prodA |= ((uint64_t)sums[s80043]&1) << 43;
    prodA |= ((uint64_t)sums[s80044]&1) << 44;
    prodA |= ((uint64_t)sums[s80045]&1) << 45;
    prodA |= ((uint64_t)sums[s80046]&1) << 46;
    prodA |= ((uint64_t)sums[s80047]&1) << 47;
    prodA |= ((uint64_t)sums[s80048]&1) << 48;
    prodA |= ((uint64_t)sums[s70049]&1) << 49;
    prodA |= ((uint64_t)sums[s80050]&1) << 50;
    prodA |= ((uint64_t)sums[s80051]&1) << 51;
    prodA |= ((uint64_t)sums[s70052]&1) << 52;
    prodA |= ((uint64_t)sums[s80053]&1) << 53;
    prodA |= ((uint64_t)sums[s80054]&1) << 54;
    prodA |= ((uint64_t)sums[s60055]&1) << 55;
    prodA |= ((uint64_t)sums[s50056]&1) << 56;
    prodA |= ((uint64_t)sums[s60057]&1) << 57;
    prodA |= ((uint64_t)sums[s70058]&1) << 58;
    prodA |= ((uint64_t)sums[s50059]&1) << 59;
    prodA |= ((uint64_t)sums[s60060]&1) << 60;
    prodA |= ((uint64_t)sums[s70061]&1) << 61;
    prodA |= ((uint64_t)sums[s80062]&1) << 62;

    prodB |= ((int)partials[1][0]) << 1;
    prodB |= (sums[s30004]&2) << 4;
    prodB |= (sums[s50007]&2) << 7;
    prodB |= (sums[s60010]&2) << 10;
    prodB |= (sums[s50011]&2) << 11;
    prodB |= (sums[s70014]&2) << 14;
    prodB |= (sums[s80017]&2) << 17;
    prodB |= (sums[s80019]&2) << 19;
    prodB |= (sums[s80020]&2) << 20;
    prodB |= (sums[s80021]&2) << 21;
    prodB |= (sums[s80023]&2) << 23;
    prodB |= (sums[s80024]&2) << 24;
    prodB |= (sums[s80025]&2) << 25;
    prodB |= (sums[s80026]&2) << 26;
    prodB |= (sums[s80027]&2) << 27;
    prodB |= (sums[s80028]&2) << 28;
    prodB |= (sums[s80029]&2) << 29;
    prodB |= ((uint64_t)sums[s80030]&2) << 30;
    prodB |= ((uint64_t)sums[s80031]&2) << 31;
    prodB |= ((uint64_t)sums[s80032]&2) << 32;
    prodB |= ((uint64_t)sums[s80033]&2) << 33;
    prodB |= ((uint64_t)sums[s80034]&2) << 34;
    prodB |= ((uint64_t)sums[s80035]&2) << 35;
    prodB |= ((uint64_t)sums[s80036]&2) << 36;
    prodB |= ((uint64_t)sums[s80037]&2) << 37;
    prodB |= ((uint64_t)sums[s80038]&2) << 38;
    prodB |= ((uint64_t)sums[s80039]&2) << 39;
    prodB |= ((uint64_t)sums[s80040]&2) << 40;
    prodB |= ((uint64_t)sums[s80041]&2) << 41;
    prodB |= ((uint64_t)sums[s80042]&2) << 42;
    prodB |= ((uint64_t)sums[s80043]&2) << 43;
    prodB |= ((uint64_t)sums[s80044]&2) << 44;
    prodB |= ((uint64_t)sums[s80045]&2) << 45;
    prodB |= ((uint64_t)sums[s80046]&2) << 46;
    prodB |= ((uint64_t)sums[s80047]&2) << 47;
    prodB |= ((uint64_t)sums[s80048]&2) << 48;
    prodB |= ((uint64_t)sums[s80050]&2) << 50;
    prodB |= ((uint64_t)sums[s80051]&2) << 51;
    prodB |= ((uint64_t)sums[s80053]&2) << 53;
    prodB |= ((uint64_t)sums[s80054]&2) << 54;
    prodB |= ((uint64_t)sums[s60055]&2) << 55;
    prodB |= ((uint64_t)sums[s70058]&2) << 58;
    prodB |= ((uint64_t)sums[s80062]&2) << 62;

    free(partials);                                                 // free allocated memory
    free(sums);
    return prodA + prodB;                                           // return final addition, this is the result of the approximate mutliplication
}