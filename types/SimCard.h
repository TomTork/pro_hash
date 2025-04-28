#ifndef SIMCARD_H
#define SIMCARD_H
#include <string>

using namespace std;

/**
 * @brief Структура, описывающая сим-карту
 */
struct SimCard {
    /**
     * @brief Номер сим-карты, формат строки — NNN-NNNNNNN
     */
    string number;
    /**
     * @brief Тариф
     */
    string tariff;
    /**
     * @brief Год выпуска
     */
    int year = 0;
    /**
     * @brief Признак наличия
     */
    bool exists = true;

    // SimCard() {
    //     if (number.length() != 11) throw invalid_argument("SimCard number must be 11 characters");
    //     if (number[3] != '-') throw invalid_argument("Third character must be '-'");
    //     const string valid = "1234567890-";
    //     for (int i = 0; i < 11; i++) {
    //         if (!valid.contains(number[i])) throw invalid_argument("Number invalid: " + number);
    //     }
    // }
};

#endif //SIMCARD_H
