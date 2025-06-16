import { Test, TestingModule } from '@nestjs/testing';
import { AudittService } from './auditt.service';

describe('AudittService', () => {
  let service: AudittService;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [AudittService],
    }).compile();

    service = module.get<AudittService>(AudittService);
  });

  it('should be defined', () => {
    expect(service).toBeDefined();
  });
});
