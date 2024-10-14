import 'package:hive/hive.dart';

part 'product_model.g.dart';

@HiveType(typeId: 1)
class ProductModel extends HiveObject {
  @HiveField(0)
  String id;

  @HiveField(1)
  String title;

  @HiveField(2)
  String price;

  @HiveField(3)
  String image;

  @HiveField(4)
  List<String> images;

  @HiveField(5)
  String description;

  @HiveField(6)
  bool isFavorite;

  @HiveField(7)
  bool isOnSale;

  ProductModel({
    required this.id,
    required this.title,
    required this.price,
    required this.image,
    required this.images,
    required this.description,
    this.isFavorite = false,
    this.isOnSale = false,
  });
}
