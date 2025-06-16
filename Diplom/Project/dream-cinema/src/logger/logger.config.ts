import { createLogger, transports, format } from 'winston';
import { ConfigService } from '@nestjs/config';

import { DEV, NODE_ENV, QA } from 'common';


const { combine, timestamp, printf } = format;

const configService = new ConfigService();

const logFormat = printf(({ level, message, timestamp }) => {
  return `${timestamp} [${level.toUpperCase()}]: ${message}`;
});

export const logger = createLogger({
  level: 'info',
  format: combine(timestamp({ format: 'YYYY-MM-DD HH:mm:ss' }), logFormat),
  transports: [new transports.Console()],
});

if (configService.get<string>(NODE_ENV) !== DEV) {
  logger.add(
    new transports.File({ filename: 'logs/error.log', level: 'error' }),
  );
  logger.add(new transports.File({ filename: 'logs/combined.log' }));
}

if (configService.get<string>(NODE_ENV) === QA) {
  logger.add(
    new transports.File({ filename: 'logs/request.log', level: 'info' }),
  );
  logger.add(
    new transports.File({ filename: 'logs/response.log', level: 'info' }),
  );
}
