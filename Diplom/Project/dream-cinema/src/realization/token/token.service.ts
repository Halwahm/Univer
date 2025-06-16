import { Injectable } from '@nestjs/common';
import { CreateTokenDto } from '../../dto/token/create.dto';
import { UpdateTokenDto } from '../../dto/token/update.dto';

@Injectable()
export class TokenService {
  create(createTokenDto: CreateTokenDto) {
    return 'This action adds a new token';
  }

  findAll() {
    return `This action returns all token`;
  }

  findOne(id: number) {
    return `This action returns a #${id} token`;
  }

  update(id: number, updateTokenDto: UpdateTokenDto) {
    return `This action updates a #${id} token`;
  }

  remove(id: number) {
    return `This action removes a #${id} token`;
  }
}
