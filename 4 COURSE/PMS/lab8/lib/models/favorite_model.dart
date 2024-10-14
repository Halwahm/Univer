import 'package:hive/hive.dart';

part 'favorite_model.g.dart';

@HiveType(typeId: 2)
class FavoriteModel extends HiveObject {
  @HiveField(0)
  String userName;

  @HiveField(1)
  String productId;

  FavoriteModel({required this.userName, required this.productId});
}
