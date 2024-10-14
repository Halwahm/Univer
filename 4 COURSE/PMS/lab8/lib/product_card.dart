import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

import 'models/favorite_model.dart';
import 'models/product_model.dart';

class ProductCard extends StatelessWidget {
  final ProductModel product;
  final VoidCallback onPressed;
  final EdgeInsetsGeometry margin;
  final String userName;

  const ProductCard({
    Key? key,
    required this.product,
    required this.onPressed,
    required this.userName,
    this.margin = const EdgeInsets.only(right: 6),
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var favoritesBox = Hive.box<FavoriteModel>('favorites');
    bool isFavorite = favoritesBox.values
        .any((fav) => fav.productId == product.id && fav.userName == userName);

    return Container(
      margin: margin,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          GestureDetector(
            onTap: onPressed,
            child: SizedBox(
              width: 180,
              height: 190,
              child: Stack(
                children: [
                  Container(
                    decoration: BoxDecoration(
                      color: const Color(0xFF1D1E3C),
                      borderRadius: BorderRadius.circular(20),
                    ),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Image.asset(
                            product.image,
                            height: 120,
                            width: 120,
                            fit: BoxFit.contain,
                          ),
                        ),
                        Row(
                          children: [
                            Padding(
                              padding: const EdgeInsets.only(left: 8.0),
                              child: Text(
                                product.price,
                                style: const TextStyle(
                                  fontSize: 22,
                                  fontWeight: FontWeight.bold,
                                  color: Colors.white,
                                ),
                              ),
                            ),
                            const Spacer(),
                            IconButton(
                              icon: Icon(
                                isFavorite
                                    ? Icons.favorite
                                    : Icons.favorite_border,
                                color: isFavorite ? Colors.red : Colors.white,
                                size: 18,
                              ),
                              onPressed: () {
                                if (isFavorite) {
                                  var toDelete = favoritesBox.values.firstWhere(
                                      (fav) =>
                                          fav.productId == product.id &&
                                          fav.userName == userName);
                                  toDelete.delete();
                                } else {
                                  favoritesBox.add(FavoriteModel(
                                      userName: userName,
                                      productId: product.id));
                                }
                              },
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                  if (product.isOnSale)
                    Positioned(
                      top: 60,
                      left: 0,
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            horizontal: 8, vertical: 4),
                        decoration: BoxDecoration(
                          color: Colors.yellow,
                          borderRadius: BorderRadius.circular(8),
                        ),
                        child: const Text(
                          "SALE",
                          style: TextStyle(
                            color: Color(0xFF1D1E3C),
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                    ),
                ],
              ),
            ),
          ),
          const SizedBox(height: 8),
          Text(
            product.title,
            textAlign: TextAlign.center,
            style: const TextStyle(
                fontSize: 16,
                color: Color(0xFF1D1E3C),
                fontWeight: FontWeight.bold),
          ),
        ],
      ),
    );
  }
}
