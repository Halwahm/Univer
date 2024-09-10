mixin PersonInfoMixin {
  void showSkills(Set<String> skills) {
    print('Skills: $skills');
  }

  void promoteEligibility(int experienceYears) {
    if (experienceYears > 3) {
      print('Eligible for a promotion.');
    } else {
      print('Not eligible for a promotion yet.');
    }
  }
}
