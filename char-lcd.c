////////////////////////////

#define PROGMEM

const unsigned char PROGMEM fontLCD_jp[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,   0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,   0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,   0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,   0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,   0, 0, 0, 0, 0,			// space
    4, 4, 4, 4, 0,   0, 4, 0, 0, 0, // !
    10, 10, 10, 0, 0, 0, 0, 0, 0, 0, // "
    10, 10, 31, 10, 31, 10, 10, 0, 0, 0, // #
    4, 15, 20, 14, 5, 30, 4, 0, 0, 0, // $
    24, 25, 2, 4, 8,  19, 3, 0, 0, 0, // %
    12, 18, 20, 8, 21, 18, 13, 0, 0, 0, // &
    12, 4, 8, 0, 0, 0, 0, 0, 0, 0, // '
    2, 4, 8, 8, 8,  4, 2, 0, 0, 0, // (
    8, 4, 2, 2, 2,  4, 8, 0, 0, 0, // )
    0, 4, 21, 14, 0, 21, 4, 0, 0, 0, // *
    0, 4, 4, 31, 0, 4, 4, 0, 0, 0, // +
    0, 0, 0, 0, 12, 4, 8, 0, 0, 0, // ,
    0, 0, 0, 31, 0, 0, 0, 0, 0, 0, // -
    0, 0, 0, 0, 0, 12, 12, 0, 0, 0,  // .
    0, 1, 2, 4, 8, 16, 0, 0, 0, 0,  // /
    14, 17, 19, 21, 25, 17, 14, 0, 0, 0,  // 0
    4, 12, 4, 4, 4, 4, 14, 0, 0, 0,  // 1
    14, 17, 1, 2, 4, 8, 31, 0, 0, 0,  // 2
    31, 2, 4, 2, 1, 17, 14, 0, 0, 0,  // 3
    2, 6, 10, 18, 31, 2, 2, 0, 0, 0,  // 4
    31, 16, 30, 1, 1, 17, 14, 0, 0, 0,  // 5
    6, 8, 16, 30, 17, 17, 14, 0, 0, 0,  // 6
    31, 1, 2, 4, 8, 8, 8, 0, 0, 0,  // 7
    14, 17, 17, 14, 17, 17, 14, 0, 0, 0,  // 8
    14, 17, 17, 15, 1, 2, 12, 0, 0, 0,  // 9
    0, 12, 12, 0, 12, 12, 0, 0, 0, 0,  // :
    0, 12, 12, 0, 12, 4, 8, 0, 0, 0,  // ;
    2, 4, 8, 16, 8, 4, 2, 0, 0, 0,  // <
    0, 0, 31, 0, 31, 0, 0, 0, 0, 0,  // =
    8, 4, 2, 1, 2, 4, 8, 0, 0, 0,  // >
    14, 17, 1, 2, 4, 0, 4, 0, 0, 0,  // ?
    14, 17, 1, 13, 21, 21, 14, 0, 0, 0,  // @
    14, 17, 17, 31, 17, 17, 17, 0, 0, 0,  // A
    30, 17, 17, 30, 17, 17, 30, 0, 0, 0,  // B
    14, 17, 16, 16, 16, 17, 14, 0, 0, 0,  // C
    28, 18, 17, 17, 17, 18, 28, 0, 0, 0,  // D
    31, 16, 16, 30, 16, 16, 31, 0, 0, 0,  // E
    31, 16, 16, 30, 16, 16, 16, 0, 0, 0,  // F
    14, 17, 16, 23, 17, 17, 15, 0, 0, 0,  // G
    17, 17, 17, 31, 17, 17, 17, 0, 0, 0,  // H
    14, 4, 4, 4, 4, 4, 14, 0, 0, 0,  // I
    14, 2, 2, 2, 2, 18, 12, 0, 0, 0,  // J
    17, 18, 20, 24, 20, 18, 17, 0, 0, 0,  // K
    16, 16, 16, 16, 16, 16, 31, 0, 0, 0,  // L
    17, 27, 21, 21, 17, 17, 17, 0, 0, 0,  // M
    17, 17, 25, 21, 19, 17, 17, 0, 0, 0,  // N
    14, 17, 17, 17, 17, 17, 14, 0, 0, 0,  // O
    30, 17, 17, 30, 16, 16, 16, 0, 0, 0,  // P
    14, 17, 17, 17, 21, 18, 13, 0, 0, 0,  // Q
    30, 17, 17, 30, 20, 18, 17, 0, 0, 0,  // R
    15, 16, 16, 14, 1, 1, 30, 0, 0, 0,  // S
    31, 4, 4, 4, 4, 4, 4, 0, 0, 0,  // T
    17, 17, 17, 17, 17, 17, 14, 0, 0, 0,  // U
    17, 17, 17, 17, 17, 10, 4, 0, 0, 0,  // V
    17, 17, 17, 21, 21, 21, 10, 0, 0, 0,  // W
    17, 17, 10, 4, 10, 17, 17, 0, 0, 0,  // X
    17, 17, 17, 10, 4, 4, 4, 0, 0, 0,  // Y
    31, 1, 2, 4, 8, 16, 31, 0, 0, 0,  // Z
    14, 8, 8, 8, 8, 8, 14, 0, 0, 0,  // 
    17, 10, 31, 4, 31, 4, 4, 0, 0, 0,  // Yen
    14, 2, 2, 2, 2, 2, 14, 0, 0, 0,  // 
    4, 10, 17, 0, 0, 0, 0, 0, 0, 0,  // ^
    0, 0, 0, 0, 0, 0, 31, 0, 0, 0,  // _
    8, 4, 2, 0, 0, 0, 0, 0, 0, 0,  // `
    0, 0, 14, 1, 15, 17, 15, 0, 0, 0,  // a
    16, 16, 22, 25, 17, 17, 30, 0, 0, 0,  // b
    0, 0, 14, 16, 16, 17, 14, 0, 0, 0,  // c
    1, 1, 13, 19, 17, 17, 15, 0, 0, 0,  // d
    0, 0, 14, 17, 31, 16, 14, 0, 0, 0,  // e
    6, 9, 8, 28, 8, 8, 8, 0, 0, 0,  // f
    0, 15, 17, 17, 15, 1, 14, 0, 0, 0,  // g
    16, 16, 22, 25, 17, 17, 17, 0, 0, 0,  // h
    4, 0, 12, 4, 4, 4, 14, 0, 0, 0,  // i
    2, 0, 6, 2, 2, 18, 12, 0, 0, 0,  // j
    16, 16, 18, 20, 24, 20, 18, 0, 0, 0,  // k
    12, 4, 4, 4, 4, 4, 31, 0, 0, 0,  // l
    0, 0, 26, 21, 21, 17, 17, 0, 0, 0,  // m
    0, 0, 22, 25, 17, 17, 17, 0, 0, 0,  // n
    0, 0, 14, 17, 17, 17, 14, 0, 0, 0,  // o
    0, 0, 30, 17, 30, 16, 16, 0, 0, 0,  // p
    0, 0, 13, 19, 15, 1, 1, 0, 0, 0,  // q
    0, 0, 22, 25, 16, 16, 16, 0, 0, 0,  // r
    0, 0, 14, 16, 14, 1, 30, 0, 0, 0,  // s
    8, 8, 28, 8, 8, 9, 6, 0, 0, 0,  // t
    0, 0, 17, 17, 17, 19, 13, 0, 0, 0,  // u
    0, 0, 17, 17, 17, 10, 4, 0, 0, 0,  // v
    0, 0, 17, 17, 21, 21, 10, 0, 0, 0,  // w
    0, 0, 17, 10, 4, 10, 17, 0, 0, 0,  // x
    0, 0, 17, 17, 15, 1, 14, 0, 0, 0,  // y
    0, 0, 31, 2, 4, 8, 31, 0, 0, 0,  // z
    2, 4, 4, 8, 4, 4, 2, 0, 0, 0,  // {
    4, 4, 4, 4, 4, 4, 4, 0, 0, 0,  // |
    8, 4, 4, 2, 4, 4, 8, 0, 0, 0,  // }
    0, 4, 2, 31, 2, 4, 0, 0, 0,0,  // ->
    0, 4, 8, 31, 8, 4, 0, 0, 0,0,  // <-

#ifdef USE_256_CHAR_FONT
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//
    0, 0, 0, 0, 28, 20, 28, 0, 0, 0,
    7, 4, 4, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 4, 4, 4, 28, 0, 0, 0,
    0, 0, 0, 0, 16, 8, 4, 0, 0, 0,
    0, 0, 0, 12, 12, 0, 0, 0, 0, 0,
    0, 31, 1, 31, 1, 2, 4, 0, 0, 0,
    0, 0, 31, 1, 6, 4, 8, 0, 0, 0,
    0, 0, 2, 4, 12, 20, 4, 0, 0, 0,
    0, 0, 4, 31, 17, 1, 14, 0, 0, 0,
    0, 0, 0, 31, 4, 4, 31, 0, 0, 0,
    0, 0, 2, 31, 6, 10, 18, 0, 0, 0,
    0, 0, 8, 31, 9, 10, 8, 0, 0, 0,
    0, 0, 0, 14, 2, 2, 31, 0, 0, 0,
    0, 0, 30, 2, 30, 2, 30, 0, 0, 0,
    0, 0, 0, 21, 21, 1, 6, 0, 0, 0,

    0, 0, 0, 31, 0, 0, 0, 0, 0, 0,
    31, 1, 5, 6, 4, 4, 8, 0, 0, 0,
    1, 2, 4, 12, 20, 4, 4, 0, 0, 0,
    4, 31, 17, 17, 1, 2, 4, 0, 0, 0,
    0, 31, 4, 4, 4, 4, 31, 0, 0, 0,
    2, 31, 2, 6, 10, 18, 2, 0, 0, 0,
    8, 31, 9, 9, 9, 9, 18, 0, 0, 0,
    4, 31, 4, 31, 4, 4, 4, 0, 0, 0,
    0, 15, 9, 17, 1, 2, 12, 0, 0, 0,
    8, 15, 18, 2, 2, 2, 4, 0, 0, 0,
    0, 31, 1, 1, 1, 1, 31, 0, 0, 0,
    10, 31, 10, 10, 2, 4, 8, 0, 0, 0,
    0, 24, 1, 25, 1, 2, 28, 0, 0, 0,
    0, 31, 1, 2, 4, 10, 17, 0, 0, 0,
    8, 31, 9, 10, 8, 8, 7, 0, 0, 0,
    0, 17, 17, 9, 1, 2, 12, 0, 0, 0,

    0, 15, 9, 21, 3, 2, 12, 0, 0, 0,
    2, 28, 4, 31, 4, 4, 8, 0, 0, 0,
    0, 21, 21, 21, 1, 2, 4, 0, 0, 0,
    14, 0, 31, 4, 4, 4, 8, 0, 0, 0,
    8, 8, 8, 12, 10, 8, 8, 0, 0, 0,
    4, 4, 31, 4, 4, 8, 16, 0, 0, 0,
    0, 14, 0, 0, 0, 0, 31, 0, 0, 0,
    0, 31, 1, 10, 4, 10, 16, 0, 0, 0,
    4, 31, 2, 4, 14, 21, 4, 0, 0, 0,
    2, 2, 2, 2, 2, 4, 8, 0, 0, 0,
    0, 4, 2, 17, 17, 17, 17, 0, 0, 0,
    16, 16, 31, 16, 16, 16, 15, 0, 0, 0,
    0, 31, 1, 1, 1, 2, 12, 0, 0, 0,
    0, 8, 20, 2, 1, 1, 0, 0, 0, 0,
    4, 31, 4, 4, 21, 21, 4, 0, 0, 0,
    0, 31, 1, 1, 10, 4, 2, 0, 0, 0,

    0, 14, 0, 14, 0, 14, 1, 0, 0, 0,
    0, 4, 8, 16, 17, 31, 1, 0, 0, 0,
    0, 1, 1, 10, 4, 10, 16, 0, 0, 0,
    0, 31, 8, 31, 8, 8, 7, 0, 0, 0,
    8, 8, 31, 9, 10, 8, 8, 0, 0, 0,
    0, 14, 2, 2, 2, 2, 31, 0, 0, 0,
    0, 31, 1, 31, 1, 1, 31, 0, 0, 0,
    14, 0, 31, 1, 1, 2, 4, 0, 0, 0,
    18, 18, 18, 18, 2, 4, 8, 0, 0, 0,
    0, 4, 20, 20, 21, 21, 22, 0, 0, 0,
    0, 16, 16, 17, 18, 20, 24, 0, 0, 0,
    0, 31, 17, 17, 17, 17, 31, 0, 0, 0,
    0, 31, 17, 17, 1, 2, 4, 0, 0, 0,
    0, 24, 0, 1, 1, 2, 28, 0, 0, 0,
    4, 18, 8, 0, 0, 0, 0, 0, 0, 0,
    28, 20, 28, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 9, 21, 18, 18, 13, 0, 0, 0, // alpha
    10, 0, 14, 1, 15, 17, 15, 0, 0, 0,  // a:
    0, 0, 14, 17, 30, 17, 30, 16, 16, 16, // beta
    0, 0, 14, 16, 12, 17, 14, 0, 0, 0, // epsilon
    0,0, 17, 17, 17, 19, 29, 16, 16, 16, // mu
    0, 0, 15, 20, 18, 17, 14, 0, 0, 0,  // sigma
    0, 0, 6, 9, 17, 17, 30, 16, 16, 16, // ro
    0, 0, 15, 17, 17, 17, 15, 1, 1, 14, // g
    0, 0, 7, 4, 4, 20, 8, 0, 0, 0, // sq root
    0, 2, 26, 2, 0, 0, 0, 0, 0, 0, // -1
    2, 0, 6, 2, 2, 2, 2, 2, 18, 12, // j
    0, 20, 8, 20, 0, 0, 0, 0, 0, 0, // x
    0, 4, 14, 20, 21, 14, 4, 0, 0, 0, // cent
    8, 8, 28, 8, 28, 8, 15, 0, 0, 0, // pound
    14, 0, 22, 25, 17, 17, 17, 0, 0, 0, // n~
    10, 0, 14, 17, 17, 17, 14, 0, 0, 0, // o:
    0, 0, 22, 25, 17, 17, 30, 16, 16, 16, // p
    0, 0, 13, 19, 17, 17, 15, 1, 1, 1, // q
    0, 14, 17, 31, 17, 17, 14, 0, 0, 0, // theta
    0, 0, 0, 11, 21, 26, 0, 0, 0, 0 // inf
    0, 0, 14, 17, 17, 10, 27, 0, 0, 0, // Omega
    10, 0, 17, 17, 17, 19, 13, 0, 0, 0, // u:
    31, 16, 8, 4, 8, 16, 31, 0, 0, 0, // Sigma
    0, 0, 31, 10, 10, 10, 19, 0, 0, 0, // pi
    31, 0, 17, 10, 4, 10, 17, 0, 0, 0, // x-
    0, 0, 17, 17, 17, 17, 15, 1, 1, 14, // y
    0, 1, 30, 4, 31, 4, 4, 0, 0, 0, 
    0, 0, 31, 8, 15, 9, 17, 0, 0, 0, 
    0, 0, 31, 21, 31, 17, 17, 0, 0, 0, // yen
    0, 0, 4, 0, 31, 0, 4, 0, 0, 0, // :-
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    31, 31, 31, 31, 31, 31, 31, 31, 31, 31
#endif  
	};

