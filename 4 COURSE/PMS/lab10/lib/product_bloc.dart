import 'dart:async';

class ProductBloc {
  final _favoritesController = StreamController<Map<String, bool>>.broadcast();
  Map<String, bool> _favorites = {};

  Stream<Map<String, bool>> get favoritesStream => _favoritesController.stream;

  void toggleFavorite(String title) {
    _favorites[title] = !(_favorites[title] ?? false);
    _favoritesController.sink.add(_favorites);
  }

  final _sizeController = StreamController<String>.broadcast();
  String _selectedSize = '6.5';

  Stream<String> get selectedSizeStream => _sizeController.stream;

  void selectSize(String size) {
    _selectedSize = size;
    _sizeController.sink.add(_selectedSize);
  }

  void dispose() {
    _favoritesController.close();
    _sizeController.close();
  }
}
