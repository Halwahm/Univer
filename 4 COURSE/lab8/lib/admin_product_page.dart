import 'package:flutter/material.dart';
import 'package:hive/hive.dart';
import 'models.dart';
import 'product_list_page.dart'; // Подключение моделей

class AdminProductPage extends StatefulWidget {
  @override
  _AdminProductPageState createState() => _AdminProductPageState();
}

class _AdminProductPageState extends State<AdminProductPage> {
  final TextEditingController _nameController = TextEditingController();
  final TextEditingController _priceController = TextEditingController();

  // Переменная для хранения текущей позиции кнопки и цвета
  Offset _buttonPosition = Offset(100, 200);  // Начальная позиция кнопки
  Color _buttonColor = Colors.blue;  // Начальный цвет кнопки

  void addProduct() {
    setState(() {
      products.add(Product(
        name: _nameController.text,
        price: double.parse(_priceController.text),
      ));

      var box = Hive.box("products");
      box.put("products", products).then(print);

      _nameController.clear();
      _priceController.clear();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Admin Product Management')),
      body: Column(
        children: [
          TextField(controller: _nameController, decoration: InputDecoration(labelText: 'Product Name')),
          TextField(controller: _priceController, decoration: InputDecoration(labelText: 'Price')),

          // Используем Stack для точного размещения кнопки
          Expanded(
            child: Stack(
              children: [
                // Оборачиваем Draggable в Positioned
                Positioned(
                  left: _buttonPosition.dx,
                  top: _buttonPosition.dy,
                  child: Draggable(
                    data: 'Add Product', // Данные, которые передаются при перетаскивании
                    feedback: Material(
                      color: Colors.transparent,
                      child: ElevatedButton(
                        onPressed: () {},
                        child: Text('Add Product (Dragging)'),
                      ),
                    ),
                    childWhenDragging: Container(), // Показываем пустую область, пока перетаскиваем
                    onDragEnd: (details) {
                      // Когда перетаскивание завершено, обновляем позицию кнопки
                      setState(() {
                        _buttonPosition = details.offset;
                        // Меняем цвет в зависимости от позиции
                        if (_buttonPosition.dx > 300 && _buttonPosition.dy > 400) {
                          _buttonColor = Colors.red;
                        } else if (_buttonPosition.dx < 200 && _buttonPosition.dy < 300) {
                          _buttonColor = Colors.green;
                        } else {
                          _buttonColor = Colors.blue;
                        }
                      });
                    },
                    child: ElevatedButton(
                      onPressed: addProduct,
                      style: ElevatedButton.styleFrom(
                        backgroundColor: _buttonColor, // Устанавливаем цвет кнопки
                      ),
                      child: Text('Add Product'),
                    ),
                  ),
                ),
              ],
            ),
          ),
          Expanded(child: ProductListPage()), // Это ваш экран со списком продуктов
        ],
      ),
    );
  }
}
