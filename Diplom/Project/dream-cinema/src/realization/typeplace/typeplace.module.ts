import { Module } from '@nestjs/common';
import { TypePlaceService } from './typeplace.service';
import { TypePlaceController } from './typeplace.controller';

@Module({
  controllers: [TypePlaceController],
  providers: [TypePlaceService],
})
export class TypePlaceModule {}
