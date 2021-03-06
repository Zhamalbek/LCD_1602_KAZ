#include "LCD_1602_KAZ.h"

wchar_t char_utf8[] = L" ";

//user_custom_symbols - количество символов, доступное пользователю для использования в своих целях (не более 8)
//Всего переопределяемых символов в LCD - 8.
//Символы с индексом от 0 до (7 - user_custom_symbols) используются библиотекой
//Символы с индексом от (8 - user_custom_symbols) до 7 - можно переопределять пользователю
//По умолчанию количество переопределяемых символов равно 0
LCD_1602_KAZ :: LCD_1602_KAZ(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t user_custom_symbols) : LiquidCrystal_I2C (lcd_Addr, lcd_cols, lcd_rows)
{
  max_symbol_count = 8 - user_custom_symbols;
  symbol_index = 0;
  cursor_col = 0;
  cursor_row = 0;
  ResetAllIndex();//Сброс значений индексов (неинициализированы = 255)
}
void LCD_1602_KAZ::clear()
{
  LiquidCrystal_I2C::clear();
  ResetAllIndex();
}
void LCD_1602_KAZ::setCursor(uint8_t col, uint8_t row)
{
  cursor_col = col;
  cursor_row = row;
  LiquidCrystal_I2C::setCursor(cursor_col, cursor_row);
}
uint8_t LCD_1602_KAZ::getCursorCol()
{
  return cursor_col;
}
uint8_t LCD_1602_KAZ::getCursorRow()
{
  return cursor_row;
}

uint8_t LCD_1602_KAZ::mbtowc(wchar_t *_chr, char *_str, uint8_t mb_num) {
  if (mb_num != 2) return 0;
  if ((_str[0] & 0xC0) == 0xC0 && (_str[1] & 0x80) == 0x80) {
    *_chr = ((_str[0] & 0x1F) << 6) + (_str[1] & 0x3F);
    return 2;
  }
  else {
    *_chr = _str[0];
    return 1;
  }
}

