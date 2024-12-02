import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:mockito/mockito.dart';
import 'package:hive/hive.dart';
import 'package:lab4/models.dart';
import 'package:lab4/product_provider.dart';
import 'package:lab4/product_list_page.dart';
import 'package:lab4/admin_product_page.dart';

class MockHiveInterface extends Mock implements HiveInterface {}
class MockBox extends Mock implements Box {}

void main() {
  late MockHiveInterface mockHiveInterface;
  late MockBox mockBox;
  late ProductProvider provider;

  setUp(() {
    mockHiveInterface = MockHiveInterface();
    mockBox = MockBox();
    provider = ProductProvider();
  });

  group('ProductProvider', () {
    test('Загружает продукты из памяти', () async {
      final products = [
        Product(name: 'Product1', price: 10.0),
        Product(name: 'Product2', price: 15.0),
      ];

      await provider.loadProducts(products);

      expect(provider.products.length, 2);
      expect(provider.products[0].name, 'Product1');
      expect(provider.products[1].price, 15.0);
    });

    test('Добавляет новый продукт в память', () async {
      await provider.addProduct('New Product', 20.0);

      expect(provider.products.length, 1);
      expect(provider.products[0].name, 'New Product');
      expect(provider.products[0].price, 20.0);
    });

    test('Переключает продукт в избранное и убирает его из избранного', () async {
      provider = ProductProvider(initialProducts: [Product(name: 'Favorite Product', price: 30.0)]);

      await provider.toggleFavorite('Favorite Product');

      expect(provider.favorites.length, 1);
      expect(provider.favorites[0].name, 'Favorite Product');

      await provider.toggleFavorite('Favorite Product');
      expect(provider.favorites.length, 0);
    });

    testWidgets('Тестирование ввода текста в поле "Product Name"', (WidgetTester tester) async {
      await tester.pumpWidget(MaterialApp(home: AdminProductPage()));

      final nameField = find.byType(TextField).first;
      await tester.enterText(nameField, 'New Product');
      await tester.pump();

      expect(find.text('New Product'), findsOneWidget);
    });

    testWidgets('Тестирование ввода текста в поле "Price"', (WidgetTester tester) async {
      await tester.pumpWidget(MaterialApp(home: AdminProductPage()));

      final priceField = find.byType(TextField).at(1);
      await tester.enterText(priceField, '30.0');
      await tester.pump();

      expect(find.text('30.0'), findsOneWidget);
    });

    testWidgets('Тестирование нажатия кнопки "Add Product"', (WidgetTester tester) async {
      await tester.pumpWidget(MaterialApp(home: AdminProductPage()));

      final nameField = find.byType(TextField).first;
      final priceField = find.byType(TextField).at(1);
      final addButton = find.byType(ElevatedButton);

      await tester.enterText(nameField, 'New Product');
      await tester.enterText(priceField, '30.0');
      await tester.pump();

      await tester.tap(addButton);
      await tester.pump();

      expect(find.text('New Product'), findsOneWidget);
      expect(find.text('30.0'), findsOneWidget);
    });

    testWidgets('Тестирование очистки полей после добавления продукта', (WidgetTester tester) async {
      await tester.pumpWidget(MaterialApp(home: AdminProductPage()));

      final nameField = find.byType(TextField).first;
      final priceField = find.byType(TextField).at(1);
      final addButton = find.byType(ElevatedButton);

      await tester.enterText(nameField, 'New Product');
      await tester.enterText(priceField, '30.0');
      await tester.pump();

      await tester.tap(addButton);
      await tester.pump();

      expect(find.text('New Product'), findsNothing);
      expect(find.text('30.0'), findsNothing);
    });
  });

}