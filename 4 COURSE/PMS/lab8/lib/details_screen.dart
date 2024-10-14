import 'package:flutter/material.dart';
import 'package:hive/hive.dart';

import 'models/favorite_model.dart';
import 'models/product_model.dart';

class DetailsScreen extends StatefulWidget {
  final ProductModel product;
  final String currentUser;

  const DetailsScreen({
    Key? key,
    required this.product,
    required this.currentUser,
  }) : super(key: key);

  @override
  _DetailsScreenState createState() => _DetailsScreenState();
}

class _DetailsScreenState extends State<DetailsScreen> {
  String selectedSize = '6.5';
  int currentPage = 0;
  late Box<FavoriteModel> favoritesBox;

  @override
  void initState() {
    super.initState();
    favoritesBox = Hive.box<FavoriteModel>('favorites');
  }

  @override
  Widget build(BuildContext context) {
    bool isFavorite = favoritesBox.values.any((fav) =>
        fav.productId == widget.product.id &&
        fav.userName == widget.currentUser);

    return Scaffold(
      backgroundColor: Colors.white,
      appBar: AppBar(
        backgroundColor: Colors.white,
        elevation: 0,
        centerTitle: true,
        title: Image.asset('assets/images/nike_logo.png', height: 30),
        leading: IconButton(
          icon: const Icon(Icons.arrow_back, color: Colors.black, size: 40),
          onPressed: () {
            Navigator.pop(context);
          },
        ),
        actions: [
          IconButton(
            icon: const Icon(Icons.shopping_bag_outlined,
                color: Colors.black, size: 40),
            onPressed: () {},
          ),
          const SizedBox(width: 16),
        ],
      ),
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            children: [
              Stack(
                children: [
                  SizedBox(
                    height: 250,
                    child: PageView.builder(
                      itemCount: widget.product.images.length,
                      onPageChanged: (index) {
                        setState(() {
                          currentPage = index;
                        });
                      },
                      itemBuilder: (context, index) {
                        return Image.asset(widget.product.images[index],
                            fit: BoxFit.contain);
                      },
                    ),
                  ),
                  if (widget.product.isOnSale)
                    const Positioned(
                      top: 10,
                      left: 10,
                      child: Chip(
                        label: Text(
                          'SALE',
                          style: TextStyle(
                            color: Color(0xFF1D1E3C),
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                        backgroundColor: Colors.yellow,
                      ),
                    ),
                  Positioned(
                    top: 10,
                    right: 10,
                    child: IconButton(
                      icon: Icon(
                        isFavorite ? Icons.favorite : Icons.favorite_border,
                        color: Colors.red,
                        size: 40,
                      ),
                      onPressed: () {
                        setState(() {
                          if (isFavorite) {
                            var toDelete = favoritesBox.values.firstWhere(
                                (fav) =>
                                    fav.productId == widget.product.id &&
                                    fav.userName == widget.currentUser);
                            toDelete.delete();
                          } else {
                            favoritesBox.add(FavoriteModel(
                                userName: widget.currentUser,
                                productId: widget.product.id));
                          }
                        });
                      },
                    ),
                  ),
                ],
              ),
              const SizedBox(height: 20),
              Center(
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: List.generate(
                    widget.product.images.length,
                    (index) => Container(
                      margin: const EdgeInsets.symmetric(horizontal: 4),
                      width: 10,
                      height: 10,
                      decoration: BoxDecoration(
                        shape: BoxShape.circle,
                        color:
                            currentPage == index ? Colors.black : Colors.grey,
                      ),
                    ),
                  ),
                ),
              ),
              const SizedBox(height: 20),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Text(
                    widget.product.title,
                    style: const TextStyle(
                      color: Color(0xFF1D1E3C),
                      fontSize: 36,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  Row(
                    children: List.generate(5, (index) {
                      return Icon(
                        index < 4 ? Icons.star : Icons.star_border,
                        color: index < 4 ? Colors.yellow : Colors.grey,
                      );
                    }),
                  ),
                ],
              ),
              const SizedBox(height: 10),
              Text(
                widget.product.description,
                style: const TextStyle(
                  fontSize: 22,
                  color: Color(0xFFB0B0C3),
                  height: 1.3,
                ),
              ),
              const SizedBox(height: 16),
              const Text(
                "Размер",
                style: TextStyle(
                  fontSize: 22,
                  fontWeight: FontWeight.bold,
                  color: Color(0xFF1D1E3C),
                ),
              ),
              const SizedBox(height: 8),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: ['5', '5.5', '6', '6.5', '7'].map((size) {
                  return GestureDetector(
                    onTap: () {
                      setState(() {
                        selectedSize = size;
                      });
                    },
                    child: Container(
                      height: 50,
                      width: 50,
                      margin: const EdgeInsets.symmetric(horizontal: 4),
                      decoration: BoxDecoration(
                        border: Border.all(
                          color: size == selectedSize
                              ? const Color(0xFF1D1E3C)
                              : Colors.grey,
                        ),
                        color: size == selectedSize
                            ? const Color(0xFF1D1E3C)
                            : Colors.transparent,
                        borderRadius: BorderRadius.circular(10),
                      ),
                      child: Center(
                        child: Text(
                          size,
                          style: TextStyle(
                            color: size == selectedSize
                                ? Colors.yellow
                                : const Color(0xFF1D1E3C),
                            fontSize: 16,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                    ),
                  );
                }).toList(),
              ),
              const SizedBox(height: 24),
              Row(
                children: [
                  const Text(
                    "Отзывы 39",
                    style: TextStyle(
                      fontSize: 22,
                      fontWeight: FontWeight.bold,
                      color: Color(0xFF1D1E3C),
                    ),
                  ),
                  const SizedBox(width: 40),
                  Row(
                    children: [
                      CircleAvatar(
                        backgroundImage: AssetImage('assets/images/user1.jpg'),
                        radius: 26,
                      ),
                      CircleAvatar(
                        backgroundImage: AssetImage('assets/images/user2.jpg'),
                        radius: 26,
                      ),
                      CircleAvatar(
                        backgroundImage: AssetImage('assets/images/user3.jpg'),
                        radius: 26,
                      ),
                      CircleAvatar(
                        backgroundImage: AssetImage('assets/images/user4.png'),
                        radius: 26,
                      ),
                    ],
                  ),
                ],
              ),
              const SizedBox(height: 40),
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Container(
                    padding:
                        const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                    decoration: BoxDecoration(
                      color: Colors.white,
                      borderRadius: BorderRadius.circular(20),
                      border: Border.all(color: Colors.grey),
                    ),
                    child: Text(
                      widget.product.price,
                      style: const TextStyle(
                        fontSize: 28,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () {},
                    style: ElevatedButton.styleFrom(
                      backgroundColor: const Color(0xFF1D1E3C),
                      padding: const EdgeInsets.symmetric(
                          horizontal: 50, vertical: 20),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(20),
                      ),
                    ),
                    child: const Text(
                      "+ Добавить в корзину",
                      style: TextStyle(
                        fontSize: 18,
                        fontWeight: FontWeight.bold,
                        color: Colors.yellow,
                      ),
                    ),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}