void LCD_1602_KAZ::print(const char *c_str) {
  wchar_t _str;
  int current_char = 0;
  int size = strlen(c_str);

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char *)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}
void LCD_1602_KAZ::print(int val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(unsigned int val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(long val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(unsigned long val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(char val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(unsigned char val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}
void LCD_1602_KAZ::print(const String &str) {
  wchar_t _str;
  const char *c_str = str.c_str();
  int current_char = 0;
  int size = str.length();

  while (current_char < size)
  {
    current_char += mbtowc(&_str, (char*)c_str + current_char, 2);
    printwc(_str);
    cursor_col++;
  }
}

void LCD_1602_KAZ::print(double val, int base) {
  cursor_col += LiquidCrystal_I2C::print(val, base);
}

void LCD_1602_KAZ::print(const wchar_t *_str) {
  int current_char  = 0;
  int size = 0;

  //Определяем длину строки (количество символов)
  while (_str[size] != 0)
  {
    size++;
  }

  while (current_char < size)
  {
    printwc(_str[current_char]);
    current_char++;
    cursor_col++;
  }

}
void LCD_1602_KAZ::CharSetToLCD(uint8_t *array, uint8_t *index)
{
  uint8_t x, y;

  if (*index == 255) // Если символ еще не создан, то создаем
  {
    x = getCursorCol();
    y = getCursorRow();
    createChar(symbol_index, (uint8_t *)array);// Создаем символ на текущем (по очереди) месте в знакогенераторе (от 0 до MAX_SYMBOL_COUNT)
    setCursor(x, y);
    write(symbol_index);// Выводим символ на экран
    //Запомианем, что букве соответствует определенный индекс
    *index = symbol_index;
    symbol_index++;
    if (symbol_index >= max_symbol_count)
    {
      symbol_index = 0;
      ResetAllIndex();
    }
  }
  else   //Иначе печатаем уже существующий
    write(*index);
}
void LCD_1602_KAZ::ResetAllIndex()
{
  symbol_index = 0;
  index_rus_B = 255;
  index_rus_G = 255;
  index_rus_D = 255;
  index_rus_ZH = 255;
  index_rus_Z = 255;
  index_rus_I = 255;
  index_rus_II = 255;
  index_rus_L = 255;
  index_rus_P = 255;
  index_rus_U = 255;
  index_rus_F = 255;
  index_rus_TS = 255;
  index_rus_CH = 255;
  index_rus_SH = 255;
  index_rus_SCH = 255;
  index_rus_tverd = 255;
  index_rus_Y = 255;
  index_rus_myagk = 255;
  index_rus_EE = 255;
  index_rus_YU = 255;
  index_rus_YA = 255;
  index_rus_b = 255;
  index_rus_v = 255;
  index_rus_g = 255;
  index_rus_d = 255;
  index_rus_yo = 255;
  index_rus_zh = 255;
  index_rus_z = 255;
  index_rus_i = 255;
  index_rus_ii = 255;
  index_rus_k = 255;
  index_rus_l = 255;
  index_rus_m = 255;
  index_rus_n = 255;
  index_rus_p = 255;
  index_rus_t = 255;
  index_rus_u = 255;
  index_rus_f = 255;
  index_rus_ts = 255;
  index_rus_ch = 255;
  index_rus_sh = 255;
  index_rus_sch = 255;
  index_rus_tverd_mal = 255;
  index_rus_y = 255;
  index_rus_myagk_mal = 255;
  index_rus_ee = 255;
  index_rus_yu = 255;
  index_rus_ya = 255;
//----------------

index_kaz_a = 255;
index_kaz_A = 255;

index_kaz_G = 255;
index_kaz_g = 255;
index_kaz_k = 255;
index_kaz_K = 255;
index_kaz_n = 255;
index_kaz_N = 255;
index_kaz_u = 255;
index_kaz_U = 255;
index_kaz_y = 255;
index_kaz_Y = 255;
index_kaz_h = 255;
index_kaz_H = 255;
index_kaz_o = 255;
index_kaz_O = 255;

}

void LCD_1602_KAZ::printwc(const wchar_t _chr) {
  uint8_t rus_[8];
  //Serial.println(_chr);

  switch (_chr)
  {
    //Русский алфавит, требующий новых символов
    //Единовременно может быть заменено только 8 символов
    case 1041: //Б
      memcpy_PF(rus_, (_uint_farptr_t)rus_B, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_B);
      break;
    case 1043: //Г
      memcpy_PF(rus_, (_uint_farptr_t)rus_G, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_G);
      break;
    case 1044: //Д
      memcpy_PF(rus_, (_uint_farptr_t)rus_D, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_D);
      break;
    case 1046: //Ж
      memcpy_PF(rus_, (_uint_farptr_t)rus_ZH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ZH);
      break;
    case 1047: //З
      memcpy_PF(rus_, (_uint_farptr_t)rus_Z, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_Z);
      break;
    case 1048: //И
      memcpy_PF(rus_, (_uint_farptr_t)rus_I, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_I);
      break;
    case 1049: //Й
      memcpy_PF(rus_, (_uint_farptr_t)rus_II, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_II);
      break;
    case 1051: //Л
      memcpy_PF(rus_, (_uint_farptr_t)rus_L, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_L);
      break;
    case 1055: //П
      memcpy_PF(rus_, (_uint_farptr_t)rus_P, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_P);
      break;
    case 1059: //У
      memcpy_PF(rus_, (_uint_farptr_t)rus_U, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_U);
      break;
    case 1060: //Ф
      memcpy_PF(rus_, (_uint_farptr_t)rus_F, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_F);
      break;
    case 1062: //Ц
      memcpy_PF(rus_, (_uint_farptr_t)rus_TS, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_TS);
      break;
    case 1063: //Ч
      memcpy_PF(rus_, (_uint_farptr_t)rus_CH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_CH);
      break;
    case 1064: //Ш
      memcpy_PF(rus_, (_uint_farptr_t)rus_SH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_SH);
      break;
    case 1065: //Щ
      memcpy_PF(rus_, (_uint_farptr_t)rus_SCH, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_SCH);
      break;
    case 1066: //Ъ
      memcpy_PF(rus_, (_uint_farptr_t)rus_tverd, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_tverd);
      break;
    case 1067: //Ы
      memcpy_PF(rus_, (_uint_farptr_t)rus_Y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_Y);
      break;
    case 1068: //Ь
      memcpy_PF(rus_, (_uint_farptr_t)rus_myagk, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_myagk);
      break;
    case 1069: //Э
      memcpy_PF(rus_, (_uint_farptr_t)rus_EE, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_EE);
      break;
    case 1070: //Ю
      memcpy_PF(rus_, (_uint_farptr_t)rus_YU, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_YU);
      break;
    case 1071: //Я
      memcpy_PF(rus_, (_uint_farptr_t)rus_YA, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_YA);
      break;
    case 1073: //б
      memcpy_PF(rus_, (_uint_farptr_t)rus_b, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_b);
      break;
    case 1074: //в
      memcpy_PF(rus_, (_uint_farptr_t)rus_v, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_v);
      break;
    case 1075: //г
      memcpy_PF(rus_, (_uint_farptr_t)rus_g, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_g);
      break;
    case 1076: //д
      memcpy_PF(rus_, (_uint_farptr_t)rus_d, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_d);
      break;
    case 1105: //ё
      memcpy_PF(rus_, (_uint_farptr_t)rus_yo, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_yo);
      break;
    case 1078: //ж
      memcpy_PF(rus_, (_uint_farptr_t)rus_zh, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_zh);
      break;
    case 1079: //з
      memcpy_PF(rus_, (_uint_farptr_t)rus_z, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_z);
      break;
    case 1080: //и
      memcpy_PF(rus_, (_uint_farptr_t)rus_i, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_i);
      break;
    case 1081: //й
      memcpy_PF(rus_, (_uint_farptr_t)rus_ii, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ii);
      break;
    case 1082: //к
      memcpy_PF(rus_, (_uint_farptr_t)rus_k, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_k);
      break;
    case 1083: //л
      memcpy_PF(rus_, (_uint_farptr_t)rus_l, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_l);
      break;
    case 1084: //м
      memcpy_PF(rus_, (_uint_farptr_t)rus_m, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_m);
      break;
    case 1085: //н
      memcpy_PF(rus_, (_uint_farptr_t)rus_n, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_n);
      break;
    case 1087: //п
      memcpy_PF(rus_, (_uint_farptr_t)rus_p, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_p);
      break;
    case 1090: //т
      memcpy_PF(rus_, (_uint_farptr_t)rus_t, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_t);
      break;
    case 1092: //ф
      memcpy_PF(rus_, (_uint_farptr_t)rus_f, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_f);
      break;
    case 1094: //ц
      memcpy_PF(rus_, (_uint_farptr_t)rus_ts, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ts);
      break;
    case 1095: //ч
      memcpy_PF(rus_, (_uint_farptr_t)rus_ch, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ch);
      break;
    case 1096: //ш
      memcpy_PF(rus_, (_uint_farptr_t)rus_sh, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_sh);
      break;
    case 1097: //щ
      memcpy_PF(rus_, (_uint_farptr_t)rus_sch, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_sch);
      break;
    case 1098: //ъ
      memcpy_PF(rus_, (_uint_farptr_t)rus_tverd_mal, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_tverd_mal);
      break;
    case 1099: //ы
      memcpy_PF(rus_, (_uint_farptr_t)rus_y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_y);
      break;
    case 1100: //ь
      memcpy_PF(rus_, (_uint_farptr_t)rus_myagk_mal, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_myagk_mal);
      break;
    case 1101: //э
      memcpy_PF(rus_, (_uint_farptr_t)rus_ee, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ee);
      break;
    case 1102: //ю
      memcpy_PF(rus_, (_uint_farptr_t)rus_yu, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_yu);
      break;
    case 1103: //я
      memcpy_PF(rus_, (_uint_farptr_t)rus_ya, 8);
      CharSetToLCD((uint8_t *)rus_, &index_rus_ya);
      break;
	  //-----------------

    case 1240: //Ә
      memcpy_PF(rus_, (_uint_farptr_t)kaz_A, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_A);
      break;
    case 1241: //ә
      memcpy_PF(rus_, (_uint_farptr_t)kaz_a, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_a);
      break;
    case 1186: //Ң
      memcpy_PF(rus_, (_uint_farptr_t)kaz_N, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_N);
      break;
    case 1187: //ң
      memcpy_PF(rus_, (_uint_farptr_t)kaz_n, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_n);
      break;
    case 1170: //Ғ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_G, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_G);
      break;
    case 1171: //ғ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_g, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_g);
      break;
    case 1198: //Ү
      memcpy_PF(rus_, (_uint_farptr_t)kaz_Y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_Y);
      break;
    case 1199: //ү
      memcpy_PF(rus_, (_uint_farptr_t)kaz_y, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_y);
      break;
    case 1200: //Ұ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_U, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_U);
      break;
    case 1201: //ұ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_u, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_u);
      break;
    case 1178: //Қ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_K, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_K);
      break;
    case 1179: //қ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_k, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_k);
      break;
    case 1256: //Ө
      memcpy_PF(rus_, (_uint_farptr_t)kaz_O, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_O);
      break;
    case 1257: //ө
      memcpy_PF(rus_, (_uint_farptr_t)kaz_o, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_o);
      break;
    case 1210: //Һ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_H, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_H);
      break;
    case 1211: //һ
      memcpy_PF(rus_, (_uint_farptr_t)kaz_h, 8);
      CharSetToLCD((uint8_t *)rus_, &index_kaz_h);
      break;

	  
	  
	  
	  
    //Русский алфавит, использующий одинаковые с английским алфавитом символы
    case 1030: //I
      LiquidCrystal_I2C::print("I");
      break;
    case 1110: //i
      LiquidCrystal_I2C::print("i");
      break;
    case 1040: //А
      LiquidCrystal_I2C::print("A");
      break;
    case 1042: //В
      LiquidCrystal_I2C::print("B");
      break;
    case 1045: //Е
      LiquidCrystal_I2C::print("E");
      break;
    case 1025: //Ё
      LiquidCrystal_I2C::print("E");
      break;
    case 1050: //К
      LiquidCrystal_I2C::print("K");
      break;
    case 1052: //M
      LiquidCrystal_I2C::print("M");
      break;
    case 1053: //H
      LiquidCrystal_I2C::print("H");
      break;
    case 1054: //O
      LiquidCrystal_I2C::print("O");
      break;
    case 1056: //P
      LiquidCrystal_I2C::print("P");
      break;
    case 1057: //C
      LiquidCrystal_I2C::print("C");
      break;
    case 1058: //T
      LiquidCrystal_I2C::print("T");
      break;
    case 1061: //X
      LiquidCrystal_I2C::print("X");
      break;
    case 1072: //а
      LiquidCrystal_I2C::print("a");
      break;
    case 1077: //е
      LiquidCrystal_I2C::print("e");
      break;
    case 1086: //o
      LiquidCrystal_I2C::print("o");
      break;
    case 1088: //p
      LiquidCrystal_I2C::print("p");
      break;
    case 1089: //c
      LiquidCrystal_I2C::print("c");
      break;
    case 1091: //y
      LiquidCrystal_I2C::print("y");
      break;
    case 1093: //x
      LiquidCrystal_I2C::print("x");
      break;
    case 0x00B0: //Знак градуса
      LiquidCrystal_I2C::write(223);
      break;
    //Английский алфавит без изменения
    default:
      LiquidCrystal_I2C::print((char)_chr);
      break;
  }
}

//Перевод символа из кодировки ASCII в UTF-8 (для печати расширенных русских символов на LCD)
wchar_t *LCD_1602_KAZ::asciiutf8(unsigned char ascii)
{
  if (ascii == 168) *char_utf8 = 0x401; //код ASCII буквы Ё
  else if (ascii == 184) *char_utf8 = 0x451; //код ASCII буквы ё
  else if (ascii >= 192) //остальные буквы русского алфавита
  {
    *char_utf8 = ascii + 848;
  }
  else *char_utf8 = ascii;

  return char_utf8;
}

//Б
const byte rus_B[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Г
const byte rus_G[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};
//Д
const byte rus_D[8] PROGMEM = {
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};
//Ж
const byte rus_ZH[8] PROGMEM = {
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b00000
};
//З
const byte rus_Z[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00110,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//И
const byte rus_I[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};
//Й
const byte rus_II[8] PROGMEM = {
  0b10101,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};
//Л
const byte rus_L[8] PROGMEM = {
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};
//П
const byte rus_P[8] PROGMEM = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};
//У
const byte rus_U[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ф
const byte rus_F[8] PROGMEM = {
  0b00100,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};
//Ц
const byte rus_TS[8] PROGMEM = {
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};
//Ч
const byte rus_CH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00001,
  0b00000
};
//Ш
const byte rus_SH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};
//Щ
const byte rus_SCH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};
//Ъ
const byte rus_tverd[8] PROGMEM = {
  0b11000,
  0b01000,
  0b01000,
  0b01110,
  0b01001,
  0b01001,
  0b01110,
  0b00000
};
//Ы
const byte rus_Y[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b10011,
  0b11101,
  0b00000
};
//Ь
const byte rus_myagk[8] PROGMEM = {
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Э
const byte rus_EE[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ю
const byte rus_YU[8] PROGMEM = {
  0b10010,
  0b10101,
  0b10101,
  0b11101,
  0b10101,
  0b10101,
  0b10010,
  0b00000
};
//Я
const byte rus_YA[8] PROGMEM = {
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b10001,
  0b00000
};
const byte rus_b[8] PROGMEM = {
  0b00011,
  0b01100,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};//б
const byte rus_v[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10001,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//в
const byte rus_g[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};//г
const byte rus_d[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};//д
const byte rus_yo[8] PROGMEM = {
  0b01010,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10000,
  0b01111,
  0b00000
};//ё
const byte rus_zh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b00000
};//ж
const byte rus_z[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00110,
  0b10001,
  0b01110,
  0b00000
};//з
const byte rus_i[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//и
const byte rus_ii[8] PROGMEM = {
  0b01010,
  0b00100,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//й
const byte rus_k[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10100,
  0b11000,
  0b10100,
  0b10010,
  0b00000
};//к
const byte rus_l[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};//л
const byte rus_m[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b11011,
  0b10101,
  0b10001,
  0b10001,
  0b00000
};//м
const byte rus_n[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b00000
};//н
const byte rus_p[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};//п
const byte rus_t[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};//т
const byte rus_f[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};//ф
const byte rus_ts[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};//ц
const byte rus_ch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00000
};//ч
const byte rus_sh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};//ш
const byte rus_sch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};//щ
const byte rus_tverd_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11000,
  0b01000,
  0b01110,
  0b01001,
  0b01110,
  0b00000
};//ъ
const byte rus_y[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b11101,
  0b00000
};//ы
const byte rus_myagk_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//ь
const byte rus_ee[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00111,
  0b10001,
  0b01110,
  0b00000
};//э
const byte rus_yu[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10101,
  0b11101,
  0b10101,
  0b10010,
  0b00000
};//ю
const byte rus_ya[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01111,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b00000
};//я
const byte kaz_A[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b01111,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};//ә
const byte kaz_a[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b00001,
  0b01111,
  0b10001,
  0b01110,
  0b00000
};//Ә
const byte kaz_G[8] PROGMEM = {
  0b01111,
  0b01000,
  0b01000,
  0b11100,
  0b01000,
  0b01000,
  0b01000,
  0b00000
};//Ғ
const byte kaz_g[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01111,
  0b01000,
  0b11100,
  0b01000,
  0b01000,
  0b00000
};//ғ
const byte kaz_k[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10100,
  0b11000,
  0b10100,
  0b10010,
  0b00010
};//қ
const byte kaz_K[8] PROGMEM = {
  0b10001,
  0b10010,
  0b10100,
  0b11000,
  0b10100,
  0b10010,
  0b10001,
  0b00001
};//қ
const byte kaz_n[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10010,
  0b11110,
  0b10010,
  0b10011,
  0b00001
};//ң
const byte kaz_N[8] PROGMEM = {
  0b10010,
  0b10010,
  0b10010,
  0b11110,
  0b10010,
  0b10010,
  0b10011,
  0b00001
};//Ң
const byte kaz_u[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01110,
  0b00100,
  0b00000
};//Ұ
const byte kaz_U[8] PROGMEM = {
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b00000
};//Ұ
const byte kaz_y[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};//ү
const byte kaz_Y[8] PROGMEM = {
  0b10001,
  0b10001,
  0b01010,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};//Ү
const byte kaz_o[8] PROGMEM = {
  0b01110,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};//o
const byte kaz_O[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10001,
  0b01110,
  0b00000
};//O
const byte kaz_H[8] PROGMEM = {
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};//o
const byte kaz_h[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b00000
};//O