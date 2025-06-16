import { Controller, Get, Post, Body, Patch, Param, Delete, BadRequestException } from '@nestjs/common';
import { HallService } from './hall.service';
import { CreateHallDto } from '../../dto/hall/create.dto';
import { UpdateHallDto } from '../../dto/hall/update.dto';

@Controller('hall')
export class HallController {
  constructor(private readonly hallService: HallService) {}

  @Post('AddHall')
  async create(@Body() createHallDto: CreateHallDto) {

    if (Number(createHallDto.coast_norm) >= Number(createHallDto.coast_vip)) {
      throw new BadRequestException(
        'Обычные места не могу стоить дороже VIP','coast'
      );
    }
    return await this.hallService.create(createHallDto);
  }

  @Get()
  findAll() {
    return this.hallService.findAll();
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.hallService.findOne(+id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateHallDto: UpdateHallDto) {
    return this.hallService.update(+id, updateHallDto);
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.hallService.remove(+id);
  }
}
