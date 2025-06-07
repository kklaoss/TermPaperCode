#include "Stationery.h"

// Конструктор базового класса: инициализация общих полей
Stationery::Stationery(const std::string& name, double purchasePrice, double salePrice, int quantity)
	: name(name), purchasePrice(purchasePrice), salePrice(salePrice), quantity(quantity) {
}

// Геттеры и сеттер:
std::string Stationery::getName() const { return name; }
double Stationery::getPurchasePrice() const { return purchasePrice; }
double Stationery::getSalePrice() const { return salePrice; }
int Stationery::getQuantity() const { return quantity; }
void Stationery::setQuantity(int newQuantity) { quantity = newQuantity; }

// Реализации для производных классов:
// Категория "Письменные принадлежности"
WritingSupplies::WritingSupplies(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string WritingSupplies::getCategory() const { return "Письменные принадлежности"; }

// Категория "Бумажная продукция"
PaperProducts::PaperProducts(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string PaperProducts::getCategory() const { return "Бумажная продукция"; }

// Категория "Офисная техника"
OfficeEquipment::OfficeEquipment(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string OfficeEquipment::getCategory() const { return "Офисная техника"; }