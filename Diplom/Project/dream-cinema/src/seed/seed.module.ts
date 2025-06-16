import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { SeedService } from './seed.service';
import { User } from 'entyties';

@Module({
  imports: [TypeOrmModule.forFeature([User])],
  providers: [SeedService],
})
export class SeedModule {}
