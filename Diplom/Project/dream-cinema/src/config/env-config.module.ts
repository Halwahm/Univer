import { Module } from '@nestjs/common';
import { ConfigModule as NestConfigModule } from '@nestjs/config';

import { ENV_PATH } from 'common';
import { envFileValidationSchema } from 'validation';

@Module({
  imports: [
    NestConfigModule.forRoot({
      envFilePath: [ENV_PATH],
      validationSchema: envFileValidationSchema,
      isGlobal: true,
    }),
  ],
})
export class EnvConfigModule {}
