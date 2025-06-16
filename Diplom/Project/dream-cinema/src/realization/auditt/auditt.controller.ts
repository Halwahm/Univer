import { Controller, Get, Post, Body, Patch, Param, Delete } from '@nestjs/common';
import { AudittService } from './auditt.service';
import { CreateAudittDto } from '../../dto/auditt/create.dto';
import { UpdateAudittDto } from '../../dto/auditt/update.dto';

@Controller('auditt')
export class AudittController {
  constructor(private readonly audittService: AudittService) {}

  @Post()
  create(@Body() createAudittDto: CreateAudittDto) {
    return this.audittService.create(createAudittDto);
  }

  @Get('GetHistory')
  findAll() {
    return this.audittService.findAll();
  }
  @Get('GetStatistic')
  GetStatistic() {
    return this.audittService.GetStatistic();
  }
  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.audittService.findOne(+id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateAudittDto: UpdateAudittDto) {
    return this.audittService.update(+id, updateAudittDto);
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return this.audittService.remove(+id);
  }
}
