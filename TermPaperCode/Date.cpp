#include "Date.h"

// Конструктор: инициализация дня, месяца, года
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
}

bool Date::isValid() const // Проверка валидности даты
{
	return (day >= 1 && day <= 31) && (month >= 1 && month <= 12) && (year > 0);
}

std::string Date::toString() const // Преобразование даты в строку формата "дд.мм.гггг"
{
	return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

bool Date::operator==(const Date& other) const // Оператор сравнения "равно" (проверяет все поля)
{
	return day == other.day && month == other.month && year == other.year;
}

bool Date::operator<(const Date& other) const // Оператор "меньше" (сравнивает сначала год, затем месяц, затем день)
{
	if (year != other.year) return year < other.year;
	if (month != other.month) return month < other.month;
	return day < other.day;
}
bool Date::operator>=(const Date& other) const // Оператор "больше или равно" (инвертирует результат оператора <)
{
	return !(*this < other);
}

bool Date::operator<=(const Date& other) const // Оператор "меньше или равно" (объединяет < и ==)
{
	return (*this < other) || (*this == other);
}