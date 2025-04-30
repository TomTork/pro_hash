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
     * @brief Признак наличия или признак продажи
     */
    bool exists = true;
};

#endif //SIMCARD_H
