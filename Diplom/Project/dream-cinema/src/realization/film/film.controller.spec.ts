import { Test, TestingModule } from '@nestjs/testing';
import { FilmController } from './film.controller';
import { FilmService } from './film.service';

describe('FilmController', () => {
  let controller: FilmController;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      controllers: [FilmController],
      providers: [FilmService],
    }).compile();

    controller = module.get<FilmController>(FilmController);
  });

  it('should be defined', () => {
    expect(controller).toBeDefined();
  });
});
