import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:lab11/auth/home.dart';

void main() {
  testWidgets('Enter text into field and verify', (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    final textFieldFinder = find.byKey(Key("addField"));
    await tester.enterText(textFieldFinder, 'New Worker');
    await tester.pumpAndSettle();

    // Проверяем, что текст "New Worker" отобразился
    expect(find.text('New Worker'), findsOneWidget);
  });

  testWidgets('Tap on add button and check list item appears',
      (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    final textFieldFinder = find.byKey(Key("addField"));
    await tester.enterText(textFieldFinder, 'New Worker');

    // Проверяем наличие кнопки добавления
    final addButtonFinder = find.byKey(Key("addButton"));
    expect(addButtonFinder, findsOneWidget, reason: 'Add button not found');

    await tester.tap(addButtonFinder);
    await tester.pumpAndSettle();

    // Проверяем, что элемент добавлен в список
    expect(find.text('New Worker'), findsOneWidget);
  });

  testWidgets('Drag worker card to new position', (WidgetTester tester) async {
    await tester.pumpWidget(MaterialApp(home: MyHomePage()));

    final textFieldFinder = find.byKey(Key("addField"));
    await tester.enterText(textFieldFinder, 'Test Worker');

    final addButtonFinder = find.byKey(Key("addButton"));
    await tester.tap(addButtonFinder);
    await tester.pumpAndSettle();

    // Поиск draggable виджета
    final draggableFinder = find.byType(Draggable);
    expect(draggableFinder, findsWidgets, reason: 'No draggable widgets found');

    // Перетаскивание виджета
    await tester.drag(draggableFinder.first, Offset(0, 100));
    await tester.pumpAndSettle();

    // Проверяем, что элемент все еще существует
    expect(find.text('Test Worker'), findsOneWidget);
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
