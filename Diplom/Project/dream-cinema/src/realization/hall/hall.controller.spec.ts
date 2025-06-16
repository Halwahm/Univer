import { Test, TestingModule } from '@nestjs/testing';
import { HallController } from './hall.controller';
import { HallService } from './hall.service';

describe('HallController', () => {
  let controller: HallController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [HallController],
      providers: [HallService],
    }).compile();

    controller = module.get<HallController>(HallController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
