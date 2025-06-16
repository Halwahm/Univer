import { Test, TestingModule } from '@nestjs/testing';
import { TypePlaceController } from './typeplace.controller';
import { TypePlaceService } from './typeplace.service';

describe('TypePlaceController', () => {
  let controller: TypePlaceController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [TypePlaceController],
      providers: [TypePlaceService],
    }).compile();

    controller = module.get<TypePlaceController>(TypePlaceController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
