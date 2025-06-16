import { BadRequestException, Injectable } from '@nestjs/common';
import { LoginResponse } from 'auth';
import RequestWithUser from 'auth/interface/request-with-user.interface';
import { ACCESS_TOKEN, REFRESH_TOKEN, SALT_OR_ROUNDS } from 'common';
import { DatabaseService } from 'data-service';
import * as bcrypt from 'bcrypt';
import { RegisterUserDto, UpdateUserDto } from 'dto';
import { UUIDDto } from 'dto/id.dto';
import { User } from 'entyties';
import { Not } from 'typeorm';

@Injectable()
export class UserService {
  constructor(private readonly dataService: DatabaseService) {}

  async create(createUserDto: RegisterUserDto) {
    const newUser = await this.dataService.user.save(createUserDto);

    return newUser;
  }
  async findUserEmail(email: string) {
    const newUser = await this.dataService.user.find({
      where: { email: email },
    });

    return newUser;
  }
  async GetUsers(id: string) {
    const foundUsers = await this.dataService.user.find({
      where: {
        id: Not(id),
      },
      relations: ['auditt'],
    });
    const newArray = foundUsers.map(obj => {
      return { ...obj, good: 0, bad: 0 };
    });
    for (let i = 0; i < foundUsers.length; i++) {
      let good = 0;
      let bad = 0;
      const obj = foundUsers[i];
      // Перебор вложенного массива в каждом объекте
      for (let j = 0; j < obj.auditt.length; j++) {
        if (obj.auditt[j].OperationType === 'Покупка билета') {
          good++;
        } else {
          bad++;
        }
      }
      newArray[i].good = good;
      newArray[i].bad = bad;
    }
    return newArray;
  }

  public async findOneById(id): Promise<User> {
    const foundUser = await this.dataService.user.findOne({ where: { id } });
    return foundUser;
  }

  public async findOneByEmail(email: string): Promise<User> {
    const foundUser = await this.dataService.user.findOne({ where: { email } });
    return foundUser;
  }

  async DeleteUser(idUser: string, id: string) {
    await this.dataService.user.update(idUser,{status:'DisActive'} );
    const foundUsers = await this.dataService.user.find({
      where: {
        id: Not(id),
      },
      relations: ['auditt'],
    });
    const newArray = foundUsers.map(obj => {
      return { ...obj, good: 0, bad: 0 };
    });
    for (let i = 0; i < foundUsers.length; i++) {
      let good = 0;
      let bad = 0;
      const obj = foundUsers[i];
      // Перебор вложенного массива в каждом объекте
      for (let j = 0; j < obj.auditt.length; j++) {
        if (obj.auditt[j].OperationType === 'Покупка билета') {
          good++;
        } else {
          bad++;
        }
      }
      newArray[i].good = good;
      newArray[i].bad = bad;
    }
    return newArray;
  }
  async UnDeleteUser(idUser: string, id: string) {
    await this.dataService.user.update(idUser, { status: 'Active' });

    const foundUsers = await this.dataService.user.find({
      where: {
        id: Not(id),
      },
      relations: ['auditt'],
    });
    const newArray = foundUsers.map(obj => {
      return { ...obj, good: 0, bad: 0 };
    });
    for (let i = 0; i < foundUsers.length; i++) {
      let good = 0;
      let bad = 0;
      const obj = foundUsers[i];
      // Перебор вложенного массива в каждом объекте
      for (let j = 0; j < obj.auditt.length; j++) {
        if (obj.auditt[j].OperationType === 'Покупка билета') {
          good++;
        } else {
          bad++;
        }
      }
      newArray[i].good = good;
      newArray[i].bad = bad;
    }
    return newArray;
  }
  public async logout({ res, cookies }: RequestWithUser) {
    res.clearCookie(ACCESS_TOKEN);
    res.clearCookie(REFRESH_TOKEN);
    const foundUser = await this.dataService.token.delete({
      token: cookies.refreshToken,
    });

    return foundUser;
  }

  async ChangeUserInfo(
    idUser: string,
    name: string,
    email: string,
    password: string,
  ) {
    const foundUserNow = await this.dataService.user.findOne({
      where: { id: idUser },
    });
    if (password === '') {
      password = foundUserNow.password;
    } else {
      const passwordRegex =
        /^[a-zA-Z0-9!@#$%^&*()_+{}[\]:;<>,.?~\\/`'"|-]{8,30}$/;

      if (passwordRegex.test(password)) {
        const saltOrRounds = SALT_OR_ROUNDS;
        const hashedPassword = await bcrypt.hash(password, saltOrRounds);
        password = hashedPassword;
      } else {
        throw new BadRequestException(
          `Пароль должен содержать только латинские буквы, цифры и символы. Длина пароля от 8 до 30 символов`,
          'password',
        );
      }
    }

    if (name === '') {
      name = foundUserNow.name;
    } else {
      const nameRegex = /^[a-zA-Zа-яА-Я]{3,30}$/;
      if (!nameRegex.test(name)) {
        throw new BadRequestException(
          `Имя должно содержать только буквы русского или английского алфавита`,
          'name',
        );
      }
    }

    if (email === '') {
      email = foundUserNow.email;
    } else {
      const emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;

      if (!emailRegex.test(email)) {
        throw new BadRequestException(
          'Некорректный адрес электронной почты',
          'email',
        );
      }
    }

    const foundUser = await this.dataService.user.update(idUser, {
      name: name,
      email: email,
      password: password,
    });
    const foundUsers = await this.dataService.user.findOne({
      where: { id: idUser },
    });

    return foundUsers;
  }
}
