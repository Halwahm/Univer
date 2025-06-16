import { Injectable } from '@nestjs/common';
import { DatabaseService } from 'data-service';

import { CreateAudittDto,UpdateAudittDto } from 'dto';
import { relative } from 'path';
@Injectable()
export class AudittService {
  constructor(private readonly databaseService: DatabaseService) {}
  create(createAudittDto: CreateAudittDto) {
    return createAudittDto;
  }

  findAll() {
    return this.databaseService.auditt.find({
      relations: ['user'],
    });
  }

  findOne(id: number) {
    return `This action returns a #${id} auditt`;
  }
  async GetStatistic() {
  
   let places = [];
   const films = await this.databaseService.auditt
     .createQueryBuilder('auditt')
     .select(['auditt.filmname', 'auditt.date', 'COUNT(auditt.id) AS count'])
     .groupBy('auditt.filmname, auditt.date')
     .orderBy('auditt.date', 'ASC') // Сортировка по возрастанию ('ASC') или по убыванию ('DESC')
     .getRawMany();
      const filmss = await this.databaseService.auditt.find({
      });
  
   return  films;
  }
  update(id: number, updateAudittDto: UpdateAudittDto) {
    return updateAudittDto;
  }

  remove(id: number) {
    return `This action removes a #${id} auditt`;
  }
}
