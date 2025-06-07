#include "Stationery.h"

// ����������� �������� ������: ������������� ����� �����
Stationery::Stationery(const std::string& name, double purchasePrice, double salePrice, int quantity)
	: name(name), purchasePrice(purchasePrice), salePrice(salePrice), quantity(quantity) {
}

// ������� � ������:
std::string Stationery::getName() const { return name; }
double Stationery::getPurchasePrice() const { return purchasePrice; }
double Stationery::getSalePrice() const { return salePrice; }
int Stationery::getQuantity() const { return quantity; }
void Stationery::setQuantity(int newQuantity) { quantity = newQuantity; }

// ���������� ��� ����������� �������:
// ��������� "���������� ��������������"
WritingSupplies::WritingSupplies(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string WritingSupplies::getCategory() const { return "���������� ��������������"; }

// ��������� "�������� ���������"
PaperProducts::PaperProducts(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string PaperProducts::getCategory() const { return "�������� ���������"; }

// ��������� "������� �������"
OfficeEquipment::OfficeEquipment(const std::string& name, double pPrice, double sPrice, int qty)
	: Stationery(name, pPrice, sPrice, qty) {
}
std::string OfficeEquipment::getCategory() const { return "������� �������"; }