import { Controller, Get, Post, Body, Patch, Param, Delete } from '@nestjs/common';
import { TypePlaceService } from './typeplace.service';
import { CreateTypePlaceDto,UpdateTypePlaceDto } from 'dto';

@Controller('typeplace')
export class TypePlaceController {
  constructor(private readonly typeplaceService: TypePlaceService) {}

  @Post()
  create(@Body() createTypePlaceDto: CreateTypePlaceDto) {
    return this.typeplaceService.create(createTypePlaceDto);
  }

  @Get()
  findAll() {
    return this.typeplaceService.findAll();
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.typeplaceService.findOne(+id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateTypePlaceDto: UpdateTypePlaceDto) {
    return this.typeplaceService.update(+id, updateTypePlaceDto);
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.typeplaceService.remove(+id);
  }
}
