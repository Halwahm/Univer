import 'package:flutter/material.dart';

import 'details_screen.dart';
import 'product_bloc.dart';

class HomeScreen extends StatelessWidget {
  final ProductBloc productBloc;

  HomeScreen({required this.productBloc});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xFFF3F6FD),
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0,
        flexibleSpace: Stack(
          children: [
            Positioned.fill(
              child: Container(color: Colors.white),
            ),
            Positioned(
              right: 0,
              top: 0,
              bottom: 0,
              width: MediaQuery.of(context).size.width * 0.4,
              child: Container(color: const Color(0xFFF3F6FD)),
            ),
          ],
        ),
        centerTitle: true,
        title: Image.asset('assets/images/nike_logo.png', height: 30),
        leading: const Icon(Icons.menu, color: Colors.black, size: 40),
        actions: const [
          Icon(Icons.shopping_bag_outlined, color: Colors.black, size: 40),
          SizedBox(width: 16),
        ],
      ),
      body: Stack(
        children: [
          Positioned.fill(child: Container(color: Colors.white)),
          Positioned(
            right: 0,
            top: 0,
            bottom: 0,
            width: MediaQuery.of(context).size.width * 0.4,
            child: Container(color: const Color(0xFFF3F6FD)),
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 24),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                _buildSearchBox(),
                const SizedBox(height: 20),
                Center(
                    child:
                        Image.asset('assets/images/asset1.png', height: 250)),
                const SizedBox(height: 20),
                RichText(
                  text: const TextSpan(
                    children: [
                      TextSpan(
                        text: 'Nike\n',
                        style: TextStyle(
                          fontSize: 36,
                          fontWeight: FontWeight.bold,
                          color: Color(0xFF1D1E3C),
                        ),
                      ),
                      TextSpan(
                        text: 'Collection',
                        style: TextStyle(
                          fontSize: 32,
                          fontWeight: FontWeight.w300,
                          color: Color(0xFFB0B0C3),
                        ),
                      ),
                    ],
                  ),
                ),
                const SizedBox(height: 20),
                Expanded(
                  child: StreamBuilder<Map<String, bool>>(
                    stream: productBloc.favoritesStream,
                    initialData: {},
                    builder: (context, snapshot) {
                      final favorites = snapshot.data ?? {};

                      return ListView.builder(
                        scrollDirection: Axis.horizontal,
                        itemCount: 3,
                        itemBuilder: (context, index) {
                          if (index == 0) {
                            return ProductCard(
                              image: 'assets/images/gtx2.png',
                              title: 'Nike GTX 2',
                              price: '\$329',
                              isFavorite: favorites['Nike GTX 2'] ?? false,
                              isOnSale: false, // Не на распродаже
                              onFavoriteToggle: () {
                                productBloc.toggleFavorite('Nike GTX 2');
                              },
                              onPressed: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => DetailsScreen(
                                      images: [
                                        'assets/images/gtx2.png',
                                        'assets/images/gtx.png'
                                      ],
                                      title: 'Nike GTX 2',
                                      price: '\$329',
                                      productBloc: productBloc,
                                    ),
                                  ),
                                );
                              },
                              margin: const EdgeInsets.only(right: 12),
                            );
                          } else if (index == 1) {
                            return ProductCard(
                              image: 'assets/images/gtx.png',
                              title: 'Nike GTX',
                              price: '\$100',
                              isFavorite: favorites['Nike GTX'] ?? false,
                              isOnSale: true, // На распродаже
                              onFavoriteToggle: () {
                                productBloc.toggleFavorite('Nike GTX');
                              },
                              onPressed: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => DetailsScreen(
                                      images: [
                                        'assets/images/gtx.png',
                                        'assets/images/gtx2.png'
                                      ],
                                      title: 'Nike GTX',
                                      price: '\$100',
                                      productBloc: productBloc,
                                    ),
                                  ),
                                );
                              },
                            );
                          } else {
                            return ProductCard(
                              image: 'assets/images/shoe_3.png',
                              title: 'Nike Air Zoom',
                              price: '\$150',
                              isFavorite: favorites['Nike Air Zoom'] ?? false,
                              isOnSale: false, // Не на распродаже
                              onFavoriteToggle: () {
                                productBloc.toggleFavorite('Nike Air Zoom');
                              },
                              onPressed: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => DetailsScreen(
                                      images: [
                                        'assets/images/shoe_3.png',
                                        'assets/images/gtx2.png'
                                      ],
                                      title: 'Nike Air Zoom',
                                      price: '\$150',
                                      productBloc: productBloc,
                                    ),
                                  ),
                                );
                              },
                            );
                          }
                        },
                      );
                    },
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildSearchBox() {
    return Container(
      decoration: BoxDecoration(
        color: Colors.white,
        borderRadius: BorderRadius.circular(30),
        boxShadow: [
          BoxShadow(
            color: Colors.grey.withOpacity(0.3),
            spreadRadius: 2,
            blurRadius: 6,
          ),
        ],
      ),
      padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 12),
      child: const Row(
        children: [
          Expanded(
            child: TextField(
              decoration: InputDecoration(
                border: InputBorder.none,
                hintText: "Shoes",
                hintStyle: TextStyle(color: Colors.blue, fontSize: 20),
              ),
            ),
          ),
          Icon(Icons.search, color: Colors.grey, size: 30),
        ],
      ),
    );
  }
}

class ProductCard extends StatelessWidget {
  final String image;
  final String title;
  final String price;
  final bool isFavorite;
  final bool isOnSale;
  final VoidCallback onFavoriteToggle;
  final VoidCallback onPressed;
  final EdgeInsetsGeometry margin;

  const ProductCard({
    Key? key,
    required this.image,
    required this.title,
    required this.price,
    required this.isFavorite,
    required this.isOnSale,
    required this.onFavoriteToggle,
    required this.onPressed,
    this.margin = const EdgeInsets.only(right: 6),
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: margin,
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          GestureDetector(
            onTap: onPressed,
            child: Container(
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
                            image,
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
                                price,
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
                              onPressed: onFavoriteToggle,
                            ),
                          ],
                        ),
                      ],
                    ),
                  ),
                  if (isOnSale)
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
            title,
            textAlign: TextAlign.center,
            style: const TextStyle(
              fontSize: 16,
              color: Color(0xFF1D1E3C),
              fontWeight: FontWeight.bold,
            ),
          ),
        ],
      ),
    );
  }
}
