import { Module } from '@nestjs/common';
import { AudittService } from './auditt.service';
import { AudittController } from './auditt.controller';

@Module({
  controllers: [AudittController],
  providers: [AudittService],
})
export class AudittModule {}
