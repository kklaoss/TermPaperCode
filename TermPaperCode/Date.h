#ifndef DATE_H
#define DATE_H

#include <string>

// Класс для работы с датами
class Date
{
private:
	int day, month, year; // День, месяц, год

public:
	Date(int d, int m, int y); // Конструктор
	bool isValid() const; // Проверка валидности даты
	std::string toString() const; // Преобразование даты в строку формата "дд.мм.гггг"

	// Операторы сравнения для работы с датами:
	bool operator==(const Date& other) const;		// Проверка на равенство
	bool operator<(const Date& other) const;		// Сравнение "меньше" (сначала год, потом месяц, потом день)
	bool operator>=(const Date& other) const;		// "Больше или равно" (обратное <)
	bool operator<=(const Date& other) const;		// "Меньше или равно" (объединение < и ==)
};

#endif