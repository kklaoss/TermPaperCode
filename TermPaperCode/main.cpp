#include <iostream>
#include "InventoryManager.h"
#include "Date.h"
#include <memory>

// Прототипы вспомогательных функций:
void displayMenu();
Date inputDate();
double inputPositiveDouble(const std::string& prompt);
int inputPositiveInt(const std::string& prompt);
std::string inputNonEmptyString(const std::string& prompt);

// Основная логика программы:
int main()
{
	system("chcp 1251"); // Настройка кодировки для Windows
	setlocale(LC_ALL, "RUS"); // Поддержка кириллицы
	InventoryManager manager; // Создание менеджера склада
	int choice = 0;

	// Цикл меню:
	do
	{
		displayMenu(); // Вывод меню
		std::cin >> choice;
		std::cin.ignore();
		try
		{
			// Обработка выбора пользователя:
			switch (choice)
			{
			case 1: // Добавление товара (с выбором категории)
			{
				std::string name = inputNonEmptyString("Введите название товара: ");
				int categoryChoice;

				double pPrice = inputPositiveDouble("Цена закупки: ");
				double sPrice = inputPositiveDouble("Цена продажи: ");
				int qty = inputPositiveInt("Начальное количество: ");

				std::cout << "Выберите категорию:\n"
					<< "1. Письменные принадлежности\n"
					<< "2. Бумажная продукция\n"
					<< "3. Офисная техника\n"
					<< "Ваш выбор: ";
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
					std::cout << "Неверный выбор, товар не добавлен!\n";
					continue;
				}

				manager.addItem(item);
				std::cout << "Товар добавлен!\n";
				break;
			}
			case 2: // Просмотр всех товаров
			{
				const auto& items = manager.getAllItems();
				if (items.empty())
				{
					std::cout << "Список товаров пуст.\n";
					break;
				}
				std::cout << "\nСписок товаров:\n";
				for (const auto& item : items)
				{
					std::cout << "Название: " << item->getName()
						<< ", Цена закупки: " << item->getPurchasePrice()
						<< ", Цена продажи: " << item->getSalePrice()
						<< ", Количество: " << item->getQuantity() << "\n";
				}
				break;
			}
			case 3: // Пополнение запаса
			{
				std::string name = inputNonEmptyString("Введите название товара: ");

				auto item = manager.findItemByName(name);
				if (!item)
				{
					std::cout << "Товар не найден!\n";
					break;
				}

				int quantity = inputPositiveInt("Введите количество для пополнения: ");
				Date date = inputDate();
				manager.restockItem(item, quantity, date);
				std::cout << "Товар пополнен!\n";
				break;
			}
			case 4: // Продажа товара (с проверкой наличия)
			{
				std::string name = inputNonEmptyString("Введите название товара: ");

				auto item = manager.findItemByName(name);
				if (!item)
				{
					std::cout << "Товар не найден!\n";
					break;
				}

				int quantity = inputPositiveInt("Введите количество для продажи: ");
				Date date = inputDate();
				manager.sellItem(item, quantity, date);
				std::cout << "Продажа оформлена!\n";
				break;
			}
			case 5: // Отчет по продажам
			case 6: // Отчет по прибыли
			{
				Date start = inputDate();
				Date end = inputDate();
				std::string filename = inputNonEmptyString("Введите имя файла для отчета: ");

				if (choice == 5)
				{
					manager.generateSalesReport(start, end, filename);
				}
				else
				{
					manager.generateProfitReport(start, end, filename);
				}
				std::cout << "Отчет сохранен в " << filename << "!\n";
				break;
			}
			case 7: // Выход
				std::cout << "До свидания!\n";
				break;
			default:
				std::cout << "Неверный выбор. Попробуйте снова.\n";
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Ошибка: " << e.what() << "\n";
		}
	} while (choice != 7);

	return 0;
}

// Вспомогательные функции:
void displayMenu() // Вывод меню
{
	std::cout << "\n=== Меню управления ===\n"
		<< "1. Добавить новый товар\n"
		<< "2. Просмотреть все товары\n"
		<< "3. Пополнить запас товара\n"
		<< "4. Продать товар\n"
		<< "5. Сгенерировать отчет по продажам\n"
		<< "6. Сгенерировать отчет по прибыли\n"
		<< "7. Выход\n"
		<< "Выберите действие: ";
}

Date inputDate() // Ввод даты с проверкой валидности
{
	int d, m, y;
	while (true)
	{
		std::cout << "Введите дату (дд мм гггг): ";
		std::cin >> d >> m >> y;
		if (std::cin.fail() || !Date(d, m, y).isValid())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Некорректная дата! Попробуйте снова.\n";
		}
		else
		{
			std::cin.ignore();
			break;
		}
	}
	return Date(d, m, y);
}

double inputPositiveDouble(const std::string& prompt) // Ввод положительного числа (double)
{
	double value;
	while (true)
	{
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "Число должно быть положительным! Попробуйте снова.\n";
		std::cin.clear();
		std::cin.ignore();
	}
	return value;
}

int inputPositiveInt(const std::string& prompt) // Ввод положительного целого числа
{
	int value;
	while (true)
	{
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "Число должно быть положительным! Попробуйте снова.\n";
		std::cin.clear();
		std::cin.ignore();
	}
	return value;
}
std::string inputNonEmptyString(const std::string& prompt) // Ввод непустой строки
{
	std::string input;
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		// Удаляем лишние пробелы в начале и конце строки
		size_t start = input.find_first_not_of(" \t");
		if (start != std::string::npos)
		{
			size_t end = input.find_last_not_of(" \t");
			input = input.substr(start, end - start + 1);
		}
		if (!input.empty()) break;
		std::cout << "Поле не может быть пустым! Попробуйте снова.\n";
	}
	return input;
}