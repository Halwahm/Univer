import 'package:flutter/material.dart';

class ProductProvider with ChangeNotifier {
  Map<String, bool> _favorites = {};
  String _selectedSize = '6.5';

  bool isFavorite(String title) {
    return _favorites[title] ?? false;
  }

  void toggleFavorite(String title) {
    _favorites[title] = !isFavorite(title);
    notifyListeners();
  }

  String get selectedSize => _selectedSize;

  void selectSize(String size) {
    _selectedSize = size;
    notifyListeners();
  }
}
