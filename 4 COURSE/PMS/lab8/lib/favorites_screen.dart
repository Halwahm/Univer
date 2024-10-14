import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:hive/hive.dart';
import 'package:hive_flutter/adapters.dart';

import 'details_screen.dart';
import 'models/favorite_model.dart';
import 'models/product_model.dart';

class FavoritesScreen extends StatelessWidget {
  final String userName;

  const FavoritesScreen({Key? key, required this.userName}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var favoritesBox = Hive.box<FavoriteModel>('favorites');
    var productsBox = Hive.box<ProductModel>('products');

    return Scaffold(
      appBar: AppBar(
        title: const Text('Избранное'),
      ),
      body: ValueListenableBuilder(
        valueListenable: favoritesBox.listenable(),
        builder: (context, Box<FavoriteModel> box, _) {
          List<FavoriteModel> userFavorites =
              box.values.where((fav) => fav.userName == userName).toList();
          if (userFavorites.isEmpty) {
            return const Center(child: Text('Нет избранных товаров'));
          } else {
            return ListView.builder(
              itemCount: userFavorites.length,
              itemBuilder: (context, index) {
                FavoriteModel favorite = userFavorites[index];
                ProductModel? product = productsBox.values
                    .firstWhereOrNull((prod) => prod.id == favorite.productId);

                if (product == null) {
                  return const SizedBox.shrink();
                }

                return ListTile(
                  title: Text(product.title),
                  subtitle: Text(product.price),
                  onTap: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) => DetailsScreen(
                            product: product, currentUser: userName),
                      ),
                    );
                  },
                  trailing: IconButton(
                    icon: const Icon(Icons.delete),
                    onPressed: () {
                      favorite.delete();
                    },
                  ),
                );
              },
            );
          }
        },
      ),
    );
  }
}
