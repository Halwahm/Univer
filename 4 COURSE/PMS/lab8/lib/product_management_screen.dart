import 'package:flutter/material.dart';
import 'package:hive_flutter/adapters.dart';

import 'models/product_model.dart';

class ProductManagementScreen extends StatefulWidget {
  @override
  _ProductManagementScreenState createState() =>
      _ProductManagementScreenState();
}

class _ProductManagementScreenState extends State<ProductManagementScreen> {
  late Box<ProductModel> productsBox;

  @override
  void initState() {
    super.initState();
    productsBox = Hive.box<ProductModel>('products');
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Управление товарами'),
      ),
      body: ValueListenableBuilder(
        valueListenable: productsBox.listenable(),
        builder: (context, Box<ProductModel> box, _) {
          if (box.values.isEmpty) {
            return const Center(child: Text('Нет товаров'));
          } else {
            return ListView.builder(
              itemCount: box.values.length,
              itemBuilder: (context, index) {
                ProductModel product = box.getAt(index)!;
                return ListTile(
                  title: Text(product.title),
                  subtitle: Text(product.price),
                  trailing: IconButton(
                    icon: const Icon(Icons.delete),
                    onPressed: () {
                      product.delete();
                      setState(() {});
                    },
                  ),
                  onTap: () => _showEditProductDialog(context, product),
                );
              },
            );
          }
        },
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _showAddProductDialog(context),
        child: const Icon(Icons.add),
      ),
    );
  }

  void _showAddProductDialog(BuildContext context) {
    String title = '';
    String price = '';
    String image = '';
    String description = '';
    bool isOnSale = false;

    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Добавить товар'),
          content: SingleChildScrollView(
            child: Column(
              children: [
                TextField(
                  decoration: const InputDecoration(labelText: 'Название'),
                  onChanged: (value) {
                    title = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Цена'),
                  onChanged: (value) {
                    price = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Изображение'),
                  onChanged: (value) {
                    image = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Описание'),
                  onChanged: (value) {
                    description = value;
                  },
                ),
                CheckboxListTile(
                  title: const Text('Распродажа'),
                  value: isOnSale,
                  onChanged: (value) {
                    setState(() {
                      isOnSale = value!;
                    });
                  },
                ),
              ],
            ),
          ),
          actions: [
            TextButton(
              onPressed: () {
                productsBox.add(ProductModel(
                  id: DateTime.now().toString(),
                  title: title,
                  price: price,
                  image: image,
                  images: [image],
                  description: description,
                  isOnSale: isOnSale,
                ));
                Navigator.pop(context);
              },
              child: const Text('Добавить'),
            ),
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: const Text('Отмена'),
            ),
          ],
        );
      },
    );
  }

  void _showEditProductDialog(BuildContext context, ProductModel product) {
    String title = product.title;
    String price = product.price;
    String image = product.image;
    String description = product.description;
    bool isOnSale = product.isOnSale;

    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Редактировать товар'),
          content: SingleChildScrollView(
            child: Column(
              children: [
                TextField(
                  decoration: const InputDecoration(labelText: 'Название'),
                  controller: TextEditingController(text: title),
                  onChanged: (value) {
                    title = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Цена'),
                  controller: TextEditingController(text: price),
                  onChanged: (value) {
                    price = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Изображение'),
                  controller: TextEditingController(text: image),
                  onChanged: (value) {
                    image = value;
                  },
                ),
                TextField(
                  decoration: const InputDecoration(labelText: 'Описание'),
                  controller: TextEditingController(text: description),
                  onChanged: (value) {
                    description = value;
                  },
                ),
                CheckboxListTile(
                  title: const Text('Распродажа'),
                  value: isOnSale,
                  onChanged: (value) {
                    setState(() {
                      isOnSale = value!;
                    });
                  },
                ),
              ],
            ),
          ),
          actions: [
            TextButton(
              onPressed: () {
                product.title = title;
                product.price = price;
                product.image = image;
                product.description = description;
                product.isOnSale = isOnSale;
                product.save();
                Navigator.pop(context);
              },
              child: const Text('Сохранить'),
            ),
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: const Text('Отмена'),
            ),
          ],
        );
      },
    );
  }
}
