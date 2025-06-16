import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { ValidationPipe } from '@nestjs/common';
import * as cookieParser from 'cookie-parser';
import { SeedService } from 'seed';
async function bootstrap() {
  const app = await NestFactory.create(AppModule);
app.useGlobalPipes(new ValidationPipe({ forbidUnknownValues: true }));
const seedService = app.get(SeedService);
await seedService.seed();
app.use(cookieParser());
app.enableCors({origin:true,
credentials:true});
await app.listen(5000);

}
bootstrap();