////////////////////////////

const unsigned char PROGMEM fontLCD_eu[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 8, 12, 14, 15, 14, 12, 8, 0, 0, // |> ; 16
    0, 2, 6, 14, 30, 14, 6, 2, 0, 0, // <|
    0, 9, 18, 27, 0, 0, 0, 0, 0, 0, // ``
    0, 27, 9, 18, 0, 0, 0, 0, 0, 0, // ''
    0, 4, 14, 31, 0, 4, 14, 31, 0, 0,
    0, 31, 14, 4, 0, 31, 14, 4, 0, 0,
    0, 0, 14, 31, 31, 31, 14, 0, 0, 0,
    0, 1, 1, 5, 9, 31, 8, 4, 0, 0, // return
    0, 4, 14, 21, 4, 4, 4, 4, 0, 0, // up
    0, 4, 4, 4, 4, 21, 14, 4, 0, 0, // down
    0, 0, 4, 2, 31, 2, 4, 0, 0, 0, // ->
    0, 0, 4, 8, 31, 8, 4, 0, 0, 0, // <-
    0, 2, 4, 8, 4, 2, 0, 31, 0, 0, // <=
    0, 8, 4, 2, 4, 8, 0, 31, 0, 0, // >=
    0, 0, 4, 4, 14, 14, 31, 0, 0, 0,
    0, 0, 31, 14, 14, 4, 4, 0, 0, 0,
    
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		// space ; 32
    0, 4, 4, 4, 4, 0, 0, 4, 0, 0, // !
    0, 10, 10, 10, 0, 0, 0, 0, 0, 0, // "
    0, 10, 10, 31, 10, 31, 10, 10, 0, 0, // #
    0, 4, 15, 20, 14, 5, 30, 4, 0, 0, // $
    0, 24, 25, 2, 4, 8, 19, 3, 0, 0, // %
    0, 12, 18, 20, 8, 21, 18, 13, 0, 0, // &
    0, 12, 4, 8, 0, 0, 0, 0, 0, 0, // '
    0, 2, 4, 8, 8, 8, 4, 2, 0, 0, // (
    0, 8, 4, 2, 2, 2, 4, 8, 0, 0, // )
    0, 0, 4, 21, 14, 21, 4, 0, 0, 0, // *
    0, 0, 4, 4, 31, 4, 4, 0, 0, 0, // +
    0, 0, 0, 0, 0, 12, 4, 8, 0, 0, // ,
    0, 0, 0, 0, 31, 0, 0, 0, 0, 0, // -
    0, 0, 0, 0, 0, 0, 12, 12, 0, 0, // .
    0, 0, 1, 2, 4, 8, 16, 0, 0, 0, // /
    0, 14, 17, 19, 21, 25, 17, 14, 0, 0, // 0 ; 48
    0, 4, 12, 4, 4, 4, 4, 14, 0, 0, // 1
    0, 14, 17, 1, 2, 4, 8, 31, 0, 0, // 2
    0, 31, 2, 4, 2, 1, 17, 14, 0, 0, // 3
    0, 2, 6, 10, 18, 31, 2, 2, 0, 0, // 4
    0, 31, 16, 30, 1, 1, 17, 14, 0, 0, // 5
    0, 6, 8, 16, 30, 17, 17, 14, 0, 0, // 6
    0, 31, 1, 2, 4, 8, 8, 8, 0, 0, // 7
    0, 14, 17, 17, 14, 17, 17, 14, 0, 0, // 8
    0, 14, 17, 17, 15, 1, 2, 12, 0, 0, // 9
    0, 0, 12, 12, 0, 12, 12, 0, 0, 0, // :
    0, 0, 12, 12, 0, 12, 4, 8, 0, 0, // ;
    0, 2, 4, 8, 16, 8, 4, 2, 0, 0, // <
    0, 0, 0, 31, 0, 31, 0, 0, 0, 0, // =
    0, 8, 4, 2, 1, 2, 4, 8, 0, 0, // >
    0, 14, 17, 1, 2, 4, 0, 4, 0, 0, // ?
    
    0, 14, 17, 1, 13, 21, 21, 14, 0, 0, // @ ; 64
    0, 4, 10, 17, 17, 31, 17, 17, 0, 0, // A
    0, 30, 17, 17, 30, 17, 17, 30, 0, 0, // B
    0, 14, 17, 16, 16, 16, 17, 14, 0, 0, // C
    0, 28, 18, 17, 17, 17, 18, 28, 0, 0, // D
    0, 31, 16, 16, 30, 16, 16, 31, 0, 0, // E
    0, 31, 16, 16, 30, 16, 16, 16, 0, 0, // F
    0, 14, 17, 16, 23, 17, 17, 15, 0, 0, // G
    0, 17, 17, 17, 31, 17, 17, 17, 0, 0, // H
    0, 14, 4, 4, 4, 4, 4, 14, 0, 0, // I
    0, 14, 2, 2, 2, 2, 18, 12, 0, 0, // J
    0, 17, 18, 20, 24, 20, 18, 17, 0, 0, // K
    0, 16, 16, 16, 16, 16, 16, 31, 0, 0, // L
    0, 17, 27, 21, 21, 17, 17, 17, 0, 0, // M
    0, 17, 17, 25, 21, 19, 17, 17, 0, 0, // N
    0, 14, 17, 17, 17, 17, 17, 14, 0, 0, // O
    0, 30, 17, 17, 30, 16, 16, 16, 0, 0, // P
    0, 14, 17, 17, 17, 21, 18, 13, 0, 0, // Q
    0, 30, 17, 17, 30, 20, 18, 17, 0, 0, // R
    0, 15, 16, 16, 14, 1, 1, 30, 0, 0, // S
    0, 31, 4, 4, 4, 4, 4, 4, 0, 0, // T
    0, 17, 17, 17, 17, 17, 17, 14, 0, 0, // U
    0, 17, 17, 17, 17, 17, 10, 4, 0, 0, // V
    0, 17, 17, 17, 21, 21, 21, 10, 0, 0, // W
    0, 17, 17, 10, 4, 10, 17, 17, 0, 0, // X
    0, 17, 17, 17, 10, 4, 4, 4, 0, 0, // Y
    0, 31, 1, 2, 4, 8, 16, 31, 0, 0, // Z
    0, 14, 8, 8, 8, 8, 8, 14, 0, 0, // 
    0, 0, 16, 8, 4, 2, 1, 0, 0, 0, // backslash
    0, 14, 2, 2, 2, 2, 2, 14, 0, 0, // 
    0, 4, 10, 17, 0, 0, 0, 0, 0, 0, // ^
    0, 0, 0, 0, 0, 0, 0, 31, 0, 0, // _
    
    0, 8, 4, 2, 0, 0, 0, 0, 0, // ` ; 96
    0, 0, 0, 14, 1, 15, 17, 15, 0, 0, // a
    0, 16, 16, 22, 25, 17, 17, 30, 0, 0, // b
    0, 0, 0, 14, 16, 16, 17, 14, 0, 0, // c
    0, 1, 1, 13, 19, 17, 17, 15, 0, 0, // d
    0, 0, 0, 14, 17, 31, 16, 14, 0, 0, // e
    0, 6, 9, 8, 28, 8, 8, 8, 0, 0, // f
    0, 0, 15, 17, 17, 15, 1, 14, 0, 0, // g
    0, 16, 16, 22, 25, 17, 17, 17, 0, 0, // h
    0, 4, 0, 4, 12, 4, 4, 14, 0, 0, // i
    0, 2, 0, 6, 2, 2, 18, 12, 0, 0, // j
    0, 16, 16, 18, 20, 24, 20, 18, 0, 0, // k
    0, 12, 4, 4, 4, 4, 4, 31, 0, 0, // l
    0, 0, 0, 26, 21, 21, 17, 17, 0, 0, // m
    0, 0, 0, 22, 25, 17, 17, 17, 0, 0, // n
    0, 0, 0, 14, 17, 17, 17, 14, 0, 0, // o
    0, 0, 0, 30, 17, 30, 16, 16, 0, 0, // p
    0, 0, 0, 13, 19, 15, 1, 1, 0, 0, // q
    0, 0, 0, 22, 25, 16, 16, 16, 0, 0, // r
    0, 0, 0, 14, 16, 14, 1, 30, 0, 0, // s
    0, 8, 8, 28, 8, 8, 9, 6, 0, 0, // t
    0, 0, 0, 17, 17, 17, 19, 13, 0, 0, // u
    0, 0, 0, 17, 17, 17, 10, 4, 0, 0, // v
    0, 0, 0, 17, 17, 21, 21, 10, 0, 0, // w
    0, 0, 0, 17, 10, 4, 10, 17, 0, 0, // x
    0, 0, 0, 17, 17, 15, 1, 14, 0, 0, // y
    0, 0, 0, 31, 2, 4, 8, 31, 0, 0, // z
    0, 2, 4, 4, 8, 4, 4, 2, 0, 0, // {
    0, 4, 4, 4, 4, 4, 4, 4, 0, 0, // |
    0, 8, 4, 4, 2, 4, 4, 8, 0, 0, // }
    0, 0, 0, 0, 13, 18, 0, 0, 0, 0, // ~
    0, 4, 10, 17, 17, 17, 31, 0, 0, 0, // del

#ifdef USE_256_CHAR_FONT
    0, 31, 17, 16, 30, 17, 17, 30, 0, 0, // .B
    15, 5, 5, 9, 17, 31, 17, 17, 0, 0, // .D
    0, 21, 21, 21, 14, 21, 21, 21, 0, 0, // .Zh
    0, 30, 1, 1, 6, 1, 1, 30, 0, 0, // .Z
    0, 17, 17, 19, 21, 25, 17, 17, 0, 0, // .I
    10, 4, 17, 19, 21, 25, 17, 17, 0, 0, // .J
    0, 15, 5, 5, 5, 5, 21, 9, 0, 0, // .L
    0, 31, 17, 17, 17, 17, 17, 17, 0, 0, // .P
    0, 17, 17, 17, 10, 4, 8, 16, 0, 0, // .U
    0, 17, 17, 17, 17, 17, 31, 1, 0, 0, // .Ts
    0, 17, 17, 17, 15, 1, 1, 1, 0, 0, // .Ch
    0, 0, 21, 21, 21, 21, 21, 31, 0, 0, // .Sh
    0, 21, 21, 21, 21, 21, 31, 1, 0, 0, // .Sch
    0, 24, 8, 8, 14, 9, 9, 14, 0, 0, // .'
    0, 17, 17, 17, 25, 21, 21, 25, 0, 0, // .Y
    0, 14, 17, 5, 11, 1, 17, 14, 0, 0, // .E
    0, 0, 0, 9, 21, 18, 18, 13, 0, 0, // alpha
    0, 4, 6, 5, 5, 4, 28, 28, 0, 0, // note
    0, 31, 17, 16, 16, 16, 16, 16, 0, 0, // .G
    0, 0, 0, 31, 10, 10, 10, 19, 0, 0, // pi
    0, 31, 16, 8, 4, 8, 16, 31, 0, 0, // Sigma
    0, 0, 0, 15, 18, 18, 18, 12, 0, 0, // sigma
    6, 5, 7, 5, 5, 29, 27, 3, 0, 0, // notes
    0, 0, 1, 14, 20, 4, 4, 2, 0, 0, // tau
    0, 4, 14, 14, 14, 31, 4, 0, 0, 0, // bell
    0, 14, 17, 17, 31, 17, 17, 14, 0, 0, // Theta
    0, 0, 14, 17, 17, 17, 10, 27, 0, 0, // Omega
    0, 6, 9, 4, 10, 17, 17, 14, 0, 0, // delta
    0, 0, 0, 11, 21, 26, 0, 0, 0, 0, // inf
    0, 0, 10, 31, 31, 31, 14, 4, 0, 0, // heart
    0, 0, 0, 14, 16, 12, 17, 14, 0, 0, // epsilon
    0, 14, 17, 17, 17, 17, 17, 17, 0, 0,
    0, 27, 27, 27, 27, 27, 27, 27, 0, 0,
    0, 4, 0, 0, 4, 4, 4, 4, 0, 0, // !!
    0, 4, 14, 20, 20, 21, 14, 4, 0, 0, // cent
    0, 6, 8, 8, 28, 8, 9, 22, 0, 0, // pound
    0, 0, 17, 14, 10, 14, 17, 0, 0, // money
    0, 17, 10, 31, 4, 31, 4, 4, 0, 0, // yen
    0, 4, 4, 4, 0, 4, 4, 4, 0, 0, // pipe
    0, 6, 9, 4, 10, 4, 18, 12, 0, 0, // paragraph
    0, 2, 5, 4, 31, 4, 20, 8, 0, 0, // f
    0, 31, 17, 21, 23, 21, 17, 31, 0, 0, // (C)
    0, 14, 1, 15, 17, 15, 0, 31, 0, 0, // a_
    0, 0, 5, 10, 20, 10, 5, 0, 0, 0,  // <<
    0, 18, 21, 21, 29, 21, 21, 18, 0, 0, // .Ju
    0, 15, 17, 17, 15, 5, 9, 17, 0, 0, // .Ja
    0, 31, 17, 21, 17, 19, 21, 31, 0, 0, // (R)
    0, 4, 8, 12, 0, 0, 0, 0, 0, 0, // `
    12, 18, 18, 18, 12, 0, 0, 0, 0, // 0
    0, 4, 4, 31, 4, 4, 0, 31, 0, 0, // +-
    12, 18, 4, 8, 30, 0, 0, 0, 0, 0, // 2
    28, 2, 12, 2, 28, 0, 0, 0, 0, 0, // 3
    28, 18, 28, 16, 18, 23, 18, 3, 0, 0, // Pt
    0, 17, 17, 17, 19, 29, 16, 16, 0, 0, // mu
    0, 15, 19, 19, 15, 3, 3, 3, 0, 0, // pilcrow
    0, 0, 0, 0, 12, 12, 0, 0, 0, // dot
    0, 0, 0, 10, 17, 21, 21, 10, 0, 0, // omega
    8, 24, 8, 8, 28, 0, 0, 0, 0, 0, // 1
    0, 14, 17, 17, 17, 14, 0, 31, 0, 0, // o_
    0, 0, 20, 10, 5, 10, 20, 0, 0, 0, // >>
    17, 18, 20, 10, 22, 10, 15, 2, 0, 0, // 1/4
    17, 18, 20, 10, 21, 1, 2, 7, 0, 0, // 1/2
    24, 8, 24, 9, 27, 5, 7, 1, 0, 0, // 3/4
    0, 4, 0, 4, 8, 16, 17, 14, 0, 0, // !?
    8, 4, 4, 10, 17, 31, 17, 17, 0, 0, // A\
    2, 4, 4, 10, 17, 31, 17, 17, 0, 0, // A/
    4, 10, 0, 14, 17, 31, 17, 17, 0, 0, // A^
    13, 18, 0, 14, 17, 31, 17, 17, 0, 0, // A~
    10, 0, 4, 10, 17, 31, 17, 17, 0, 0, // A:
    4, 10, 4, 10, 17, 31, 17, 17, 0, 0, // Ao
    0, 7, 12, 20, 23, 28, 20, 23, 0, 0, // AE
    14, 17, 16, 16, 17, 14, 2, 6, 0, 0, // C,
    8, 4, 0, 31, 16, 30, 16, 31, 0, 0, // E\
    2, 4, 0, 31, 16, 30, 16, 31, 0, 0, // E/
    4, 10, 0, 31, 16, 30, 16, 31, 0, 0, // E^
    0, 10, 0, 31, 16, 30, 16, 31, 0, 0, // E:
    8, 4, 0, 14, 4, 4, 4, 14, 0, 0, // I\
    2, 4, 0, 14, 4, 4, 4, 14, 0, 0, // I/
    4, 10, 0, 14, 4, 4, 4, 14, 0, 0, // I^
    0, 10, 0, 14, 4, 4, 4, 14, 0, 0, // I:
    0, 14, 9, 9, 29, 9, 9, 14, 0, 0, // -D
    13, 18, 0, 17, 25, 21, 19, 17, 0, 0, // N~
    8, 4, 14, 17, 17, 17, 17, 14, 0, 0, // O\
    2, 4, 14, 17, 17, 17, 17, 14, 0, 0, // O/
    4, 10, 0, 14, 17, 17, 17, 14, 0, 0, // O^
    13, 18, 0, 14, 17, 17, 17, 14, 0, 0, // O~
    10, 0, 14, 17, 17, 17, 17, 14, 0, 0, // O:
    0, 0, 17, 10, 4, 10, 17, 0, 0, 0,  // X
    0, 14, 4, 14, 21, 14, 4, 14, 0, 0, // .F
    8, 4, 17, 17, 17, 17, 17, 14, 0, 0, // U\
    2, 4, 17, 17, 17, 17, 17, 14, 0, 0, // U/
    4, 10, 0, 17, 17, 17, 17, 14, 0, 0, // U^
    10, 0, 17, 17, 17, 17, 17, 14, 0, 0, // U:
    2, 4, 17, 10, 4, 4, 4, 4, 0, 0, // Y/
    24, 8, 14, 9, 9, 14, 8, 28, 0, 0, // -P
    0, 6, 9, 9, 14, 9, 9, 22, 0, 0, // beta
    8, 4, 0, 14, 1, 15, 17, 15, 0, 0, // a\
    2, 4, 0, 14, 1, 15, 17, 15, 0, 0, // a/
    4, 10, 0, 14, 1, 15, 17, 15, 0, 0, // a^
    13, 18, 0, 14, 1, 15, 17, 15, 0, 0, // a~
    0, 10, 0, 14, 1, 15, 17, 15, 0, 0, // a:
    4, 10, 4, 14, 1, 15, 17, 15, 0, 0, // ao
    0, 0, 26, 5, 15, 20, 21, 10, 0, 0, // ae
    0, 0, 14, 16, 17, 14, 4, 12, 0, 0, // c,
    8, 4, 0, 14, 17, 31, 16, 14, 0, 0, // e\
    2, 4, 0, 14, 17, 31, 16, 14, 0, 0, // e/
    4, 10, 0, 14, 17, 31, 16, 14, 0, 0, // e^
    0, 10, 0, 14, 17, 31, 16, 14, 0, 0, // e:
    8, 4, 0, 4, 12, 4, 4, 14, 0, 0, // i\
    2, 4, 0, 4, 12, 4, 4, 14, 0, 0, // i/
    4, 10, 0, 4, 12, 4, 4, 14, 0, 0, // i^
    0, 10, 0, 4, 12, 4, 4, 14, 0, 0, // i:
    0, 20, 8, 20, 2, 15, 17, 14, 0, 0, // -d
    13, 18, 0, 22, 25, 17, 17, 17, 0, 0, // n~
    8, 4, 0, 14, 17, 17, 17, 14, 0, 0, // o\
    2, 4, 0, 14, 17, 17, 17, 14, 0, 0, // o/
    0, 4, 10, 0, 14, 17, 17, 14, 0, 0, // o^
    0, 13, 18, 0, 14, 17, 17, 14, 0, 0, // o~
    0, 10, 0, 14, 17, 17, 17, 14, 0, 0, // o:
    0, 0, 4, 0, 31, 0, 4, 0, 0, 0, // :/
    0, 2, 4, 14, 21, 14, 4, 8, 0, 0, // .f
    8, 4, 0, 17, 17, 17, 19, 13, 0, 0, // u\
    2, 4, 0, 17, 17, 17, 19, 13, 0, 0, // u/
    4, 10, 0, 17, 17, 17, 19, 13, 0, 0, // u^
    0, 10, 0, 17, 17, 17, 19, 13, 0, 0, // u:
    2, 4, 0, 17, 17, 15, 1, 14, 0, 0, // y/
    0, 12, 4, 6, 5, 6, 4, 14, 0, 0, // p-
    0, 10, 0, 17, 17, 15, 1, 14, 0, 0, // y:
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
#endif
	};


