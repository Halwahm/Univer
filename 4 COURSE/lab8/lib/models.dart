// lib/models.dart

import 'package:hive/hive.dart';

part 'models.g.dart';

@HiveType(typeId: 0)
class User {
  @HiveField(0)
  String name;
  
  @HiveField(1)
  String role; // 'admin', 'manager', 'user'

  User({required this.name, required this.role});
}

@HiveType(typeId: 1)
class Favorite {
  @HiveField(0)
  String item;

  Favorite(this.item);


}

@HiveType(typeId: 2)
class Product {
  @HiveField(0)
  final String name;
  @HiveField(1)
  final double price;

  Product({required this.name, required this.price});
}

// Пример данных
List<User> users = [
  User(name: "Alice", role: "admin"),
  User(name: "Bob", role: "manager"),
  User(name: "Charlie", role: "user"),
];

List<Favorite> favorites = [];

List<Product> products = [
];

