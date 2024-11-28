import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:lab11/auth/home.dart';
import 'package:lab11/db_services.dart';
import 'package:mockito/mockito.dart';

class MockDatabaseService extends Mock implements DatabaseService {}

void main() {
  testWidgets('Enter text into field and verify', (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    await tester.tap(find.byKey(const Key("addButton")));
    await tester.pumpAndSettle();

    final textFieldFinder = find.byType(TextFormField).first;
    await tester.enterText(textFieldFinder, 'New Worker');
    await tester.pumpAndSettle();

    // Проверяем, что текст "New Worker" отобразился в поле ввода
    expect(find.widgetWithText(TextFormField, 'New Worker'), findsOneWidget);
  });

  testWidgets('Tap on add button and check list item appears',
      (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    // Находим поле ввода и вводим данные
    await tester.enterText(find.byKey(const Key("addField")), 'New Worker');
    await tester.tap(find.byKey(const Key("addButton")));
    await tester.pumpAndSettle();

    // Проверяем, что элемент появился в списке
    expect(find.text('New Worker'), findsOneWidget);
  });

  testWidgets('Testing Draggable interaction', (WidgetTester tester) async {
    // Отрисовываем MyHomePage
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    // Ждем загрузки UI
    await tester.pumpAndSettle();

    // Проверяем, что есть хотя бы один Draggable
    expect(find.byType(Draggable), findsOneWidget);

    // Найдем первый Draggable
    final draggableFinder = find.byType(Draggable).first;

    // Получаем начальную позицию
    final initialPosition = tester.getTopLeft(draggableFinder);

    // Выполняем перетаскивание
    await tester.drag(draggableFinder, const Offset(100, 100));
    await tester.pumpAndSettle();

    // Проверяем, что позиция изменилась
    final newPosition = tester.getTopLeft(draggableFinder);
    expect(newPosition, isNot(initialPosition));
  });

  testWidgets('Enter text, tap add, and verify multiple items',
      (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    await tester.enterText(find.byKey(Key("addField")), 'Worker 1');
    await tester.tap(find.byKey(Key("addButton")));
    await tester.pumpAndSettle();

    await tester.enterText(find.byKey(Key("addField")), 'Worker 2');
    await tester.tap(find.byKey(Key("addButton")));
    await tester.pumpAndSettle();

    // Проверяем, что оба элемента добавлены в список
    expect(find.text('Worker 1'), findsOneWidget);
    expect(find.text('Worker 2'), findsOneWidget);
  });

  testWidgets('Ensure no duplicate entries on add',
      (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    await tester.enterText(find.byKey(Key("addField")), 'Unique Worker');
    await tester.tap(find.byKey(Key("addButton")));
    await tester.pumpAndSettle();

    await tester.enterText(find.byKey(Key("addField")), 'Unique Worker');
    await tester.tap(find.byKey(Key("addButton")));
    await tester.pumpAndSettle();

    // Проверяем, что элемент "Unique Worker" добавлен только один раз
    expect(find.text('Unique Worker'), findsOneWidget);
  });
}
