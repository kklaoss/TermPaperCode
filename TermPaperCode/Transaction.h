#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Stationery.h"
#include "Date.h"

// Тип транзакции: продажа или пополнение
enum class TransactionType { SALE, RESTOCK };

// Класс для хранения информации о транзакции
class Transaction
{
private:
	Date date;				// Дата транзакции
	TransactionType type;	// Тип (продажа/пополнение)
	Stationery* item;		// Указатель на товар
	int quantity;			// Количество товара

public:
	Transaction(const Date& date, TransactionType type, Stationery* item, int quantity); // Конструктор

	// Геттеры для доступа к полям:
	Date getDate() const;
	TransactionType getType() const;
	Stationery* getItem() const;
	int getQuantity() const;
};

#endif