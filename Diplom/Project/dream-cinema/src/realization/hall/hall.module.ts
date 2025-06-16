import { Module } from '@nestjs/common';
import { HallService } from './hall.service';
import { HallController } from './hall.controller';

@Module({
  controllers: [HallController],
  providers: [HallService],
})
export class HallModule {}
