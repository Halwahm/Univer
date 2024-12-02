import 'package:flutter/material.dart';

class DragPage extends StatefulWidget {
  const DragPage({super.key});

  @override
  _DragPageState createState() => _DragPageState();
}

class _DragPageState extends State<DragPage> {
  double top = 100.0;
  double left = 100.0;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Draggable Demo'),
      ),
      body: Stack(
        children: [
          // Перетаскиваемый элемент с ключом для тестирования
          Positioned(
            top: top,
            left: left,
            child: Draggable<String>(
              key: Key('draggable_button'), // Ключ для тестирования
              data: 'Add Worker!', // Данные, передаваемые при перетаскивании
              feedback: Material(
                color: Colors.transparent, // Прозрачность фона
                child: Container(
                  width: 100,
                  height: 50,
                  color: Colors.blue,
                  alignment: Alignment.center,
                  child: const Text(
                    'Add Product',
                    style: TextStyle(color: Colors.white),
                  ),
                ),
              ),
              childWhenDragging:
                  Container(), // Виджет, отображаемый во время перетаскивания
              onDragUpdate: (details) {
                setState(() {
                  // Обновляем позицию перетаскиваемого элемента
                  top = details.localPosition.dy;
                  left = details.localPosition.dx;
                });
              },
              onDraggableCanceled: (velocity, offset) {
                setState(() {
                  // Возвращаем позицию элемента после отмены перетаскивания
                  top = offset.dy;
                  left = offset.dx;
                });
              },
              child: Container(
                width: 100,
                height: 50,
                color: Colors.blue,
                alignment: Alignment.center,
                child: const Text(
                  'Add Worker',
                  style: TextStyle(color: Colors.white),
                ),
              ),
            ),
          ),
        ],
      ),
    );
  }
}
