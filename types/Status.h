#ifndef STATUS_H
#define STATUS_H
#include <string>

using namespace std;

/**
 * @brief Структура, описывающая статус сим-карты / сделки
 */
struct Status {
  /**
   * @brief Паспорт клиента
   */
  string passport;
  /**
   * @brief Номер сим-карты
   */
  string number;
  /**
   * @brief Дата выдачи
   */
  string dateStart;
  /**
   * @brief Дата окончания выдачи
   */
  string dateEnd;
};

#endif //STATUS_H
