#include "InventoryManager.h"
#include <fstream>
#include <map>
#include <algorithm>
#include <memory>

// ���������� ������ � ������ (����� shared_ptr)
void InventoryManager::addItem(const std::shared_ptr<Stationery>& item)
{
	items.push_back(item);
}

// ���������� ������ ������: ����������� ���������� � ������ ����������
void InventoryManager::restockItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date)
{
	item->setQuantity(item->getQuantity() + quantity);
	transactions.emplace_back(date, TransactionType::RESTOCK, item.get(), quantity);
}

// ������� ������: ��������� �������, ��������� ����������, ������ ����������
void InventoryManager::sellItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date)
{
	if (item->getQuantity() < quantity) throw std::runtime_error("Not enough stock");
	item->setQuantity(item->getQuantity() - quantity);
	transactions.emplace_back(date, TransactionType::SALE, item.get(), quantity);
}

// ����� ������ �� ����� (���������� nullptr, ���� �� ������)
std::shared_ptr<Stationery> InventoryManager::findItemByName(const std::string& name)
{
	auto it = std::find_if(items.begin(), items.end(),
		[&name](const std::shared_ptr<Stationery>& item) { return item->getName() == name; });
	return (it != items.end()) ? *it : nullptr;
}

// ���������� ������ ���� ������� (����������� ������)
const std::vector<std::shared_ptr<Stationery>>& InventoryManager::getAllItems() const
{
	return items;
}

// ��������� ������ �� �������� �� ������
void InventoryManager::generateSalesReport(const Date& start, const Date& end, const std::string& filename)
{
	std::ofstream file(filename);
	std::map<std::string, double> categorySales; // ����������� �� ����������

	// ���������� ����������: ������ + ��� SALE
	for (const auto& t : transactions)
	{
		if (t.getDate() >= start && t.getDate() <= end && t.getType() == TransactionType::SALE)
		{
			auto category = t.getItem()->getCategory();
			categorySales[category] += t.getItem()->getSalePrice() * t.getQuantity();
		}
	}

	// ������ � ����
	file << "����� �� �������� (" << start.toString() << " - " << end.toString() << ")\n";
	for (const auto& entry : categorySales) {
		file << "���������: " << entry.first << " - �����: " << entry.second << "\n";
	}
}

// ��������� ������ �� ������� �� ������ (���������� ��������)
void InventoryManager::generateProfitReport(const Date& start, const Date& end, const std::string& filename)
{
	std::ofstream file(filename);
	std::map<std::string, double> categoryProfit;

	for (const auto& t : transactions)
	{
		if (t.getDate() >= start && t.getDate() <= end && t.getType() == TransactionType::SALE)
		{
			auto category = t.getItem()->getCategory();
			double profit = (t.getItem()->getSalePrice() - t.getItem()->getPurchasePrice()) * t.getQuantity();
			categoryProfit[category] += profit;
		}
	}

	file << "����� �� ������� (" << start.toString() << " - " << end.toString() << ")\n";
	for (const auto& entry : categoryProfit)
	{
		file << "���������: " << entry.first << " - �������: " << entry.second << "\n";
	}
}