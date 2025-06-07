#include "Transaction.h"

// Конструктор транзакции : сохраняет дату, тип, товар и количество
Transaction::Transaction(const Date& date, TransactionType type, Stationery* item, int quantity)
	: date(date), type(type), item(item), quantity(quantity) {
}

// Геттеры для доступа к данным транзакции:
Date Transaction::getDate() const { return date; }
TransactionType Transaction::getType() const { return type; }
Stationery* Transaction::getItem() const { return item; }
int Transaction::getQuantity() const { return quantity; }