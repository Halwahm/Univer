class Worker {
  //String id;
  String name;
  String specialization;

  Worker({
    // this.id = '',
    required this.name,
    required this.specialization,
  });

  Worker.fromJson(Map<String, Object?> json)
      : this(
            name: json['name']! as String,
            specialization: json['specialization']! as String);

  Worker copyWith({
    String? name,
    String? specialization,
  }) {
    return Worker(
        name: name ?? this.name,
        specialization: specialization ?? this.specialization);
  }

  Map<String, Object?> toJson() {
    return {
      'name': name,
      'specialization': specialization,
    };
  }
}
