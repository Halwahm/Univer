import { BadRequestException, Injectable } from '@nestjs/common';
import { CreateHallDto } from '../../dto/hall/create.dto';
import { UpdateHallDto } from '../../dto/hall/update.dto';
import { DatabaseService } from 'data-service';

@Injectable()
export class HallService {
  constructor(private readonly databaseService: DatabaseService) {}
  private id: string;
  async create(createHallDto: CreateHallDto) {
    const checkHallName = await this.databaseService.hall.findOne({
      where: {
        name: createHallDto.name,
      },
    });
    if (checkHallName) {
      throw new BadRequestException(
        'Зал с таким название уже существует',
        'hall',
      );
    }
    const checkTypePlace = await this.databaseService.typeplace.findOne({
      where: {
        cost_normal: createHallDto.coast_norm,
        cost_vip: createHallDto.coast_vip,
      },
    });
    if (!checkTypePlace) {
      const checkTypePlaces = await this.databaseService.typeplace.save({
        cost_normal: createHallDto.coast_norm,
        cost_vip: createHallDto.coast_vip,
      });
      this.id = checkTypePlaces.id;
    } else {
      this.id = checkTypePlace.id;
    }

    const createHall = await this.databaseService.hall.save({
      name: createHallDto.name,
      count_rows: createHallDto.count_rows,
      count_place: createHallDto.count_place,
      type_Plase: this.id,
    });

    const rowCount = createHallDto.count_place * createHallDto.count_rows;
    for (let i = 1; i <= rowCount; i++) {
      await this.databaseService.place.save({
        place: i,
        hall: {id:createHall.id},
      });
    }
    return createHall;
  }

  async findAll() {
    return await this.databaseService.hall.find();
  }

  findOne(id: number) {
    return `This action returns a #${id} hall`;
  }

  update(id: number, updateHallDto: UpdateHallDto) {
    return `This action updates a #${id} hall`;
  }

  remove(id: number) {
    return `This action removes a #${id} hall`;
  }
}
