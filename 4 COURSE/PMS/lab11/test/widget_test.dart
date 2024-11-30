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

  testWidgets('Add a todo item and drag it to a new position',
      (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    // Добавляем задачу
    final textFieldFinder = find.byKey(const Key("addField"));
    final addButtonFinder = find.byKey(const Key("addButton"));

    await tester.enterText(textFieldFinder, 'Draggable Task');
    await tester.tap(addButtonFinder);
    await tester.pumpAndSettle();

    // Проверяем, что Draggable появился
    final draggableFinder = find.byType(Draggable<String>);
    expect(draggableFinder, findsOneWidget,
        reason: 'Draggable widget not found');

    // Получаем начальное положение Draggable элемента
    final initialPosition = tester.getCenter(draggableFinder);

    // Перетаскиваем элемент
    await tester.drag(draggableFinder, const Offset(0, 100));
    await tester.pumpAndSettle();

    // Получаем финальную позицию элемента после перетаскивания
    final finalPosition = tester.getCenter(draggableFinder);

    // Проверяем, что позиция не изменилась (элемент вернулся на место)
    expect(initialPosition, equals(finalPosition),
        reason:
            'Draggable widget has moved after drag, but it should stay in the same position');
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
