import 'package:flutter/foundation.dart';
import 'models.dart';

class ProductProvider with ChangeNotifier {
  List<Product> _products;
  List<Product> _favorites;

  ProductProvider({
    List<Product>? initialProducts,
    List<Product>? initialFavorites,
  })  : _products = initialProducts ?? [],
        _favorites = initialFavorites ?? [];

  List<Product> get products => _products;
  List<Product> get favorites => _favorites;

  Future<void> loadProducts(List<Product> products) async {
    _products = products;
    notifyListeners();
  }

  Future<void> addProduct(String name, double price) async {
    _products.add(Product(name: name, price: price));
    notifyListeners();
  }

  Future<void> loadFavorites(List<Product> favorites) async {
    _favorites = favorites;
    notifyListeners();
  }

  Future<void> toggleFavorite(String productName) async {
    final productIndex = _favorites.indexWhere((product) => product.name == productName);

    if (productIndex != -1) {
      _favorites.removeAt(productIndex); // Удаляем из избранного, если уже добавлен
    } else {
      final product = _products.firstWhere((p) => p.name == productName);
      if (product != null) {
        _favorites.add(product); // Добавляем в избранное, если найден
      }
    }

    notifyListeners();
  }
}
