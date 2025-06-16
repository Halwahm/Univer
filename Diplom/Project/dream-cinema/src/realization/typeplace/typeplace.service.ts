import { Injectable } from '@nestjs/common';
import { DatabaseService } from 'data-service';
import { CreateTypePlaceDto,UpdateTypePlaceDto } from 'dto';

@Injectable()
export class TypePlaceService {
  constructor(private readonly databaseService: DatabaseService) {}
  create(createTypePlaceDto: CreateTypePlaceDto) {
    return createTypePlaceDto;
  }

  async findAll() {
    return await this.databaseService.typeplace.find();
  }

  findOne(id: number) {
    return `This action returns a #${id} typeplace`;
  }

  update(id: number, updateTypePlaceDto: UpdateTypePlaceDto) {
    return updateTypePlaceDto;
  }

  remove(id: number) {
    return `This action removes a #${id} typeplace`;
  }
}
