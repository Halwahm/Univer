// lib/product_list_page.dart

import 'package:flutter/material.dart';
import 'package:hive/hive.dart';
import 'models.dart'; // Подключение моделей

class ProductListPage extends StatefulWidget {
  @override
  _ProductListPageState createState() => _ProductListPageState();
}

class _ProductListPageState extends State<ProductListPage> {

  bool isFavorite(String productName) {
    // Проверяем, есть ли товар в избранном
    for (var fav in favorites) {
      if (fav.item == productName) {
        return true;
      }
    }
    return false;
  }

  void toggleFavorite(String productName) {
    setState(() {
      for (var i = 0; i < favorites.length; i++) {
        Favorite fav = favorites.elementAt(i);
        if (fav.item == productName) {
          favorites.removeAt(i); // Удаляем, если уже в избранном
          return;
        }
      }
      favorites.add(Favorite(productName)); // Добавляем в избранное, если не было
      Hive.box("favorites").put("favorites", favorites);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Products')),
      body: ListView.builder(
        itemCount: products.length,
        itemBuilder: (context, index) {
          return ListTile(
            title: Text(products[index].name),
            subtitle: Text("\$${products[index].price}"),
            trailing: IconButton(
              icon: Icon(
                isFavorite(products[index].name) ? Icons.favorite : Icons.favorite_border, // Иконка в зависимости от избранного
                color: isFavorite(products[index].name) ? Colors.red : Colors.grey, // Цвет иконки
              ),
              onPressed: () {
                toggleFavorite(products[index].name); // Меняем состояние избранного
              },
            ),
          );
        },
      ),
    );
  }
}
