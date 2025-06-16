import {
  Catch,
  ArgumentsHost,
  HttpException,
  HttpStatus,
  NotAcceptableException,
  ConflictException,
} from '@nestjs/common';
import { BaseExceptionFilter } from '@nestjs/core';
import { logger } from 'logger/logger.config';


@Catch()
export class ErrorMiddleware extends BaseExceptionFilter {
  catch(exception: unknown, host: ArgumentsHost) {
    const ctx = host.switchToHttp();
    const response = ctx.getResponse();
    const request = ctx.getRequest();

    const status =
      exception instanceof HttpException
        ? exception.getStatus()
        : HttpStatus.INTERNAL_SERVER_ERROR;

    const message =
      exception instanceof HttpException
        ? exception.getResponse()
        : 'Internal Server Error';

    if (exception instanceof NotAcceptableException) {
      // Обработка ошибки типа NotAcceptableException
      logger.error(exception.message);
    } else if (exception instanceof ConflictException) {
      // Обработка ошибки типа ConflictException
      logger.error(exception.message);
    } else {
      logger.error(exception);
    }

    response.status(status).json({
      statusCode: status,
      message,
      timestamp: new Date().toISOString(),
      path: request.url,
    });
  }
}
