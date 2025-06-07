#include <iostream>
#include "InventoryManager.h"
#include "Date.h"
#include <memory>

// ��������� ��������������� �������:
void displayMenu();
Date inputDate();
double inputPositiveDouble(const std::string& prompt);
int inputPositiveInt(const std::string& prompt);
std::string inputNonEmptyString(const std::string& prompt);

// �������� ������ ���������:
int main()
{
	system("chcp 1251"); // ��������� ��������� ��� Windows
	setlocale(LC_ALL, "RUS"); // ��������� ���������
	InventoryManager manager; // �������� ��������� ������
	int choice = 0;

	// ���� ����:
	do
	{
		displayMenu(); // ����� ����
		std::cin >> choice;
		std::cin.ignore();
		try
		{
			// ��������� ������ ������������:
			switch (choice)
			{
			case 1: // ���������� ������ (� ������� ���������)
			{
				std::string name = inputNonEmptyString("������� �������� ������: ");
				int categoryChoice;

				double pPrice = inputPositiveDouble("���� �������: ");
				double sPrice = inputPositiveDouble("���� �������: ");
				int qty = inputPositiveInt("��������� ����������: ");

				std::cout << "�������� ���������:\n"
					<< "1. ���������� ��������������\n"
					<< "2. �������� ���������\n"
					<< "3. ������� �������\n"
					<< "��� �����: ";
				std::cin >> categoryChoice;
				std::cin.ignore();

				std::shared_ptr<Stationery> item;
				switch (categoryChoice)
				{
				case 1:
					item = std::make_shared<WritingSupplies>(name, pPrice, sPrice, qty);
					break;
				case 2:
					item = std::make_shared<PaperProducts>(name, pPrice, sPrice, qty);
					break;
				case 3:
					item = std::make_shared<OfficeEquipment>(name, pPrice, sPrice, qty);
					break;
				default:
					std::cout << "�������� �����, ����� �� ��������!\n";
					continue;
				}

				manager.addItem(item);
				std::cout << "����� ��������!\n";
				break;
			}
			case 2: // �������� ���� �������
			{
				const auto& items = manager.getAllItems();
				if (items.empty())
				{
					std::cout << "������ ������� ����.\n";
					break;
				}
				std::cout << "\n������ �������:\n";
				for (const auto& item : items)
				{
					std::cout << "��������: " << item->getName()
						<< ", ���� �������: " << item->getPurchasePrice()
						<< ", ���� �������: " << item->getSalePrice()
						<< ", ����������: " << item->getQuantity() << "\n";
				}
				break;
			}
			case 3: // ���������� ������
			{
				std::string name = inputNonEmptyString("������� �������� ������: ");

				auto item = manager.findItemByName(name);
				if (!item)
				{
					std::cout << "����� �� ������!\n";
					break;
				}

				int quantity = inputPositiveInt("������� ���������� ��� ����������: ");
				Date date = inputDate();
				manager.restockItem(item, quantity, date);
				std::cout << "����� ��������!\n";
				break;
			}
			case 4: // ������� ������ (� ��������� �������)
			{
				std::string name = inputNonEmptyString("������� �������� ������: ");

				auto item = manager.findItemByName(name);
				if (!item)
				{
					std::cout << "����� �� ������!\n";
					break;
				}

				int quantity = inputPositiveInt("������� ���������� ��� �������: ");
				Date date = inputDate();
				manager.sellItem(item, quantity, date);
				std::cout << "������� ���������!\n";
				break;
			}
			case 5: // ����� �� ��������
			case 6: // ����� �� �������
			{
				Date start = inputDate();
				Date end = inputDate();
				std::string filename = inputNonEmptyString("������� ��� ����� ��� ������: ");

				if (choice == 5)
				{
					manager.generateSalesReport(start, end, filename);
				}
				else
				{
					manager.generateProfitReport(start, end, filename);
				}
				std::cout << "����� �������� � " << filename << "!\n";
				break;
			}
			case 7: // �����
				std::cout << "�� ��������!\n";
				break;
			default:
				std::cout << "�������� �����. ���������� �����.\n";
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "������: " << e.what() << "\n";
		}
	} while (choice != 7);

	return 0;
}

// ��������������� �������:
void displayMenu() // ����� ����
{
	std::cout << "\n=== ���� ���������� ===\n"
		<< "1. �������� ����� �����\n"
		<< "2. ����������� ��� ������\n"
		<< "3. ��������� ����� ������\n"
		<< "4. ������� �����\n"
		<< "5. ������������� ����� �� ��������\n"
		<< "6. ������������� ����� �� �������\n"
		<< "7. �����\n"
		<< "�������� ��������: ";
}

Date inputDate() // ���� ���� � ��������� ����������
{
	int d, m, y;
	while (true)
	{
		std::cout << "������� ���� (�� �� ����): ";
		std::cin >> d >> m >> y;
		if (std::cin.fail() || !Date(d, m, y).isValid())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "������������ ����! ���������� �����.\n";
		}
		else
		{
			std::cin.ignore();
			break;
		}
	}
	return Date(d, m, y);
}

double inputPositiveDouble(const std::string& prompt) // ���� �������������� ����� (double)
{
	double value;
	while (true)
	{
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "����� ������ ���� �������������! ���������� �����.\n";
		std::cin.clear();
		std::cin.ignore();
	}
	return value;
}

int inputPositiveInt(const std::string& prompt) // ���� �������������� ������ �����
{
	int value;
	while (true)
	{
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "����� ������ ���� �������������! ���������� �����.\n";
		std::cin.clear();
		std::cin.ignore();
	}
	return value;
}
std::string inputNonEmptyString(const std::string& prompt) // ���� �������� ������
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		// ������� ������ ������� � ������ � ����� ������
		size_t start = input.find_first_not_of(" \t");
		if (start != std::string::npos)
		{
			size_t end = input.find_last_not_of(" \t");
			input = input.substr(start, end - start + 1);
		}
		if (!input.empty()) break;
		std::cout << "���� �� ����� ���� ������! ���������� �����.\n";
	}
	return input;
}