import 'package:flutter/material.dart';

import 'product_bloc.dart';

class DetailsScreen extends StatelessWidget {
  final List<String> images;
  final String title;
  final String price;
  final ProductBloc productBloc;

  const DetailsScreen({
    Key? key,
    required this.images,
    required this.title,
    required this.price,
    required this.productBloc,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
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
          StreamBuilder<Map<String, bool>>(
            stream: productBloc.favoritesStream,
            initialData: {},
            builder: (context, snapshot) {
              final isFavorite = snapshot.data?[title] ?? false;
              return IconButton(
                icon: Icon(
                  isFavorite ? Icons.favorite : Icons.favorite_border,
                  color: isFavorite ? Colors.red : Colors.black,
                  size: 40,
                ),
                onPressed: () {
                  productBloc.toggleFavorite(title);
                },
              );
            },
          ),
          const SizedBox(width: 16),
        ],
      ),
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Center(
                child: Stack(
                  children: [
                    SizedBox(
                      height: 250,
                      child: PageView.builder(
                        itemCount: images.length,
                        onPageChanged: (index) {},
                        itemBuilder: (context, index) {
                          return Image.asset(images[index],
                              fit: BoxFit.contain);
                        },
                      ),
                    ),
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
                  ],
                ),
              ),
              const SizedBox(height: 20),
              Center(
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: List.generate(
                    images.length,
                    (index) => Container(
                      margin: const EdgeInsets.symmetric(horizontal: 4),
                      width: 10,
                      height: 10,
                      decoration: BoxDecoration(
                        shape: BoxShape.circle,
                        color: Colors.grey,
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
                    title,
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
              const Text(
                "The Nike GTX Shoe borrows design lines from the heritage runners like the Nike React technology.",
                style: TextStyle(
                  fontSize: 22,
                  color: Color(0xFFB0B0C3),
                  height: 1.3,
                ),
              ),
              const SizedBox(height: 16),
              const Text(
                "Size",
                style: TextStyle(
                  fontSize: 22,
                  fontWeight: FontWeight.bold,
                  color: Color(0xFF1D1E3C),
                ),
              ),
              const SizedBox(height: 8),
              StreamBuilder<String>(
                stream: productBloc.selectedSizeStream,
                initialData: '6.5',
                builder: (context, snapshot) {
                  final selectedSize = snapshot.data ?? '6.5';

                  return Row(
                    mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                    children: ['5', '5.5', '6', '6.5', '7'].map((size) {
                      return GestureDetector(
                        onTap: () {
                          productBloc.selectSize(size);
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
                  );
                },
              ),
              const SizedBox(height: 24),
              const Row(
                children: [
                  Text(
                    "Reviews 39",
                    style: TextStyle(
                      fontSize: 22,
                      fontWeight: FontWeight.bold,
                      color: Color(0xFF1D1E3C),
                    ),
                  ),
                  SizedBox(width: 40),
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
                      price,
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
                      "+ Add To Cart",
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
