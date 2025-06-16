import { Injectable } from '@nestjs/common';
import * as bcrypt from 'bcrypt';

import { DatabaseService } from 'data-service';
import { SALT_OR_ROUNDS } from 'common';


@Injectable()
export class SeedService {
  constructor(private readonly dataService: DatabaseService) {}

  async seed() {
    const adminExists = await this.dataService.user.findOne({
      where: { email: 'demo@devias.io' },
    });

    const saltOrRounds = SALT_OR_ROUNDS;
    const adminPassword = 'Barabull17';

    const hashedPassword = await bcrypt.hash(adminPassword, saltOrRounds);

    if (!adminExists) {
      // Create a new admin user
      const adminUser = await this.dataService.user.create({
        email: 'demo@devias.io',
        password: hashedPassword,
        role: 'Admin',
        name: 'Kir',
      });

      // Save the admin user to the database
      await this.dataService.user.save(adminUser);
    }
  }
}
