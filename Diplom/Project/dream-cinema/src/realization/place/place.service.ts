import { Injectable } from '@nestjs/common';
import { CreatePlaceDto } from '../../dto/place/create.dto';
import { UpdatePlaceDto } from '../../dto/place/update.dto';
import { DatabaseService } from 'data-service';

@Injectable()
export class PlaceService {
  constructor(private readonly databaseService: DatabaseService) {}
  create(createPlaceDto: CreatePlaceDto) {
    return 'This action adds a new place';
  }

  async findAll() {
    return await this.databaseService.place.find();
  }

  findOne(id: number) {
    return `This action returns a #${id} place`;
  }

  update(id: number, updatePlaceDto: UpdatePlaceDto) {
    return `This action updates a #${id} place`;
  }

  remove(id: number) {
    return `This action removes a #${id} place`;
  }
}
