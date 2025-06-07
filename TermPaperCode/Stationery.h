#ifndef STATIONERY_H
#define STATIONERY_H

#include <string>

// Базовый абстрактный класс для канцелярских товаров
class Stationery
{
protected:
	std::string name;		// Название товара
	double purchasePrice;	// Цена закупки
	double salePrice;		// Цена продажи
	int quantity;			// Количество на складе

public:
	Stationery(const std::string& name, double purchasePrice, double salePrice, int quantity); // Конструктор
	virtual ~Stationery() = default;
	virtual std::string getCategory() const = 0; // Виртуальный метод для получения категории товара

	// Геттеры и сеттер для работы с полями:
	std::string getName() const;
	double getPurchasePrice() const;
	double getSalePrice() const;
	int getQuantity() const;

	void setQuantity(int newQuantity); // Обновление количества товара
};

// Производные классы для конкретных категорий товаров:
class WritingSupplies : public Stationery // Письменные принадлежности
{
public:
	WritingSupplies(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

class PaperProducts : public Stationery // Бумажная продукция
{
public:
	PaperProducts(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

class OfficeEquipment : public Stationery // Офисная техника
{
public:
	OfficeEquipment(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

#endif