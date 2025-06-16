import { Test, TestingModule } from '@nestjs/testing';
import { TypePlaceService } from './typeplace.service';

describe('TypeplaceService', () => {
  let service: TypePlaceService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [TypePlaceService],
    }).compile();

    service = module.get<TypePlaceService>(TypePlaceService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
