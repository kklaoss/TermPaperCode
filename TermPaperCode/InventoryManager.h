#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include <memory>
#include "Transaction.h"
#include "Stationery.h"

// Класс для управления складом и транзакциями
class InventoryManager
{
private:
	std::vector<std::shared_ptr<Stationery>> items; // Список товаров (владение через умные указатели)
	std::vector<Transaction> transactions; // История транзакций

public:
	void addItem(const std::shared_ptr<Stationery>& item); // Добавление нового товара
	void restockItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date); // Пополнение запаса (увеличивает количество, создает транзакцию)
	void sellItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date); // Продажа товара (уменьшает количество, создает транзакцию)

	std::shared_ptr<Stationery> findItemByName(const std::string& name); // Поиск товара по имени

	const std::vector<std::shared_ptr<Stationery>>& getAllItems() const; // Получение списка всех товаров

	// Генерация отчетов:
	void generateSalesReport(const Date& start, const Date& end, const std::string& filename); // Отчет по продажам (сумма по категориям)
	void generateProfitReport(const Date& start, const Date& end, const std::string& filename); // Отчет по прибыли (разница между продажей и закупкой)
};

#endif