import { Test, TestingModule } from '@nestjs/testing';
import { AudittController } from './auditt.controller';
import { AudittService } from './auditt.service';

describe('AudittController', () => {
  let controller: AudittController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [AudittController],
      providers: [AudittService],
    }).compile();

    controller = module.get<AudittController>(AudittController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
