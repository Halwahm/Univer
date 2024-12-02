import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:lab4/drag.dart'; // Импорт вашего класса DragPage

void main() {
  testWidgets('Test Drag and Drop Button with Key', (WidgetTester tester) async {
    // Построение виджета
    await tester.pumpWidget(MaterialApp(home: const DragPage()));

    final draggableButton = find.byKey(Key('draggable_button'));

    // Проверяем, что кнопка найдена
    expect(draggableButton, findsOneWidget);

    if (draggableButton.evaluate().isNotEmpty) {
      print('Draggable button found.');
    } else {
      print('Draggable button not found.');
    }

    // Проверка, что Draggable элемент найден
    final draggable = find.byType(Draggable<String>);
    expect(draggable, findsOneWidget);

    // Получаем начальные координаты кнопки
    final initialPosition = tester.getTopLeft(draggableButton);
    print('Initial Position: $initialPosition');

    // Перемещаем кнопку
    await tester.drag(draggableButton, Offset(150, 150)); // Перемещение
    await tester.pumpAndSettle(); // Ожидание завершения анимации

    // Получаем новые координаты кнопки
    final newPosition = tester.getTopLeft(draggableButton);
    print('New Position: $newPosition');

    // Проверяем, что позиция изменилась (координаты не одинаковы)
    expect(newPosition, isNot(equals(initialPosition)));

    // Дополнительные проверки, например, можно проверить, что текст изменился
    // Если вы хотите проверить, что текст изменился после перетаскивания:
    // expect(find.textContaining('Dropped at'), findsOneWidget);
  });
}
